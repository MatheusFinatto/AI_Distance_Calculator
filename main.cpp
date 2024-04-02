#include <iostream>
#include <algorithm>
#include "functions.h"
#include "AStar.h"

int main()
{
    char finished = 'N';
    char firstPlaceName = ' ';
    char lastPlaceName = ' ';
    std::vector<Place> places(NUMBER_OF_PLACES);

    generatePlaces(places);

    do
    {
        printPlaces(places);

        getInputs(firstPlaceName, lastPlaceName);

        if (isInputValid(firstPlaceName, lastPlaceName))
        {
            int firstIndex = firstPlaceName - FIRST_PLACE;
            int lastIndex = lastPlaceName - FIRST_PLACE;

            printEuclidianDistanceFromOriginToGoal(firstPlaceName, lastPlaceName, places, firstIndex, lastIndex);

            // Use shortestPath to find the total distance of the shortest path
            float distance = shortestPath(firstPlaceName, lastPlaceName, places);

            // Print the total distance
            std::cout << "Shortest path distance from " << firstPlaceName << " to " << lastPlaceName << " is: " << distance << std::endl;

            // Use AStar algorithm to find the shortest path
            std::vector<Place> path = AStar(places, firstPlaceName, lastPlaceName);

            // Print the path
            pathPrinter(firstPlaceName, lastPlaceName, path);
        }

    } while (shouldContinue(finished));

    return 0;
}
