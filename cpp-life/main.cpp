#include <iostream>
#include "LifeModel.h"

using namespace std;

void println(LifeModel& model)
{
	for (int i = 0; i != 7; i++)
	{
		for (int j = 0; j != 7; j++)
		{
			cout << model.getCell(i, j);
		}
		cout << endl;
	}
}

int main()
{
	int width = 7;
	int height = 7;
	LifeModel model(width, height);
	model.setCellOn(2, 2);
	model.setCellOn(2, 3);
	model.setCellOn(2, 1);

	println(model);
	model.simulate();
	println(model);
	model.simulate();
	println(model);
	return 0;
}
