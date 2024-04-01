#include "functions.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>

void generatePlaces(std::vector<Place> &places)
{
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_PLACES; i++)
    {
        places[i].name = FIRST_PLACE + i;
        places[i].x = rand() % (COORDINATES_UPPER_LIMIT - COORDINATES_LOWER_LIMIT + 1) + COORDINATES_LOWER_LIMIT;
        places[i].y = rand() % (COORDINATES_UPPER_LIMIT - COORDINATES_LOWER_LIMIT + 1) + COORDINATES_LOWER_LIMIT;
    }

    for (int i = 0; i < NUMBER_OF_PLACES; i++)
    {

        switch (places[i].name)
        {
        case 'A':
            places[i].adjacentPlaces.push_back(places[1]); // B
            places[i].adjacentPlaces.push_back(places[2]); // C
            break;
        case 'B':
            places[i].adjacentPlaces.push_back(places[0]); // A
            places[i].adjacentPlaces.push_back(places[5]); // F
            break;
        case 'C':
            places[i].adjacentPlaces.push_back(places[0]); // A
            places[i].adjacentPlaces.push_back(places[3]); // D
            break;
        case 'D':
            places[i].adjacentPlaces.push_back(places[2]); // C
            places[i].adjacentPlaces.push_back(places[4]); // E
            places[i].adjacentPlaces.push_back(places[5]); // F
            break;
        case 'E':
            places[i].adjacentPlaces.push_back(places[3]); // D
            places[i].adjacentPlaces.push_back(places[4]); // E
            places[i].adjacentPlaces.push_back(places[5]); // F
            places[i].adjacentPlaces.push_back(places[6]); // G
            break;
        case 'F':
            places[i].adjacentPlaces.push_back(places[1]); // B
            places[i].adjacentPlaces.push_back(places[3]); // D
            places[i].adjacentPlaces.push_back(places[6]); // G

            break;
        case 'G':
            places[i].adjacentPlaces.push_back(places[4]); // E
            places[i].adjacentPlaces.push_back(places[5]); // F
            break;
        default:
            break;
        }

        // Random
        // int numAdjacent = rand() % 4 + 1;
        // std::vector<int> chosenIndices;
        // for (int j = 0; j < numAdjacent; j++)
        // {
        //     int randomIndex;
        //     do
        //     {
        //         randomIndex = rand() % NUMBER_OF_PLACES;
        //     } while (randomIndex == i || std::find(chosenIndices.begin(), chosenIndices.end(), randomIndex) != chosenIndices.end());
        //     // Ensure not selecting the same place or previously chosen place

        //     chosenIndices.push_back(randomIndex);                    // Mark this index as chosen
        //     places[i].adjacentPlaces.push_back(places[randomIndex]); // Add the adjacent place to the current place's adjacentPlaces vector
        // }

        // Print adjacent places
        // std::cout << "Adjacent places of " << places[i].name << " are: ";
        // for (int j = 0; j < places[i].adjacentPlaces.size(); j++)
        // {
        //     std::cout << places[i].adjacentPlaces[j].name;
        //     if (j != places[i].adjacentPlaces.size() - 1)
        //     {
        //         std::cout << ", ";
        //     }
        // }
        // std::cout << std::endl;
    }
}

void printPlaces(const std::vector<Place> &places)
{
    std::cout << "List of places: " << std::endl;

    std::cout
        << "----------------------------------------------" << std::endl;
    std::cout << std::setw(5) << "Name" << std::setw(10) << "X" << std::setw(10) << "Y" << std::setw(20) << "Adjacent places" << std::endl;

    for (const Place &place : places)
    {
        std::cout << std::setw(5) << place.name << std::setw(10) << place.x << std::setw(10) << place.y << std::setw(6);

        if (place.adjacentPlaces.size() != 0)
        {
            for (const Place &adjacent : place.adjacentPlaces)
                std::cout << adjacent.name << " ";
        }
        else
        {
            std::cout << "";
        }

        std::cout << std::endl;
    }

    std::cout << "----------------------------------------------" << std::endl
              << std::endl;
}

bool shouldContinue(char &finished)
{
    std::cout << "Do you want to test again? Y/N: ";
    std::cin >> finished;

    return (finished == 'Y' || finished == 'y');
}

float euclideanDistance(const Place &firstPlace, const Place &lastPlace)
{
    return std::sqrt(std::pow(lastPlace.x - firstPlace.x, 2) + std::pow(lastPlace.y - firstPlace.y, 2));
}

bool isInputValid(char firstPlaceName, char lastPlaceName)
{
    if (firstPlaceName < FIRST_PLACE || firstPlaceName > LAST_PLACE || lastPlaceName < FIRST_PLACE || lastPlaceName > LAST_PLACE)
    {
        std::cout << "The places entered are not valid; Use letters from " << FIRST_PLACE << " to " << LAST_PLACE << std::endl;
        return false;
    }

    if (firstPlaceName == lastPlaceName)
    {
        std::cout << "The first place must be different from the last" << std::endl;
        return false;
    }

    return true;
}

void getInputs(char &firstPlaceName, char &lastPlaceName)
{
    std::cout << "Choose the starting place: ";
    std::cin >> firstPlaceName;
    std::cout << "Choose the ending place: ";
    std::cin >> lastPlaceName;

    firstPlaceName = toupper(firstPlaceName);
    lastPlaceName = toupper(lastPlaceName);
}

float shortestPath(char firstPlaceName, char lastPlaceName)
{
    return 10.0;
}

std::vector<char> generatePathNodes(const std::vector<Place> &places, int firstIndex, int lastIndex)
{
    return std::vector<char>({'A', 'B', 'C', 'D', 'E', 'F', 'G'});
}