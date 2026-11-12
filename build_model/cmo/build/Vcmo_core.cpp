// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcmo_core__pch.h"

//============================================================
// Constructors

Vcmo_core::Vcmo_core(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcmo_core__Syms(contextp(), _vcname__, this)}
    , clk_i{vlSymsp->TOP.clk_i}
    , rst_ni{vlSymsp->TOP.rst_ni}
    , req_valid_i{vlSymsp->TOP.req_valid_i}
    , req_ready_o{vlSymsp->TOP.req_ready_o}
    , req_op_i{vlSymsp->TOP.req_op_i}
    , cache_req_valid_o{vlSymsp->TOP.cache_req_valid_o}
    , cache_req_ready_i{vlSymsp->TOP.cache_req_ready_i}
    , cache_req_op_o{vlSymsp->TOP.cache_req_op_o}
    , cache_rsp_valid_i{vlSymsp->TOP.cache_rsp_valid_i}
    , cache_rsp_error_i{vlSymsp->TOP.cache_rsp_error_i}
    , done_o{vlSymsp->TOP.done_o}
    , error_o{vlSymsp->TOP.error_o}
    , req_addr_i{vlSymsp->TOP.req_addr_i}
    , cache_req_addr_o{vlSymsp->TOP.cache_req_addr_o}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcmo_core::Vcmo_core(const char* _vcname__)
    : Vcmo_core(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcmo_core::~Vcmo_core() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcmo_core___024root___eval_debug_assertions(Vcmo_core___024root* vlSelf);
#endif  // VL_DEBUG
void Vcmo_core___024root___eval_static(Vcmo_core___024root* vlSelf);
void Vcmo_core___024root___eval_initial(Vcmo_core___024root* vlSelf);
void Vcmo_core___024root___eval_settle(Vcmo_core___024root* vlSelf);
void Vcmo_core___024root___eval(Vcmo_core___024root* vlSelf);

void Vcmo_core::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcmo_core::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcmo_core___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcmo_core___024root___eval_static(&(vlSymsp->TOP));
        Vcmo_core___024root___eval_initial(&(vlSymsp->TOP));
        Vcmo_core___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcmo_core___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcmo_core::eventsPending() { return false; }

uint64_t Vcmo_core::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vcmo_core::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcmo_core___024root___eval_final(Vcmo_core___024root* vlSelf);

VL_ATTR_COLD void Vcmo_core::final() {
    Vcmo_core___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcmo_core::hierName() const { return vlSymsp->name(); }
const char* Vcmo_core::modelName() const { return "Vcmo_core"; }
unsigned Vcmo_core::threads() const { return 1; }
void Vcmo_core::prepareClone() const { contextp()->prepareClone(); }
void Vcmo_core::atClone() const {
    contextp()->threadPoolpOnClone();
}
