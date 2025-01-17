// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VPE.h"
#include "VPE__Syms.h"

//============================================================
// Constructors

VPE::VPE(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new VPE__Syms(_vcontextp__, _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_inA{vlSymsp->TOP.io_inA}
    , io_inB{vlSymsp->TOP.io_inB}
    , io_switch{vlSymsp->TOP.io_switch}
    , io_reset{vlSymsp->TOP.io_reset}
    , io_inC{vlSymsp->TOP.io_inC}
    , io_outC{vlSymsp->TOP.io_outC}
    , io_debug_0{vlSymsp->TOP.io_debug_0}
    , io_debug_1{vlSymsp->TOP.io_debug_1}
    , rootp{&(vlSymsp->TOP)}
{
}

VPE::VPE(const char* _vcname__)
    : VPE(nullptr, _vcname__)
{
}

//============================================================
// Destructor

VPE::~VPE() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void VPE___024root___eval_initial(VPE___024root* vlSelf);
void VPE___024root___eval_settle(VPE___024root* vlSelf);
void VPE___024root___eval(VPE___024root* vlSelf);
#ifdef VL_DEBUG
void VPE___024root___eval_debug_assertions(VPE___024root* vlSelf);
#endif  // VL_DEBUG
void VPE___024root___final(VPE___024root* vlSelf);

static void _eval_initial_loop(VPE__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    VPE___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        VPE___024root___eval_settle(&(vlSymsp->TOP));
        VPE___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void VPE::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VPE::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VPE___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        VPE___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

VerilatedContext* VPE::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* VPE::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void VPE::final() {
    VPE___024root___final(&(vlSymsp->TOP));
}
