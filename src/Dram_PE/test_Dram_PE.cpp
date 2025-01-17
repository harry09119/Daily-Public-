#include "VPE.h"
#include "DRAMSim/DRAMSim.h"  // Include DRAMSim2 headers
#include <queue>

int main() {
    VPE *top = new VPE;  // Instantiate Verilator model for PE
    top->clock = 0;      // Initialize clock

    // DRAMSim2 Initialization
    const std::string config_file = "ini/DDR3_micron_32M_8B_x8_sg15.ini";
    const std::string working_dir = "DRAMSim2";
    DRAMSim::MultiChannelMemorySystem *memSystem = DRAMSim::getMemorySystemInstance(
        config_file, working_dir, "results", 4096
    );

    // DRAMSim2 Callbacks
    uint64_t cycle = 0;  // Unified cycle counter
    bool dram_busy = false;  // DRAM busy flag
    uint64_t dram_wait_until = 0;  // Cycle to wait until DRAM completes

    auto read_complete = [&dram_busy](uint64_t addr, uint64_t cycle) {
        printf("Read complete: Addr=%llu\n", addr);
        dram_busy = false;
    };

    auto write_complete = [&dram_busy](uint64_t addr, uint64_t cycle) {
        printf("Write complete: Addr=%llu\n", addr);
        dram_busy = false;
    };

    memSystem->RegisterCallbacks(read_complete, write_complete, nullptr);

    // Test Initialization
    top->io_switch = 1;

    // 1 to 16 Write to DRAM
    for (int i = 1; i <= 16; ++i) {
        uint64_t write_address_inA = 0x1000 + i * 8;  // InA address
        uint64_t write_address_inB = 0x2000 + i * 8;  // InB address

        // Write Transactions
        if (!dram_busy) {
            memSystem->addTransaction(true, write_address_inA);
            memSystem->addTransaction(true, write_address_inB);
            dram_busy = true;
            dram_wait_until = cycle + 20;  // Simulate DRAM latency (example: 20 cycles)
        }

        // Wait for DRAM write completion
        while (cycle < dram_wait_until) {
            memSystem->update();
            top->clock = !top->clock;
            top->eval();
            cycle++;
        }
    }

    // 1 to 16 Read from DRAM and Process in Verilator
    for (int i = 1; i <= 16; ++i) {
        uint64_t read_address_inA = 0x1000 + i * 8;  // InA address
        uint64_t read_address_inB = 0x2000 + i * 8;  // InB address

        // Read Transactions
        if (!dram_busy) {
            memSystem->addTransaction(false, read_address_inA);
            memSystem->addTransaction(false, read_address_inB);
            dram_busy = true;
            dram_wait_until = cycle + 20;  // Simulate DRAM latency (example: 20 cycles)
        }

        // Wait for DRAM read completion and pass data to Verilator
        while (cycle < dram_wait_until) {
            memSystem->update();
            top->clock = !top->clock;
            top->eval();
            cycle++;
        }

        // Pass read values to Verilator inputs
        top->io_inA = i;  // Example value for InA
        top->io_inB = i;  // Example value for InB

        // Run Verilator for 2 cycles to simulate computation
        for (int verilator_steps = 0; verilator_steps < 2; ++verilator_steps) {
            top->clock = !top->clock;
            top->eval();
            cycle++;

            // Output results at the end of a full clock cycle
            if (verilator_steps == 1) {
                printf("[Cycle %llu] OutC: %d Debug0: %d Debug1: %d\n",
                       cycle, top->io_outC, top->io_debug_0, top->io_debug_1);
            }
        }
    }

    // Cleanup
    delete top;
    return 0;
}
