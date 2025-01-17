module PE(
  input         clock,
  input         reset,
  input  [7:0]  io_inA,
  input  [7:0]  io_inB,
  input  [31:0] io_inC,
  output [31:0] io_outC,
  input         io_switch,
  input         io_reset,
  output [31:0] io_debug_0,
  output [31:0] io_debug_1
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
  reg [31:0] _RAND_1;
`endif // RANDOMIZE_REG_INIT
  reg [31:0] out0; // @[sa.scala 18:21]
  reg [31:0] out1; // @[sa.scala 19:21]
  wire [15:0] mul = io_inA * io_inB; // @[sa.scala 22:20]
  wire [31:0] _GEN_0 = {{16'd0}, mul}; // @[sa.scala 24:50]
  wire [31:0] _out0_T_1 = out0 + _GEN_0; // @[sa.scala 24:50]
  wire [31:0] _out1_T_1 = out1 + _GEN_0; // @[sa.scala 25:58]
  assign io_outC = io_switch ? out1 : out0; // @[sa.scala 27:17]
  assign io_debug_0 = out0; // @[sa.scala 28:12]
  assign io_debug_1 = out1; // @[sa.scala 28:12]
  always @(posedge clock) begin
    if (reset) begin // @[sa.scala 18:21]
      out0 <= 32'h0; // @[sa.scala 18:21]
    end else if (io_reset) begin // @[sa.scala 24:14]
      out0 <= 32'h0;
    end else if (io_switch) begin // @[sa.scala 24:33]
      out0 <= _out0_T_1;
    end else begin
      out0 <= io_inC;
    end
    if (reset) begin // @[sa.scala 19:21]
      out1 <= 32'h0; // @[sa.scala 19:21]
    end else if (io_reset) begin // @[sa.scala 25:14]
      out1 <= 32'h0;
    end else if (io_switch) begin // @[sa.scala 25:33]
      out1 <= io_inC;
    end else begin
      out1 <= _out1_T_1;
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  out0 = _RAND_0[31:0];
  _RAND_1 = {1{`RANDOM}};
  out1 = _RAND_1[31:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
