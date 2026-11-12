#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "Vcmo_core.h"
#include "verilated.h"

enum class CmoOp : uint8_t {
    PREFETCH_R = 0,
    PREFETCH_W = 1,
    CLEAN      = 2,
    FLUSH      = 3,
    INVAL      = 4,
    ZERO       = 5
};


// Basic test helpers

static void tick(Vcmo_core* dut)
{
    dut->clk_i = 0;
    dut->eval();

    dut->clk_i = 1;
    dut->eval();

    dut->clk_i = 0;
    dut->eval();
}


static void expect(bool condition, const char* message)
{
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}


static void reset_dut(Vcmo_core* dut)
{
    dut->req_valid_i = 0;
    dut->req_addr_i = 0;
    dut->req_op_i = 0;

    dut->cache_req_ready_i = 0;

    dut->cache_rsp_valid_i = 0;
    dut->cache_rsp_error_i = 0;

    dut->rst_ni = 0;

    tick(dut);
    tick(dut);

    dut->rst_ni = 1;

    tick(dut);
}


// Helper for starting a CMO request

static void send_request(
    Vcmo_core* dut,
    uint32_t address,
    CmoOp operation)
{
    expect(
        dut->req_ready_o == 1,
        "CMO must be ready before accepting a request"
    );

    dut->req_valid_i = 1;
    dut->req_addr_i = address;
    dut->req_op_i = static_cast<uint8_t>(operation);

    tick(dut);

    dut->req_valid_i = 0;
}



static void test_reset(Vcmo_core* dut)
{
    std::cout << "[TEST] reset\n";

    reset_dut(dut);

    expect(dut->req_ready_o == 1,
           "CMO must be ready after reset");

    expect(dut->cache_req_valid_o == 0,
           "No cache request may exist after reset");

    expect(dut->done_o == 0,
           "done must be zero after reset");

    expect(dut->error_o == 0,
           "error must be zero after reset");

    std::cout << "  PASS\n";
}



static void test_basic_blocking_request(Vcmo_core* dut)
{
    std::cout << "[TEST] basic CLEAN\n";

    reset_dut(dut);

    send_request(
        dut,
        0x1000,
        CmoOp::CLEAN
    );

    expect(dut->cache_req_valid_o == 1,
           "Cache request must become valid");

    expect(dut->cache_req_addr_o == 0x1000,
           "Cache request address must match CPU request");

    expect(
        dut->cache_req_op_o ==
            static_cast<uint8_t>(CmoOp::CLEAN),
        "Cache operation must be CLEAN"
    );

    expect(dut->req_ready_o == 0,
           "CMO must not accept another request while busy");

    // Cache accepts request.
    dut->cache_req_ready_i = 1;

    tick(dut);

    dut->cache_req_ready_i = 0;

    expect(dut->cache_req_valid_o == 0,
           "Cache request must stop after acceptance");

    expect(dut->done_o == 0,
           "CMO must not finish before response");

    dut->cache_rsp_valid_i = 1;
    dut->cache_rsp_error_i = 0;

    tick(dut);

    dut->cache_rsp_valid_i = 0;

    expect(dut->done_o == 1,
           "CMO must assert done after cache response");

    expect(dut->error_o == 0,
           "Successful response must not report error");

    // done should only be one cycle.
    tick(dut);

    expect(dut->done_o == 0,
           "done must be a one-cycle pulse");

    expect(dut->req_ready_o == 1,
           "CMO must return to ready state");

    std::cout << "  PASS\n";
}



static void test_cache_backpressure(Vcmo_core* dut)
{
    std::cout << "[TEST] cache backpressure\n";

    reset_dut(dut);

    send_request(
        dut,
        0x2000,
        CmoOp::CLEAN
    );

    // Cache intentionally refuses request for several cycles.
    dut->cache_req_ready_i = 0;

    for (int i = 0; i < 5; ++i) {

        expect(dut->cache_req_valid_o == 1,
               "Request valid must stay asserted during backpressure");

        expect(dut->cache_req_addr_o == 0x2000,
               "Address must remain stable during backpressure");

        expect(
            dut->cache_req_op_o ==
                static_cast<uint8_t>(CmoOp::CLEAN),
            "Operation must remain stable during backpressure"
        );

        expect(dut->done_o == 0,
               "CMO cannot finish before cache accepts request");

        tick(dut);
    }

    dut->cache_req_ready_i = 1;

    tick(dut);

    dut->cache_req_ready_i = 0;

    expect(dut->cache_req_valid_o == 0,
           "Request must disappear after handshake");

    dut->cache_rsp_valid_i = 1;

    tick(dut);

    dut->cache_rsp_valid_i = 0;

    expect(dut->done_o == 1,
           "CMO must complete after cache response");

    std::cout << "  PASS\n";
}



static void test_delayed_response(Vcmo_core* dut)
{
    std::cout << "[TEST] delayed response\n";

    reset_dut(dut);

    send_request(
        dut,
        0x3000,
        CmoOp::FLUSH
    );

    dut->cache_req_ready_i = 1;

    tick(dut);

    dut->cache_req_ready_i = 0;

    for (int i = 0; i < 5; ++i) {

        expect(dut->done_o == 0,
               "done must stay low while waiting for response");

        expect(dut->req_ready_o == 0,
               "CMO must remain busy while waiting for response");

        tick(dut);
    }

    dut->cache_rsp_valid_i = 1;
    dut->cache_rsp_error_i = 0;

    tick(dut);

    dut->cache_rsp_valid_i = 0;

    expect(dut->done_o == 1,
           "Delayed response must eventually complete request");

    expect(dut->error_o == 0,
           "Successful delayed response must not report error");

    std::cout << "  PASS\n";
}



static void test_error_response(Vcmo_core* dut)
{
    std::cout << "[TEST] error response\n";

    reset_dut(dut);

    send_request(
        dut,
        0x4000,
        CmoOp::INVAL
    );

    dut->cache_req_ready_i = 1;
    tick(dut);
    dut->cache_req_ready_i = 0;

    dut->cache_rsp_valid_i = 1;
    dut->cache_rsp_error_i = 1;

    tick(dut);

    dut->cache_rsp_valid_i = 0;
    dut->cache_rsp_error_i = 0;

    expect(dut->done_o == 1,
           "Error response still completes the transaction");

    expect(dut->error_o == 1,
           "Cache error must propagate to CMO error output");

    tick(dut);

    expect(dut->error_o == 0,
           "error must return to zero");

    std::cout << "  PASS\n";
}



static void test_back_to_back_requests(Vcmo_core* dut)
{
    std::cout << "[TEST] back-to-back requests\n";

    reset_dut(dut);

    send_request(
        dut,
        0x5000,
        CmoOp::CLEAN
    );

    expect(dut->req_ready_o == 0,
           "CMO must be busy after first request");

    dut->req_valid_i = 1;
    dut->req_addr_i = 0x6000;
    dut->req_op_i =
        static_cast<uint8_t>(CmoOp::FLUSH);

    tick(dut);

    expect(dut->req_ready_o == 0,
           "Second request must not be accepted while CMO is busy");

    expect(dut->cache_req_addr_o == 0x5000,
           "First request must not be overwritten by second request");

    dut->cache_req_ready_i = 1;

    tick(dut);

    dut->cache_req_ready_i = 0;

    dut->cache_rsp_valid_i = 1;

    tick(dut);

    dut->cache_rsp_valid_i = 0;

    expect(dut->done_o == 1,
           "First request must complete");

    expect(dut->req_ready_o == 1,
           "CMO must become ready after completing first request");

    tick(dut);

    dut->req_valid_i = 0;

    expect(dut->cache_req_valid_o == 1,
           "Second request must now be issued");

    expect(dut->cache_req_addr_o == 0x6000,
           "Second request address must be preserved");

    expect(
        dut->cache_req_op_o ==
            static_cast<uint8_t>(CmoOp::FLUSH),
        "Second operation must be PREFETCH_W"
    );

    dut->cache_req_ready_i = 1;
    tick(dut);
    dut->cache_req_ready_i = 0;

    dut->cache_rsp_valid_i = 1;
    dut->cache_rsp_error_i = 0;

    tick(dut);

    dut->cache_rsp_valid_i = 0;

    expect(dut->done_o == 1,
           "Second request must complete");

    std::cout << "  PASS\n";
}



static void test_reset_while_busy(Vcmo_core* dut)
{
    std::cout << "[TEST] reset while busy\n";

    reset_dut(dut);

    send_request(
        dut,
        0x7000,
        CmoOp::ZERO
    );

    expect(dut->cache_req_valid_o == 1,
           "Request must be active before reset");

    dut->rst_ni = 0;
    dut->eval();

    expect(dut->cache_req_valid_o == 0,
           "Reset must cancel pending cache request");

    expect(dut->req_ready_o == 1,
           "Reset must return CMO to idle");

    expect(dut->done_o == 0,
           "Reset must clear done");

    expect(dut->error_o == 0,
           "Reset must clear error");

    dut->rst_ni = 1;
    tick(dut);

    expect(dut->req_ready_o == 1,
           "CMO must operate normally after reset");

    std::cout << "  PASS\n";
}


static void test_operation_passthrough(Vcmo_core* dut)
{
    std::cout << "[TEST] operation pass-through\n";

    const CmoOp operations[] = {
        CmoOp::PREFETCH_R,
        CmoOp::PREFETCH_W,
        CmoOp::CLEAN,
        CmoOp::FLUSH,
        CmoOp::INVAL,
        CmoOp::ZERO
    };

    for (CmoOp op : operations) {
        reset_dut(dut);

        send_request(dut, 0x12345678, op);

        expect(
            dut->cache_req_op_o ==
                static_cast<uint8_t>(op),
            "CMO operation changed during forwarding"
        );

        expect(
            dut->cache_req_addr_o == 0x12345678,
            "Address changed during forwarding"
        );
    }

    std::cout << "  PASS\n";
}

static void test_cache_ready_preasserted(Vcmo_core* dut)
{
    std::cout << "[TEST] cache ready preasserted\n";

    reset_dut(dut);

    dut->cache_req_ready_i = 1;

    send_request(
        dut,
        0x9000,
        CmoOp::CLEAN
    );

    tick(dut);

    dut->cache_req_ready_i = 0;

    expect(
        dut->cache_req_valid_o == 0,
        "Request should be accepted when cache was already ready"
    );

    expect(
        dut->done_o == 0,
        "Acceptance alone must not complete transaction"
    );

    dut->cache_rsp_valid_i = 1;
    tick(dut);
    dut->cache_rsp_valid_i = 0;

    expect(dut->done_o == 1,
           "Transaction must complete normally");

    std::cout << "  PASS\n";
}

static void test_spurious_response_idle(Vcmo_core* dut)
{
    std::cout << "[TEST] spurious response while idle\n";

    reset_dut(dut);

    dut->cache_rsp_valid_i = 1;
    dut->cache_rsp_error_i = 1;

    tick(dut);

    dut->cache_rsp_valid_i = 0;
    dut->cache_rsp_error_i = 0;

    expect(dut->done_o == 0,
           "Spurious response must not complete a transaction");

    expect(dut->error_o == 0,
           "Spurious response must not create an error");

    expect(dut->req_ready_o == 1,
           "CMO must remain idle");

    std::cout << "  PASS\n";
}

static void test_reset_while_waiting_response(Vcmo_core* dut)
{
    std::cout << "[TEST] reset while waiting for response\n";

    reset_dut(dut);

    send_request(
        dut,
        0xA000,
        CmoOp::FLUSH
    );

    // Cache accepts the request.
    dut->cache_req_ready_i = 1;
    tick(dut);
    dut->cache_req_ready_i = 0;

    // We should now be waiting for the response.
    expect(dut->cache_req_valid_o == 0,
           "Request must already be accepted");

    expect(dut->req_ready_o == 0,
           "CMO must remain busy while waiting for response");

    expect(dut->done_o == 0,
           "CMO must not be done before response");

    // Reset while waiting for response.
    dut->rst_ni = 0;
    dut->eval();

    expect(dut->req_ready_o == 1,
           "Reset must return CMO to idle");

    expect(dut->cache_req_valid_o == 0,
           "Reset must not produce a cache request");

    expect(dut->done_o == 0,
           "Reset must clear done");

    expect(dut->error_o == 0,
           "Reset must clear error");

    dut->rst_ni = 1;
    tick(dut);

    expect(dut->req_ready_o == 1,
           "CMO must be usable after reset");

    std::cout << "  PASS\n";
}

static void test_prefetch_no_response_wait(Vcmo_core* dut)
{
    std::cout << "[TEST] prefetch does not wait for response\n";

    reset_dut(dut);

    send_request(
        dut,
        0xB000,
        CmoOp::PREFETCH_R
    );

    expect(dut->cache_req_valid_o == 1,
           "Prefetch request must become valid");

    expect(dut->cache_req_addr_o == 0xB000,
           "Prefetch address must match request");

    expect(
        dut->cache_req_op_o ==
            static_cast<uint8_t>(CmoOp::PREFETCH_R),
        "Operation must be PREFETCH_R"
    );

    expect(dut->req_ready_o == 0,
           "CMO must be busy while prefetch request is pending");

    dut->cache_req_ready_i = 0;

    for (int i = 0; i < 3; ++i) {

        expect(dut->cache_req_valid_o == 1,
               "Prefetch valid must remain asserted during backpressure");

        expect(dut->cache_req_addr_o == 0xB000,
               "Prefetch address must remain stable");

        expect(
            dut->cache_req_op_o ==
                static_cast<uint8_t>(CmoOp::PREFETCH_R),
            "Prefetch operation must remain stable"
        );

        expect(dut->done_o == 0,
               "Prefetch cannot finish before request is accepted");

        tick(dut);
    }

    dut->cache_req_ready_i = 1;

    tick(dut);

    dut->cache_req_ready_i = 0;

    expect(dut->cache_req_valid_o == 0,
           "Prefetch request must disappear after acceptance");

    expect(dut->done_o == 1,
           "Prefetch must complete without waiting for response");

    expect(dut->error_o == 0,
           "Prefetch must not report an error");

    expect(dut->req_ready_o == 1,
           "CMO must return to idle after accepted prefetch");

    tick(dut);

    expect(dut->done_o == 0,
           "Prefetch done must be a one-cycle pulse");

    expect(dut->req_ready_o == 1,
           "CMO must remain ready after prefetch");

    std::cout << "  PASS\n";
}


int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    auto* dut = new Vcmo_core;

    std::cout << "CMO core unit tests\n";
    std::cout << "===================\n";

    test_reset(dut);
    test_basic_blocking_request(dut);
    test_cache_backpressure(dut);
    test_delayed_response(dut);
    test_error_response(dut);
    test_back_to_back_requests(dut);
    test_reset_while_busy(dut);
    test_operation_passthrough(dut);
    test_cache_ready_preasserted(dut);
    test_spurious_response_idle(dut);
    test_reset_while_waiting_response(dut);
    test_prefetch_no_response_wait(dut);

    std::cout << "===================\n";
    std::cout << "ALL TESTS PASSED\n";

    dut->final();
    delete dut;

    return 0;
}