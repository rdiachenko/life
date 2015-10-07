#include <iostream>
#include <cstring>
#include "LifeModel.h"
#include "LifeApp.h"

using std::cout;
using std::endl;

void showHelp(char** argv)
{
	if (strcmp(argv[1], "-h") == 0)
	{
		cout << "Usage: " << endl
			<< "<MOUSE_LEFT_CLICK> - turn cell on" << endl
			<< "<MOUSE_RIGHT_CLICK> - turn cell off" << endl
			<< "<SPACE> - pause/resume" << endl
			<< "<ESC> - clear field" << endl;
	}
}

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		showHelp(argv);
		return 0;
	}
	else
	{
		LifeApp life;
		return life.execute();
	}
}
