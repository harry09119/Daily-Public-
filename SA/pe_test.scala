package sa

import org.scalatest._
import chiseltest._
import chisel3._
import chisel3.util._

class PE_Test extends FlatSpec with ChiselScalatestTester with Matchers {
  behavior of "PE"
  it should "produce right output" in {
    //Add your own functions here
    //Add your own values here
    test(new PE(8)) { c =>
      // Prepare Data
      val iter = 10
      val test_W = for (i <- 1 to iter) yield i
      val test_I1 = for (i <- 1 to iter) yield i
      val test_I2 = for (i <- iter + 1 to iter * 2) yield i

      val answer1 = (test_W zip test_I1).map { case (a, b) => a * b }.sum
      val answer2 = (test_W zip test_I2).map { case (a, b) => a * b }.sum

      var look = 0

      // Set Up
      var switch = true
      c.io.reset.poke(true.B)
      c.clock.step(1) // reset 활성화
      c.io.reset.poke(false.B) // reset 비활성화
      c.io.switch.poke(switch.B)
      c.io.inC.poke(0.U)

      // Runtime
      for (cycle <- 0 to iter * 2) {
        if (cycle < iter) {
          c.io.inA.poke(test_W(cycle).U)
          c.io.inB.poke(test_I1(cycle).U)
        } else if (cycle >= iter && cycle < iter*2) {
          c.io.inA.poke(test_W(cycle - iter).U)
          c.io.inB.poke(test_I2(cycle - iter).U)
        } 
        
        if ((cycle) % iter == 0) {
          switch = !switch
          c.io.switch.poke(switch.B)
        }
        
        look = c.io.outC.peek().litValue.toInt
        val out0 = c.io.debug(0).peek().litValue.toInt
        val out1 = c.io.debug(1).peek().litValue.toInt

        c.clock.step(1) // 한 사이클 진행 후 출력 확인
      
        println(s"Cycle $cycle: reg = [$out0, $out1] : out = [$look]")
        
        if ((cycle) % iter == 0) {
          val end = cycle / iter
          if (end == 1)
            println(s"Iter[$end] End, have to be $answer1 \n")
          if (end == 2)
            println(s"Iter[$end] End, have to be $answer2 \n")
        }
      }
      //println(s"Iter[2] End, have to be $answer2\n")
    }
  }
}
