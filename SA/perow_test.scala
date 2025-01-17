package sa

import org.scalatest._
import chiseltest._
import chisel3._
import chisel3.util._
import scala.collection.mutable.ArrayBuffer
import scala.util.Random

class PErow_Test extends FlatSpec with ChiselScalatestTester with Matchers {
  behavior of "PErow"
  it should "produce right output" in {
    //Add your own functions here
    //Add your own values here
    val rowL = 4
    val width = 8
    test(new PErow(rowL,width)) { c =>
      // Prepare Data
      val epoch = 3
      val length = 16
      
      val test_W = for (i <- 1 to length) yield Random.nextInt(16)
      val test_I = for (i <- 0 until rowL) yield for (j <- 1 to length) yield Random.nextInt(16)
      
      var answer =  test_I.map(row => (row zip test_W).map { case (a, b) => a * b }.sum)
      
      // Set Up
      var look = 0
      var switch = true

      c.io.reset.poke(true.B)
      c.clock.step(1) 
      c.io.reset.poke(false.B)

      c.io.switch.poke(switch.B)
      c.io.inC.poke(0.U)

      // Runtime
      
      var move = 0
      var step = 0
      var loop = 0
      val total = length * epoch

      var inB = 0
      var inA:  ArrayBuffer[Int] = ArrayBuffer()

      for (cycle <- 0 until total + rowL) {

        step = cycle % length
        loop = cycle / length 

        if (step == 0 && cycle > 0) {
          switch = !switch
          c.io.switch.poke(switch.B)
          
          //println(s"Iter[$loop] End, have to be $answer \n")
          answer = answer.tail :+ answer.head
        }
        
        if (cycle < total) {
          /*
          c.io.inB.poke(test_W(step).U)
          
          for (pe <- 0 until rowL) {
            val rotate = (pe + move)%rowL
            c.io.inA(pe).poke(test_I(rotate)(step).U)
          }
          */
          inB = test_W(step)
          inA = ArrayBuffer(test_I.map(row => row(step)): _*)
        }
        else {
          /*
          c.io.inB.poke(0.U)
          for(pe <- 0 until rowL)
            c.io.inA(pe).poke(0.U)
          */
          inB = 0
          inA = ArrayBuffer.fill(rowL)(0)
        }
        
        c.io.inB.poke(inB.U)
        for(pe <- 0 until rowL) {
          val rotate = (pe + loop)%rowL
          c.io.inA(pe).poke(inA(rotate).U)
        }
      
        look = c.io.outC.peek().litValue.toInt

        c.clock.step(1) // 한 사이클 진행 후 출력 확인

        val pes = for (pe <- 0 until rowL) yield (c.io.debug(pe).map(_.peek().litValue.toInt)).mkString(",")
        
   
        //println(s"Cycle $cycle: In = [$inB|${inA.mkString(",")}] : reg = [${pes.mkString("][")}] : out = [$look]")
        
      }
    }
  }
}
