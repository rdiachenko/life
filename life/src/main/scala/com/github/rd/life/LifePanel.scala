package com.github.rd.life

import scala.swing.Panel
import scala.swing.event.{MouseDragged, MousePressed, MouseReleased, MouseEvent}
import scala.actors.Actor
import scala.actors.Actor._

import java.awt.{Color, Dimension, Graphics2D}

class LifePanel(lifeActor: Actor) extends Panel {

  private val cellSize = 6
  private val cellGap = 1

  private val liveCellColor = new Color(0x505050)
  private val emptyCellColor = new Color(0xFFFFFF)

  private var rightBtnPressed = false
  private var leftBtnPressed = false

  override def background = Color.BLACK

  listenTo(mouse.clicks, mouse.moves)
  
  reactions += {
    case e: MouseDragged => processCell(e)
    case e: MousePressed =>
      if (e.peer.getButton == java.awt.event.MouseEvent.BUTTON1) {
        leftBtnPressed = true
        rightBtnPressed = false
        processCell(e)
      } else if (e.peer.getButton == java.awt.event.MouseEvent.BUTTON3) {
        leftBtnPressed = false
        rightBtnPressed = true
        processCell(e)
      }
    case e: MouseReleased =>
      if (e.peer.getButton == java.awt.event.MouseEvent.BUTTON1) {
        leftBtnPressed = false
      } else if (e.peer.getButton == java.awt.event.MouseEvent.BUTTON3) {
        rightBtnPressed = false
      }
  }

  override def preferredSize: Dimension = {
    val (height, width) = getDimension()
    new Dimension(
      (cellSize + cellGap) * width + cellGap,
      (cellSize + cellGap) * height + cellGap
    )
  }

  override def paint(g: Graphics2D) {
    super.paint(g)
    val (height, width) = getDimension()

    for (x <- 0 until height) {
      for (y <- 0 until width) {
        val live = getCell(x, y)
        g.setColor(
          if (live == 1) liveCellColor else emptyCellColor
        )
        g.fillRect(
          (cellSize + cellGap) * x + cellGap,
          (cellSize + cellGap) * y + cellGap,
          cellSize,
          cellSize
        )
      }
    }
  }

  def clear() {
    lifeActor ! "CLEAR"
    repaint
  }

  private def getDimension(): (Int, Int) = {
    lifeActor ! FieldDimension(Actor.self)
    val dimension = Actor.self.receive {
      case FieldDimensionRes(height, width) => FieldDimensionRes(height, width)
    }
    dimension match {
      case FieldDimensionRes(height, width) => (height, width)
      case _ => (100, 70)
    }
  }

  private def setCell(x: Int, y: Int, value: Byte) {
    lifeActor ! CellSetter(x, y, value)
  }

  private def getCell(x: Int, y: Int): Byte = {
    lifeActor ! CellGetter(x, y, Actor.self)
    val value = Actor.self.receive {
      case receivedValue: Byte => receivedValue
    }
    value
  }

  private def processCell(e: MouseEvent) {
    val x = e.point.x / (cellSize + cellGap)
    val y = e.point.y / (cellSize + cellGap)
    val (height, width) = getDimension()

    if (x >= 0 && x < height && y >= 0 && y < width) {
      if (rightBtnPressed) {
        setCell(x, y, 0)
        repaint
      }
      if (leftBtnPressed) {
        setCell(x, y, 1)
        repaint
      }
    }
  }
}
