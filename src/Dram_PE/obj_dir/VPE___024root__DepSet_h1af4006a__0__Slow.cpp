// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VPE.h for the primary calling header

#include "verilated.h"

#include "VPE___024root.h"

VL_ATTR_COLD void VPE___024root___settle__TOP__0(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___settle__TOP__0\n"); );
    // Body
    vlSelf->PE__DOT__mul = (0xffffU & ((IData)(vlSelf->io_inA) 
                                       * (IData)(vlSelf->io_inB)));
    vlSelf->io_debug_0 = vlSelf->PE__DOT__out0;
    vlSelf->io_debug_1 = vlSelf->PE__DOT__out1;
    vlSelf->io_outC = ((IData)(vlSelf->io_switch) ? vlSelf->PE__DOT__out1
                        : vlSelf->PE__DOT__out0);
    vlSelf->PE__DOT___out0_T_1 = (vlSelf->PE__DOT__out0 
                                  + (IData)(vlSelf->PE__DOT__mul));
    vlSelf->PE__DOT___out1_T_1 = (vlSelf->PE__DOT__out1 
                                  + (IData)(vlSelf->PE__DOT__mul));
}

VL_ATTR_COLD void VPE___024root___eval_initial(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clock = vlSelf->clock;
}

VL_ATTR_COLD void VPE___024root___eval_settle(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___eval_settle\n"); );
    // Body
    VPE___024root___settle__TOP__0(vlSelf);
}

VL_ATTR_COLD void VPE___024root___final(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___final\n"); );
}

VL_ATTR_COLD void VPE___024root___ctor_var_reset(VPE___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VPE__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VPE___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_inA = VL_RAND_RESET_I(8);
    vlSelf->io_inB = VL_RAND_RESET_I(8);
    vlSelf->io_inC = VL_RAND_RESET_I(32);
    vlSelf->io_outC = VL_RAND_RESET_I(32);
    vlSelf->io_switch = VL_RAND_RESET_I(1);
    vlSelf->io_reset = VL_RAND_RESET_I(1);
    vlSelf->io_debug_0 = VL_RAND_RESET_I(32);
    vlSelf->io_debug_1 = VL_RAND_RESET_I(32);
    vlSelf->PE__DOT__out0 = VL_RAND_RESET_I(32);
    vlSelf->PE__DOT__out1 = VL_RAND_RESET_I(32);
    vlSelf->PE__DOT__mul = VL_RAND_RESET_I(16);
    vlSelf->PE__DOT___out0_T_1 = VL_RAND_RESET_I(32);
    vlSelf->PE__DOT___out1_T_1 = VL_RAND_RESET_I(32);
}
