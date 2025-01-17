#include "VPE.h"  // Include the generated header for the PE module

int main() {
  VPE *top = new VPE;  // Instantiate the Verilator model for the PE module

  // Setup initial values and drive inputs
  top->io_switch = 1;

  // Evaluate the module
  top->io_inA = 5;// = 5
  top->io_inB = 3;// = 8
  top->io_inC = 15;// = 15
  top->eval();

  for(int i=0; i < 10; i++) 
  {
    if(i==0)
      top->io_reset = 1;
    else
      top->io_reset = 0;

    top->clock = !top->clock;
    top->eval();

    // Access outputs, expect 55
    if(i%2==0)
    {
      int cycle = i/2;
      int outputValue = top->io_outC;
      int debug0Value = top->io_debug_0;
      int debug1Value = top->io_debug_1;

      printf("\n> [%d]: %d %d %d\n", cycle, outputValue, debug0Value, debug1Value);
    }
  }
  // Cleanup
  delete top;
  return 0;
}

