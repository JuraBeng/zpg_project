#include "Engine.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>

int main(void)
{
	auto& gameEngine = Engine::get();
	gameEngine.render();
}
