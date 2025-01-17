#include "Vdramsim_test.h"  // Verilator로 생성된 모듈 헤더
#include <DRAMSim.h>  // DRAMSim2 헤더
#include <iostream>
#include <cmath>
#include <queue>

using namespace DRAMSim;
//#define RETURN_TRANSACTIONS 1

int ready_R = 0;

class mem_task
{
  public:
    void read_end(unsigned id, uint64_t address, uint64_t clock_cycle)
    {
      printf("[Callback] read complete: %d 0x%lx cycle=%lu\n", id, address, clock_cycle);
      ready_R = 1;
    }

    void write_end(unsigned id, uint64_t address, uint64_t clock_cycle)
    {
      printf("[Callback] write complete: %d 0x%lx cycle=%lu\n", id, address, clock_cycle); 
    }
    
  //private:

};

int main(int argc, char** argv) {
    // RTL 모델 호출 
    Vdramsim_test *top = new Vdramsim_test;  // Verilator 모델 인스턴스

    // DRAM 모델 호출
    const std::string config_file = "/home/harry09119/dramsim/ini/DDR3_micron_32M_8B_x4_sg15.ini";
    const std::string working_dir = "/home/harry09119/dramsim/system.ini";
    const std::string results_dir = "/home/harry09119/dramsim/result_dir";
    const std::string trace_file = "";
    unsigned memory_size = 1024 * 4;  // 메모리 크기를 unsigned로 명시

    MultiChannelMemorySystem *dram = getMemorySystemInstance(config_file, working_dir, results_dir, trace_file, memory_size);
    
    mem_task task;
    TransactionCompleteCB *read_cb = new Callback<mem_task, void, unsigned, uint64_t, uint64_t>(&task, &mem_task::read_end);
    TransactionCompleteCB *write_cb = new Callback<mem_task, void, unsigned, uint64_t, uint64_t>(&task, &mem_task::write_end);    
    
    dram->RegisterCallbacks(read_cb, write_cb, NULL);

    top->clock = 0;  // 클럭 초기화
    
    int bit = 8;
    int tile_num = 1;
    int tile_len = 16;
    int tile_wid = 1;
    int block = 64/bit;
    int group = std::ceil(tile_len/block);
 
    printf(">>> %d %d %d\n", tile_num,group,block);
    //===1. MatMul 준비단계===//
    
    unsigned startCycle = 0;
    unsigned endCycle = 0;

    //DRAM에 data 저장
    uint8_t dataA[tile_num][group][block];
    uint8_t dataB[tile_num][group][block];

    for (uint8_t i = 0; i < tile_num ; i++) {
      for (uint8_t j = 0; j < group; j++) {
        for(uint8_t k = 0; k < block; k++) {
          dataA[i][j][k] = i*tile_len + j*block + k + 1;
          dataB[i][j][k] = i*tile_len + j*block + k + 1;
        }
      }
    }
    
    //===2. MATMUL 실행 ===//
    //필요 1: data가 준비됬는지 확인
    //필요 2: PE에 준비된 data 만을 전달
    
    int valid = 1;
    int cycle = 0; // top 모델 기준 

    int next_A[block];
    int next_B[block];    
    
    int tile_i = 0;
    int group_i = 0;
    int block_i = 0;

    int addr = 0;
    
    while(1)
    {
      printf("[%d] tile_i:%d, group_i:%d, block_i:%d\n",cycle, tile_i,group_i, block_i);
      printf(">> valid:%d, ready:%d\n", valid, ready_R);

      //PE Run
      if(!valid)
      {
        top->io_inA = next_A[block_i];
        top->io_inB = next_B[block_i];
        block_i -= 1;
        if(block_i <= 0)
          valid = 1;

        if(tile_i < 0)
          printf("%d\n",tile_i);
          endCycle = cycle;
          break;
      }

      //DRAM Read
      if(!ready_R && tile_i>=0)
      {
        addr = tile_i * group_i;
        addr = 1LL<<33 | addr;        
        dram->addTransaction(0,addr);
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

        group_i += 1;
        if(group_i >= group)
        {
          group_i = 0;
          tile_i += 1;
        }

        if(tile_i >= tile_num)
          tile_i = -10; //Stop DRAM reading

        valid = 0;
        ready_R = 0;
      }    

      //Clock Management
      cycle += 1;

      dram->update();
      top->clock = (cycle % 2 == 0) ? 0 : 1;
      top->eval();
    }
    
    delete top;  // 리소스 해제
    delete dram;
    return 0;
}

