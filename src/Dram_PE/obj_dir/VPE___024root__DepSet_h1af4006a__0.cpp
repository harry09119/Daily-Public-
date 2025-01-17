// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VPE.h for the primary calling header

#include "verilated.h"

#include "VPE___024root.h"

VL_INLINE_OPT void VPE___024root___combo__TOP__0(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___combo__TOP__0\n"); );
    // Body
    vlSelf->PE__DOT__mul = (0xffffU & ((IData)(vlSelf->io_inA) 
                                       * (IData)(vlSelf->io_inB)));
}

VL_INLINE_OPT void VPE___024root___sequent__TOP__0(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___sequent__TOP__0\n"); );
    // Body
    if (vlSelf->reset) {
        vlSelf->PE__DOT__out1 = 0U;
        vlSelf->PE__DOT__out0 = 0U;
    } else if (vlSelf->io_reset) {
        vlSelf->PE__DOT__out1 = 0U;
        vlSelf->PE__DOT__out0 = 0U;
    } else if (vlSelf->io_switch) {
        vlSelf->PE__DOT__out1 = vlSelf->io_inC;
        vlSelf->PE__DOT__out0 = vlSelf->PE__DOT___out0_T_1;
    } else {
        vlSelf->PE__DOT__out1 = vlSelf->PE__DOT___out1_T_1;
        vlSelf->PE__DOT__out0 = vlSelf->io_inC;
    }
    vlSelf->io_debug_1 = vlSelf->PE__DOT__out1;
    vlSelf->io_debug_0 = vlSelf->PE__DOT__out0;
}

VL_INLINE_OPT void VPE___024root___combo__TOP__1(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___combo__TOP__1\n"); );
    // Body
    vlSelf->PE__DOT___out1_T_1 = (vlSelf->PE__DOT__out1 
                                  + (IData)(vlSelf->PE__DOT__mul));
    vlSelf->PE__DOT___out0_T_1 = (vlSelf->PE__DOT__out0 
                                  + (IData)(vlSelf->PE__DOT__mul));
    vlSelf->io_outC = ((IData)(vlSelf->io_switch) ? vlSelf->PE__DOT__out1
                        : vlSelf->PE__DOT__out0);
}

void VPE___024root___eval(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___eval\n"); );
    // Body
    VPE___024root___combo__TOP__0(vlSelf);
    if (((IData)(vlSelf->clock) & (~ (IData)(vlSelf->__Vclklast__TOP__clock)))) {
        VPE___024root___sequent__TOP__0(vlSelf);
    }
    VPE___024root___combo__TOP__1(vlSelf);
    // Final
    vlSelf->__Vclklast__TOP__clock = vlSelf->clock;
}

#ifdef VL_DEBUG
void VPE___024root___eval_debug_assertions(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelf->io_switch & 0xfeU))) {
        Verilated::overWidthError("io_switch");}
    if (VL_UNLIKELY((vlSelf->io_reset & 0xfeU))) {
        Verilated::overWidthError("io_reset");}
}
#endif  // VL_DEBUG
