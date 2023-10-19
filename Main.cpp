
#include <iostream>
#include "Models.h"
#include "Views.h"
#include <string>
#include "Controllers.h"
using namespace std;

int main()
{
	Controllers c;
	c.setConsoleWindow(1450, 735);
	SetConsoleTitle(L"Game Caro Chess");
	c.loopGame();
	return 0;
}


	