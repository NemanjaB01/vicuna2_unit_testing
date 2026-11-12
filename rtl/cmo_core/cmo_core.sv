module cmo_core (
    input  logic        clk_i,
    input  logic        rst_ni,

    // Request from CPU/XIF wrapper.
    // All requests reaching this core are assumed to be committed
    // and therefore non-speculative
    // req_op_i is assumed to contain a supported CMO operation
    input  logic        req_valid_i,
    output logic        req_ready_o,
    input  logic [31:0] req_addr_i,
    input  logic [2:0]  req_op_i,

    // Request toward cache/memory system
    output logic        cache_req_valid_o,
    input  logic        cache_req_ready_i,
    output logic [31:0] cache_req_addr_o,
    output logic [2:0]  cache_req_op_o,

    // Response from cache/memory system.
    input  logic        cache_rsp_valid_i,
    input  logic        cache_rsp_error_i,

    // Completion of the memory-side CMO transaction.
    output logic        done_o,
    output logic        error_o
);

    typedef enum logic [2:0] {
        CMO_PREFETCH_R = 3'd0,
        CMO_PREFETCH_W = 3'd1,
        CMO_CLEAN      = 3'd2,
        CMO_FLUSH      = 3'd3,
        CMO_INVAL      = 3'd4,
        CMO_ZERO       = 3'd5
    } cmo_op_t;

    typedef enum logic [1:0] {
        IDLE,
        SEND_REQ,
        WAIT_RSP
    } state_t;

    state_t state_q;

    logic [31:0] addr_q;
    cmo_op_t     op_q;

    logic is_prefetch;

    assign is_prefetch =
        (op_q == CMO_PREFETCH_R) ||
        (op_q == CMO_PREFETCH_W);

    assign req_ready_o = (state_q == IDLE);

    assign cache_req_valid_o = (state_q == SEND_REQ);

    assign cache_req_addr_o = addr_q;
    assign cache_req_op_o   = op_q;

    always_ff @(posedge clk_i or negedge rst_ni) begin
        if (!rst_ni) begin
            state_q <= IDLE;
            addr_q  <= '0;
            op_q    <= CMO_PREFETCH_R;
            done_o  <= 1'b0;
            error_o <= 1'b0;
        end else begin

            done_o  <= 1'b0;
            error_o <= 1'b0;

            case (state_q)

                IDLE: begin
                    if (req_valid_i && req_ready_o) begin
                        addr_q  <= req_addr_i;
                        op_q    <= cmo_op_t'(req_op_i);
                        state_q <= SEND_REQ;
                    end
                end

                SEND_REQ: begin
                    if (cache_req_valid_o && cache_req_ready_i) begin

                        if (is_prefetch) begin
                            done_o  <= 1'b1;
                            error_o <= 1'b0;
                            state_q <= IDLE;
                        end

                        else begin
                            state_q <= WAIT_RSP;
                        end
                    end
                end

                WAIT_RSP: begin
                    if (cache_rsp_valid_i) begin
                        done_o  <= 1'b1;
                        error_o <= cache_rsp_error_i;
                        state_q <= IDLE;
                    end
                end

                default: begin
                    state_q <= IDLE;
                end

            endcase
        end
    end

endmodule