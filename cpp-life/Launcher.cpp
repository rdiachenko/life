#include <iostream>
#include "LifeModel.h"

using namespace std;

int main()
{
	int width = 7;
	int height = 7;
	LifeModel model(width, height);
	model.simulate();
	return 0;
}
