// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VPE__SYMS_H_
#define VERILATED_VPE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VPE.h"

// INCLUDE MODULE CLASSES
#include "VPE___024root.h"

// SYMS CLASS (contains all model state)
class VPE__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VPE* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VPE___024root                  TOP;

    // CONSTRUCTORS
    VPE__Syms(VerilatedContext* contextp, const char* namep, VPE* modelp);
    ~VPE__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
