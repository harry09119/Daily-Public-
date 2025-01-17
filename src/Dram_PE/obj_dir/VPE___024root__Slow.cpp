// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VPE.h for the primary calling header

#include "verilated.h"

#include "VPE__Syms.h"
#include "VPE___024root.h"

void VPE___024root___ctor_var_reset(VPE___024root* vlSelf);

VPE___024root::VPE___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    VPE___024root___ctor_var_reset(this);
}

void VPE___024root::__Vconfigure(VPE__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

VPE___024root::~VPE___024root() {
}
