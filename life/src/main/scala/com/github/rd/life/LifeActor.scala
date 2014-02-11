package com.github.rd.life

import scala.actors.Actor

case class CellSetter(x: Int, y: Int, value: Byte)
case class CellGetter(x: Int, y: Int, respondTo: Actor)
case class FieldDimension(respondTo: Actor)
case class FieldDimensionRes(
  height: Int,
  width: Int
)

class LifeActor(model: LifeModel) extends Actor {

  start()

  def act() {
    loop {
      react {
        case CellSetter(x, y, value) =>
          model.setCell(x, y, value)
        case CellGetter(x, y, actor) =>
          actor ! model.getCell(x, y)
        case "CLEAR" =>
          model.clear()
        case FieldDimension(actor) =>
          actor ! FieldDimensionRes(model.getHeight(), model.getWidth())
      }
    }
  }
}
