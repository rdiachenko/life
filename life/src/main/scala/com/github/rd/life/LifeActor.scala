package com.github.rd.life

import scala.actors.Actor
import scala.actors.Actor._

case class CellSetter(x: Int, y: Int, value: Byte)
case class CellGetter(x: Int, y: Int, respondTo: Actor)
case class FieldDimension(respondTo: Actor)
case class FieldDimensionRes(
  height: Int,
  width: Int
)
case class Cmd(cmdCode: String, respondTo: Actor)
case class DelayTime(time: Int)

class LifeActor(model: LifeModel) extends Actor {

  private var simulation = false

  private var sleepTime = 100

  start()

  def act() {
    loop {
      react {
        case CellSetter(x, y, value) =>
          model.setCell(x, y, value)
        case CellGetter(x, y, actor) =>
          actor ! model.getCell(x, y)
        case Cmd("CLEAR", actor) =>
          model.clear()
        case FieldDimension(actor) =>
          actor ! FieldDimensionRes(model.getHeight(), model.getWidth())
        case Cmd("SIMULATE", actor) =>
          if (simulation) {
            model.simulate()
            actor ! "ON"
            sleep(sleepTime, actor)
          }
        case Cmd("STOP", actor) =>
          simulation = false
          actor ! "OFF"
        case Cmd("START", actor) =>
          simulation = true
          actor ! "ON"
          self ! Cmd("SIMULATE", actor)
        case DelayTime(time) =>
          sleepTime = time
      }
    }
  }

  private def sleep(time: Int, other: Actor) {
    val mainActor = self
    actor {
      Thread.sleep(time)
      mainActor ! Cmd("SIMULATE", other)
    }
  }
}
