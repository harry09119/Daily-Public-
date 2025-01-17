// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VPE.h for the primary calling header

#ifndef VERILATED_VPE___024ROOT_H_
#define VERILATED_VPE___024ROOT_H_  // guard

#include "verilated.h"

class VPE__Syms;
VL_MODULE(VPE___024root) {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(io_inA,7,0);
    VL_IN8(io_inB,7,0);
    VL_IN8(io_switch,0,0);
    VL_IN8(io_reset,0,0);
    CData/*0:0*/ __Vclklast__TOP__clock;
    SData/*15:0*/ PE__DOT__mul;
    VL_IN(io_inC,31,0);
    VL_OUT(io_outC,31,0);
    VL_OUT(io_debug_0,31,0);
    VL_OUT(io_debug_1,31,0);
    IData/*31:0*/ PE__DOT__out0;
    IData/*31:0*/ PE__DOT__out1;
    IData/*31:0*/ PE__DOT___out0_T_1;
    IData/*31:0*/ PE__DOT___out1_T_1;

    // INTERNAL VARIABLES
    VPE__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
    VPE___024root(const char* name);
    ~VPE___024root();
    VL_UNCOPYABLE(VPE___024root);

    // INTERNAL METHODS
    void __Vconfigure(VPE__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
