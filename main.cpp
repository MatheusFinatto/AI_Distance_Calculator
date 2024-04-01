#include <iostream>
#include "functions.h"

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

            std::cout << std::endl
                      << "Euclidean distance between places " << firstPlaceName << " and " << lastPlaceName
                      << " is: " << std::endl
                      << euclideanDistance(places[firstIndex], places[lastIndex]) << std::endl
                      << std::endl;

            std::vector<char> path = generatePathNodes(places, firstIndex, lastIndex);

            std::cout << "Shortest path distance from " << firstPlaceName << " to " << lastPlaceName << " is: " << shortestPath(firstPlaceName, lastPlaceName) << std::endl;

            ;
            std::cout << "Path from " << firstPlaceName << " to " << lastPlaceName << " is: ";
            for (int i = 0; i < path.size(); i++)
            {
                std::cout << path[i];
                if (i != path.size() - 1)
                {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl
                      << std::endl;
        }

    } while (shouldContinue(finished));

    return 0;
}
