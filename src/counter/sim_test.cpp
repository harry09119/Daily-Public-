#include "Vtop_module.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main() {
    Verilated::traceEverOn(true);  // VCD 파일 활성화

    Vtop_module* top = new Vtop_module;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);           // 추적 설정
    tfp->open("waveform.vcd");     // VCD 파일 열기

    for (int time = 0; time < 100; ++time) {
        top->clk = time % 2;       // 클럭 생성
        top->eval();               // 평가
        tfp->dump(time);           // VCD 기록
        Verilated::timeInc(1);     // 시간 증가
    }

    tfp->close();                  // VCD 파일 닫기
    delete tfp;                    // 메모리 해제
    delete top;

    return 0;
}

