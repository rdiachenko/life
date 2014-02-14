package com.github.rd.life

import scala.swing.{SimpleSwingApplication, MainFrame, BoxPanel, 
                    Orientation, Button, Slider, Swing, Label}
import scala.swing.event.{ButtonClicked, ValueChanged}
import java.awt.Dimension

object LifeApp extends SimpleSwingApplication {

  def top = new MainFrame {
    title = "Life"

    val lifeActor = new LifeActor(new LifeModel(100, 70))
    val lifePanel = new LifePanel(lifeActor)
    
    val toolBar = new BoxPanel(Orientation.Horizontal) {
      val stateBtn = new Button {
        text = "Start life"
      }

      val slider = new Slider {
        tooltip = "Life speed"
        min = 1
        max = 200
        value = 100
        labels = Map(1 -> new Label("1"), 200 -> new Label("200"))
        paintLabels = true
        border = Swing.EmptyBorder(0, 10, 0, 15)
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
        case ButtonClicked(`stateBtn`) =>
          if (lifePanel.isSimulation) {
            stateBtn.text = "StartLife"
            lifePanel stopSimulation
          } else {
            stateBtn.text = "StopLife"
            lifePanel startSimulation
          }
        case ButtonClicked(`clearBtn`) => lifePanel clear
        case ValueChanged(`slider`) => lifePanel updateDelay(slider.value)
      }
    } 

    contents = new BoxPanel(Orientation.Vertical) {
      contents += toolBar
      contents += lifePanel
    }
    minimumSize = new Dimension(704, 574)
  }
}
