package sa

import chisel3._
import chisel3.util._

class PE(val width: Int) extends Module {
  val io = IO(new Bundle {
    val inA = Input(UInt(width.W))   // 입력 입력값
    val inB = Input(UInt(width.W))   // 입력 가중치
    val inC = Input(UInt(32.W))   // 입력 합산 값
    val outC = Output(UInt(32.W)) // 다음 PE로 전달될 완성된 출력값
    val switch = Input(Bool())    // Double Buffer 스위치 신호
    val reset = Input(Bool())     // register reset
    
    val debug = Output(Vec(2,UInt(32.W)))
  })
  // 두 개의 출력 레지스터
  val out0 = RegInit(0.U(32.W))
  val out1 = RegInit(0.U(32.W))

  // Multiply and Accumulate
  val mul = io.inA * io.inB

  out0 := Mux(io.reset, 0.U, Mux(io.switch, out0 + mul, io.inC))
  out1 := Mux(io.reset, 0.U, Mux(io.switch, io.inC, out1 + mul))

  io.outC := Mux(io.switch, out1, out0)
  io.debug := Seq(out0, out1)
}

class PErow(val rowL: Int, val width: Int) extends Module {
  val io = IO(new Bundle {
    val inA = Input(Vec(rowL, UInt(width.W)))  // "rowL"개의 입력값
    val inB = Input(UInt(width.W))  // 1개의 가중치
    val inC = Input(UInt(32.W))   // 입력 합산 값
    val outC = Output(UInt(32.W)) // 전달되는 합산값
    val switch = Input(Bool())    // Double Buffer 스위치 신호
    val reset = Input(Bool())     // register reset
    val debug = Output(Vec(rowL, Vec(2, UInt(32.W))))
  })

  // 2D Array of Processing Elements
  val perow = Seq.fill(rowL)(Module(new PE(width)))

  // Connect inputs to PEs and outputs

  for (i <- 0 until rowL) {
    perow(i).io.inA := io.inA(i)  // 행 단위로 inA 연결
    perow(i).io.inB := io.inB       // 열 단위로 inB 연결

    if (i > 0){ 
      perow(i - 1).io.inC := perow(i).io.outC  // 이전 PE의 출력 연결
      if (i == rowL-1)
        perow(i).io.inC := io.inC
    }
    else
      io.outC := perow(i).io.outC

    perow(i).io.switch := io.switch
    perow(i).io.reset := io.reset

    io.debug(i)(0) := perow(i).io.debug(0)
    io.debug(i)(1) := perow(i).io.debug(1)
  }
}

class Tile(val rowL: Int, val colL: Int, val width: Int) extends Module {
  val io = IO(new Bundle {
    val inA = Input(Vec(rowL, UInt(width.W)))  // "rowL"개의 입력값
    val inB = Input(Vec(colL, UInt(width.W)))  // 1개의 가중치
    val inC = Input(Vec(colL, UInt(32.W)))   // 입력 합산 값
    val outC = Output(Vec(colL, UInt(32.W))) // 전달되는 합산값
    val switch = Input(Bool())    // Double Buffer 스위치 신호
    val reset = Input(Bool())     // register reset
  })

  // 2D Array of Processing Elements
  val tile = Seq.fill(colL)(Module(new PErow(rowL, width)))

  for (i <- 0 until rowL) {
    tile(0).io.inA := io.inA(i)  // 행 단위로 inA 연결
  }
  
  for (i <- 0 until colL){
    tile(i).io.inB := io.inB(i)       // 열 단위로 inB 연결

    tile(i).io.switch := io.switch
    tile(i).io.reset := io.reset

    io.outC(i) := tile(i).io.outC
    tile(i).io.inC := io.inC(i)
  }
}

class SA(val rowL: Int, val colL: Int, val bit: Int) extends Module {
  val io = IO(new Bundle {
    val writeA = Input(Vec(64/bit, UInt(bit.W)))
    val writeB = Input(Vec(64/bit, UInt(bit.W)))
    val inA = Input(Vec(rowL, UInt(bit.W)))  // "rowL"개의 입력값
    val inB = Input(Vec(colL, UInt(bit.W)))  // 1개의 가중치
    val inC = Input(Vec(colL, UInt(32.W)))   // 입력 합산 값
    val outC = Output(Vec(colL, UInt(32.W))) // 전달되는 합산값
    val switch = Input(Bool())    // Double Buffer 스위치 신호
    val reset = Input(Bool())     // register reset
  })

  // 2D Array of Processing Elements
  val tile = Seq.fill(colL)(Module(new PErow(rowL, width)))

  for (i <- 0 until rowL) {
    tile(0).io.inA := io.inA(i)  // 행 단위로 inA 연결
  }
  
  for (i <- 0 until colL){
    tile(i).io.inB := io.inB(i)       // 열 단위로 inB 연결

    tile(i).io.switch := io.switch
    tile(i).io.reset := io.reset

    io.outC(i) := tile(i).io.outC
    tile(i).io.inC := io.inC(i)
  }
}


// Top-Level 모듈

//object SystolicArrayMain extends App {
//  (new chisel3.stage.ChiselStage).emitVerilog(new PE(8), Array("--target-dir", "/home/harry09119/chisel/src/main/scala/SA/verilog"))
//}


