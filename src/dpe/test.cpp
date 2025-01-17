#include "Vdpe.h"  // Verilator로 생성된 모듈 헤더
#include "DRAMSim.h"  // DRAMSim2 헤더
#include <iostream>
#include <cmath>
#include <queue>

bool ready_R = false;
void readCallback(uint64_t address, uint8_t *data, unsigned size)
{
    ready_R = true;
}
int main(int argc, char** argv) {
    // RTL 모델 호출 
    Vdpe *top = new Vdpe;  // Verilator 모델 인스턴스
    top->clock = 0;  // 클럭 초기화

    top->reset = 1;  // top 초기화
    top->clock = 1;
    top->eval();
    top->reset = 0;
    top->clock = 0;
    top->eval();
    
    int bit = 8;
    int tile_num = 1;
    int tile_len = 16;
    int tile_wid = 1;
    int block = 64/bit;
    int group = std::ceil(tile_len/block);
 
    // DRAM 모델 호출
    const std::string config_file = "/home/harry09119/dramsim/ini/DDR3_micron_32M_8B_x4_sg15.ini";
    const std::string working_dir = "/home/harry09119/dramsim/system.ini";
    const std::string results_dir = "/home/harry09119/dramsim/result_dir";
    const std::string trace_file = "";
    unsigned memory_size = 4096;  // 메모리 크기를 unsigned로 명시

    DRAMSim::MultiChannelMemorySystem *memSystem = DRAMSim::getMemorySystemInstance(
        config_file, working_dir, results_dir, trace_file, memory_size
    );

    memSystem->RegisterCallbacks(readCallback, nullptr, nullptr);

    //===1. MatMul 준비단계===//
    
    unsigned startCycle = 0;
    unsigned endCycle = 0;

    //DRAM에 data 저장
    uint8_t dataA[tile_num][group][block];
    uint8_t dataB[tile_num][group][block];

    for (uint8_t i = 0; i < tile_num ; i++) {
      for (uint8_t j = 0; j < group; j++) {
        for(uint8_t k = 0; k < block; k++) {
          dataA[i][j] = i*tile_len + j*block + k + 1;
          dataB[i][j] = i*tile_len + j*block + k + 1;
        }
      }
    }
    
    DRAMSim::MemoryTransaction writeTransaction(DRAMSim::MemoryTransaction::WRITE, 0, tile_len * 2);
    memSystem->addTransaction(writeTransaction);

    while (!memSystem->done()) {
        memSystem->update();
    }

    endCycle = memSystem->getCurrentCycle();

    unsigned preCycle = endCycle - startCycle;
    

    //===2. MATMUL 실행 ===//
    //필요 1: data가 준비됬는지 확인
    //필요 2: PE에 준비된 data 만을 전달
    
    bool valid = true;
    int cycle = 0; // top 모델 기준 

    int next_A[block];
    int next_B[block];    
    
    int tile_i = 0;
    int group_i = 0
    int block_i = 0;

    while(1)
    {
      //PE Run
      if(!valid)
      {
        top->io_inA = next_A[block_i];
        top->io_inB = next_B[block_i];
        block_i -= 1;
        if(bi <= 0)
          valid = true;
      }

      //DRAM Read
      if(!ready_R)
      {
        DRAMSim::MemoryTransaction readTransaction(DRAMSim::MemoryTransaction::READ, 8*group_i*tile_i, 8);
        memSystem->addTransaction(readTransaction);
      }
      
      //Check Data (SRAM 역할)
      if(valid&&ready_R)
      {
        for(int i = 0; i<block;i++)
        {
          next_A[i] = dataA[tile_i][group_i][i];
          next_B[i] = dataB[tile_i][group_i][i];
        }
        block_i = block;
        valid = false;
        ready_R = false;
      }    

      //Clock Management
      clock += 1;

      memSystem->update();
      memSystem->update();
      top->clk = (cycle % 2 == 0) ? 0 : 1;
      top->eval();
    }

    delete top;  // 리소스 해제
    delete memSystem;
    return 0;
}

