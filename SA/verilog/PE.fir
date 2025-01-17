;buildInfoPackage: chisel3, version: 3.4.1, scalaVersion: 2.12.12, sbtVersion: 1.3.10
circuit PE : 
  module PE : 
    input clock : Clock
    input reset : UInt<1>
    output io : {flip inA : UInt<8>, flip inB : UInt<8>, flip inC : UInt<32>, outC : UInt<32>, flip switch : UInt<1>, flip reset : UInt<1>, debug : UInt<32>[2]}
    
    reg out0 : UInt<32>, clock with : (reset => (reset, UInt<32>("h00"))) @[sa.scala 18:21]
    reg out1 : UInt<32>, clock with : (reset => (reset, UInt<32>("h00"))) @[sa.scala 19:21]
    node mul = mul(io.inA, io.inB) @[sa.scala 22:20]
    node _out0_T = add(out0, mul) @[sa.scala 24:50]
    node _out0_T_1 = tail(_out0_T, 1) @[sa.scala 24:50]
    node _out0_T_2 = mux(io.switch, _out0_T_1, io.inC) @[sa.scala 24:33]
    node _out0_T_3 = mux(io.reset, UInt<1>("h00"), _out0_T_2) @[sa.scala 24:14]
    out0 <= _out0_T_3 @[sa.scala 24:8]
    node _out1_T = add(out1, mul) @[sa.scala 25:58]
    node _out1_T_1 = tail(_out1_T, 1) @[sa.scala 25:58]
    node _out1_T_2 = mux(io.switch, io.inC, _out1_T_1) @[sa.scala 25:33]
    node _out1_T_3 = mux(io.reset, UInt<1>("h00"), _out1_T_2) @[sa.scala 25:14]
    out1 <= _out1_T_3 @[sa.scala 25:8]
    node _io_outC_T = mux(io.switch, out1, out0) @[sa.scala 27:17]
    io.outC <= _io_outC_T @[sa.scala 27:11]
    io.debug[0] <= out0 @[sa.scala 28:12]
    io.debug[1] <= out1 @[sa.scala 28:12]
    
