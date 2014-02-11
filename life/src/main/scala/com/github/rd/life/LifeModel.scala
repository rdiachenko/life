package com.github.rd.life

/*object LifeModel extends App {
  val model = new LifeModel(3, 3)
  model.setCell(1, 0, 1)
  model.setCell(1, 1, 1)
  model.setCell(1, 2, 1)
  printModel

  model.simulate
  printModel
  model.simulate
  printModel
  model.simulate
  printModel

  model.clear
  printModel

  def printModel {
    for (i <- 0 until 3) {
      for (j <- 0 until 3) {
        print(model.getCell(i, j))
      }
      println
    }
    println
  }
}*/

class LifeModel(height: Int, width: Int) {

  private var mainField = Array.fill[Byte](height, width)(0)
  private var backField = Array.fill[Byte](height, width)(0)
  private val neighborsOffsets = Array(
    Array(-1, -1),
    Array(-1, 0),
    Array(-1, 1),
    Array(0, -1),
    Array(0, 1),
    Array(1, -1),
    Array(1, 0),
    Array(1, 1)
  )
  
  def getHeight() = height
  def getWidth() = width

  def setCell(x: Int, y: Int, value: Byte) {
    mainField(x)(y) = value
  }

  def getCell(x: Int, y: Int): Byte = mainField(x)(y)

  def simulate {
    for (x <- 0 until height) {
      for (y <- 0 until width) {
        val neighborsCount = countNeighbors(x, y)
        backField(x)(y) = simulateCell(mainField(x)(y), neighborsCount)
      }
    }
    mainField = for (line <- backField) yield {
      for (elem <- line) yield elem
    }
    backField = Array.fill[Byte](height, width)(0)
  }

  def clear() {
    mainField = Array.fill[Byte](height, width)(0)
    backField = Array.fill[Byte](height, width)(0)
  }
  
  private def countNeighbors(x: Int, y: Int): Int = {
    //def normalizeXY(value: Int, bound: Int): Int = {
    //  if (value == bound) 0
    //  else if (value < 0) bound - 1
    //  else value
    //}
    var count = 0

    for (offsets <- neighborsOffsets) {
      //val xOffset = normalizeXY(x + offsets(0), height)
      //val yOffset = normalizeXY(y + offsets(1), width)
      //count += mainField(xOffset)(yOffset)
      
      val xOffset = x + offsets(0)
      val yOffset = y + offsets(1)
      if (xOffset >= 0 && xOffset < height && yOffset >= 0 && yOffset < width) count += mainField(xOffset)(yOffset)
    }
    count
  }

  private def simulateCell(state: Byte, neighbors: Int): Byte = {
    if (state == 0) if (neighbors == 3) 1 else 0
    else if (neighbors < 2 || neighbors > 3) 0 else 1
  }
}
