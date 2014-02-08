package com.github.rd.life

import scala.swing.Panel
import scala.swing.event.{MouseDragged, MousePressed, MouseReleased, MouseEvent}

import java.awt.{Color, Dimension, Graphics2D}

class LifePanel(model: LifeModel) extends Panel {

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
    new Dimension(
      (cellSize + cellGap) * model.getWidth + cellGap,
      (cellSize + cellGap) * model.getHeight + cellGap
    )
  }

  override def paint(g: Graphics2D) {
    super.paint(g)
    for (x <- 0 until model.getHeight) {
      for (y <- 0 until model.getWidth) {
        val live = model.getCell(x, y)
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

  private def processCell(e: MouseEvent) {
    val x = e.point.x / (cellSize + cellGap)
    val y = e.point.y / (cellSize + cellGap)

    if (x >= 0 && x < model.getHeight && y >= 0 && y < model.getWidth) {
      if (rightBtnPressed) {
        model.setCell(x, y, 0)
        repaint
      }
      if (leftBtnPressed) {
        model.setCell(x, y, 1)
        repaint
      }
    }
  }
}
