#include "../include/gameCore.h"

#define __DEBUG_MODE__

int main(int argc, char **argv)
{
	gameCore tanks;
	tanks.Init(800,600,32);
	tanks.Start();
	return 0;
}
