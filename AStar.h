#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include "functions.h"

std::vector<Place> AStar(const std::vector<Place> &places, char start, char end);
float shortestPath(char firstPlaceName, char lastPlaceName, const std::vector<Place> &places);

#endif