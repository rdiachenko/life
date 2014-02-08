package com.github.rd.life

import scala.swing.{SimpleSwingApplication, MainFrame, BoxPanel, 
                    Orientation, Button, Slider, Swing, Label}
import scala.swing.event.{ButtonClicked, ValueChanged}
import java.awt.Dimension

object LifeApp extends SimpleSwingApplication {

  def top = new MainFrame {
    title = "Life"

    val toolBar = new BoxPanel(Orientation.Horizontal) {
      val stateBtn = new Button {
        text = "Start life"
      }

      val slider = new Slider {
        tooltip = "Life speed"
        min = 1
        max = 200
        value = 50
        labels = Map(1 -> new Label("1"), 200 -> new Label("200"))
        paintLabels = true
        border = Swing.EmptyBorder(0, 10, 0, 15)
       // paintTicks = true
      //  paintTrack = true
      }

      val clearBtn = new Button {
        text = "Clear field"
      }
      
      contents += stateBtn
      contents += slider
      contents += clearBtn

      border = Swing.EmptyBorder(5, 5, 5, 5)

      listenTo(stateBtn, slider, clearBtn)
      reactions += {
        case ButtonClicked(`stateBtn`) => println("stateBtn")
        case ButtonClicked(`clearBtn`) => println("clearBtn")
        case ValueChanged(`slider`) => println("slider: " + slider.value)
      }
    }
    
    val lifePanel = new LifePanel(new LifeModel(100, 70))

    contents = new BoxPanel(Orientation.Vertical) {
      contents += toolBar
      contents += lifePanel
    }
    minimumSize = new Dimension(704, 574)
  }
}
