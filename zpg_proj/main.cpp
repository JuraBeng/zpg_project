
#include "Engine.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>


int main(void)
{
	auto& gameEngine = Engine::Get();
	gameEngine.Render();
}
