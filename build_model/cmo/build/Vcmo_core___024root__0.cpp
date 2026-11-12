// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcmo_core.h for the primary calling header

#include "Vcmo_core__pch.h"

void Vcmo_core___024root___eval_triggers_vec__act(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_triggers_vec__act\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_ni)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_ni__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk_i) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk_i__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk_i__0 = vlSelfRef.clk_i;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_ni__0 = vlSelfRef.rst_ni;
}

bool Vcmo_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vcmo_core___024root___nba_sequent__TOP__0(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___nba_sequent__TOP__0\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vdly__cmo_core__DOT__state_q;
    __Vdly__cmo_core__DOT__state_q = 0;
    // Body
    __Vdly__cmo_core__DOT__state_q = vlSelfRef.cmo_core__DOT__state_q;
    if (vlSelfRef.rst_ni) {
        vlSelfRef.done_o = 0U;
        vlSelfRef.error_o = 0U;
        if ((0U == (IData)(vlSelfRef.cmo_core__DOT__state_q))) {
            if (((IData)(vlSelfRef.req_valid_i) & (IData)(vlSelfRef.req_ready_o))) {
                vlSelfRef.cmo_core__DOT__addr_q = vlSelfRef.req_addr_i;
                vlSelfRef.cmo_core__DOT__op_q = vlSelfRef.req_op_i;
                __Vdly__cmo_core__DOT__state_q = 1U;
            }
        } else if ((1U == (IData)(vlSelfRef.cmo_core__DOT__state_q))) {
            if (((IData)(vlSelfRef.cache_req_valid_o) 
                 & (IData)(vlSelfRef.cache_req_ready_i))) {
                if (vlSelfRef.cmo_core__DOT__is_prefetch) {
                    vlSelfRef.done_o = 1U;
                    vlSelfRef.error_o = 0U;
                    __Vdly__cmo_core__DOT__state_q = 0U;
                } else {
                    __Vdly__cmo_core__DOT__state_q = 2U;
                }
            }
        } else if ((2U == (IData)(vlSelfRef.cmo_core__DOT__state_q))) {
            if (vlSelfRef.cache_rsp_valid_i) {
                vlSelfRef.done_o = 1U;
                vlSelfRef.error_o = vlSelfRef.cache_rsp_error_i;
                __Vdly__cmo_core__DOT__state_q = 0U;
            }
        } else {
            __Vdly__cmo_core__DOT__state_q = 0U;
        }
    } else {
        __Vdly__cmo_core__DOT__state_q = 0U;
        vlSelfRef.cmo_core__DOT__addr_q = 0U;
        vlSelfRef.cmo_core__DOT__op_q = 0U;
        vlSelfRef.done_o = 0U;
        vlSelfRef.error_o = 0U;
    }
    vlSelfRef.cmo_core__DOT__state_q = __Vdly__cmo_core__DOT__state_q;
    vlSelfRef.cache_req_addr_o = vlSelfRef.cmo_core__DOT__addr_q;
    vlSelfRef.cache_req_op_o = vlSelfRef.cmo_core__DOT__op_q;
    vlSelfRef.cmo_core__DOT__is_prefetch = ((0U == (IData)(vlSelfRef.cmo_core__DOT__op_q)) 
                                            | (1U == (IData)(vlSelfRef.cmo_core__DOT__op_q)));
    vlSelfRef.req_ready_o = (0U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
    vlSelfRef.cache_req_valid_o = (1U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
}

void Vcmo_core___024root___eval_nba(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_nba\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q;
    __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 0;
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q 
            = vlSelfRef.cmo_core__DOT__state_q;
        if (vlSelfRef.rst_ni) {
            vlSelfRef.done_o = 0U;
            vlSelfRef.error_o = 0U;
            if ((0U == (IData)(vlSelfRef.cmo_core__DOT__state_q))) {
                if (((IData)(vlSelfRef.req_valid_i) 
                     & (IData)(vlSelfRef.req_ready_o))) {
                    vlSelfRef.cmo_core__DOT__addr_q 
                        = vlSelfRef.req_addr_i;
                    vlSelfRef.cmo_core__DOT__op_q = vlSelfRef.req_op_i;
                    __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 1U;
                }
            } else if ((1U == (IData)(vlSelfRef.cmo_core__DOT__state_q))) {
                if (((IData)(vlSelfRef.cache_req_valid_o) 
                     & (IData)(vlSelfRef.cache_req_ready_i))) {
                    if (vlSelfRef.cmo_core__DOT__is_prefetch) {
                        vlSelfRef.done_o = 1U;
                        vlSelfRef.error_o = 0U;
                        __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 0U;
                    } else {
                        __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 2U;
                    }
                }
            } else if ((2U == (IData)(vlSelfRef.cmo_core__DOT__state_q))) {
                if (vlSelfRef.cache_rsp_valid_i) {
                    vlSelfRef.done_o = 1U;
                    vlSelfRef.error_o = vlSelfRef.cache_rsp_error_i;
                    __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 0U;
                }
            } else {
                __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 0U;
            }
        } else {
            __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q = 0U;
            vlSelfRef.cmo_core__DOT__addr_q = 0U;
            vlSelfRef.cmo_core__DOT__op_q = 0U;
            vlSelfRef.done_o = 0U;
            vlSelfRef.error_o = 0U;
        }
        vlSelfRef.cmo_core__DOT__state_q = __Vinline__nba_sequent__TOP__0___Vdly__cmo_core__DOT__state_q;
        vlSelfRef.cache_req_addr_o = vlSelfRef.cmo_core__DOT__addr_q;
        vlSelfRef.cache_req_op_o = vlSelfRef.cmo_core__DOT__op_q;
        vlSelfRef.cmo_core__DOT__is_prefetch = ((0U 
                                                 == (IData)(vlSelfRef.cmo_core__DOT__op_q)) 
                                                | (1U 
                                                   == (IData)(vlSelfRef.cmo_core__DOT__op_q)));
        vlSelfRef.req_ready_o = (0U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
        vlSelfRef.cache_req_valid_o = (1U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
    }
}

void Vcmo_core___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcmo_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vcmo_core___024root___eval_phase__act(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_phase__act\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vcmo_core___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcmo_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vcmo_core___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vcmo_core___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vcmo_core___024root___eval_phase__nba(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_phase__nba\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vcmo_core___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vcmo_core___024root___eval_nba(vlSelf);
        Vcmo_core___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vcmo_core___024root___eval(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vcmo_core___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("rtl/cmo_core/cmo_core.sv", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vcmo_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("rtl/cmo_core/cmo_core.sv", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vcmo_core___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vcmo_core___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vcmo_core___024root___eval_debug_assertions(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_debug_assertions\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk_i & 0xfeU)))) {
        Verilated::overWidthError("clk_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_ni & 0xfeU)))) {
        Verilated::overWidthError("rst_ni");
    }
    if (VL_UNLIKELY(((vlSelfRef.req_valid_i & 0xfeU)))) {
        Verilated::overWidthError("req_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.req_op_i & 0xf8U)))) {
        Verilated::overWidthError("req_op_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.cache_req_ready_i & 0xfeU)))) {
        Verilated::overWidthError("cache_req_ready_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.cache_rsp_valid_i & 0xfeU)))) {
        Verilated::overWidthError("cache_rsp_valid_i");
    }
    if (VL_UNLIKELY(((vlSelfRef.cache_rsp_error_i & 0xfeU)))) {
        Verilated::overWidthError("cache_rsp_error_i");
    }
}
#endif  // VL_DEBUG
