#include "stdafx.h"

#include "HeatWave.h"

#include "DirectedGraph.h"

#include <utility>
#include <vector>

#include "UnitTest++/UnitTest++.h"


// program entry
int main() {

	// run the game
	HeatWave* game = new HeatWave();
	game->start();

	return 0;
}