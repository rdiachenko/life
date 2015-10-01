#include <iostream>
#include "LifeModel.h"

using std::cout;
using std::endl;

int LifeModel::getCell(int row, int col)
{
	int index = row * n + col;
	return frontField[index];
}

void LifeModel::setCellOn(int row, int col)
{
	setCell(row, col, 1);
}

void LifeModel::setCellOff(int row, int col)
{
	setCell(row, col, 0);
}

void LifeModel::setCell(int row, int col, int val)
{
	int index = row * n + col;
	frontField[index] = val;
}

void LifeModel::simulate()
{
	cout << "simultaion step started" << endl;

	for (int i = 0; i != n; i++)
	{
		int row = i * n;

		for (int j = 0; j != m; j++)
		{
			int neighboursCount = countNeighbours(i, j);
			int cellState = getCell(i, j);
			int index = row + j;

			if ((cellState == 0 && neighboursCount == 3)
					|| (cellState > 0 && (neighboursCount == 2 || neighboursCount == 3)))
			{
				backField[index] = 1;
			}
			else
			{
				backField[index] = 0;
			}
		}
	}
	swapFields();

	cout << "simultaion step finished" << endl;
}

int LifeModel::countNeighbours(int row, int col)
{
	static const int offsetsCount = 8;
	static const int offsets[offsetsCount][2] = 
	{
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1}
	};
	int count = 0;

	for (int k = 0; k != offsetsCount; k++)
	{
		int i = row + offsets[k][0];
		int j = col + offsets[k][1];

		if (i >= 0 && i < n && j >= 0 && j < m)
		{
			count += getCell(i, j);
		}
	}
	return count;
}

void LifeModel::swapFields()
{
	int* temp = frontField;
	frontField = backField;
	backField = temp;
}

void LifeModel::clear()
{
	for (int i = 0; i != n; i++)
	{
		int row = i * n;

		for (int j = 0; j != m; j++)
		{
			int index = row + j;
			frontField[index] = 0;
			backField[index] = 0;
		}
	}
}
