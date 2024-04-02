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
    }
    for (int i = 0; i < NUMBER_OF_PLACES; i++)
    {
        for (int j = 0; j < places[i].adjacentPlaces.size(); j++)
        {
            places[i].adjacentPlaces[j].distanceFromOriginPlace = euclideanDistance(places[i], places[i].adjacentPlaces[j]);
        }
    }
}

void printPlaces(const std::vector<Place> &places)
{
    std::cout << "List of places: " << std::endl;

    std::cout
        << "----------------------------------------------" << std::endl;
    std::cout << std::setw(5) << "Name" << std::setw(10) << "X" << std::setw(10) << "Y" << std::setw(20) << "Adjacent places" << std::setw(25) << "Distance from origin" << std::endl;

    for (const Place &place : places)
    {
        std::cout << std::setw(5) << place.name << std::setw(10) << place.x << std::setw(10) << place.y << std::setw(6);

        if (place.adjacentPlaces.size() != 0)
        {
            for (const Place &adjacent : place.adjacentPlaces)
                std::cout << adjacent.name << " ";
        }

        for (int i = 0; i < place.adjacentPlaces.size(); i++)
        {

            std::cout << std::setw(20) << place.adjacentPlaces[i].distanceFromOriginPlace;
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

void printEuclidianDistanceFromOriginToGoal(char firstPlaceName, char lastPlaceName, std::vector<Place> &places, int firstIndex, int lastIndex)
{
    std::cout << std::endl
              << "Euclidean distance between places " << firstPlaceName << " and " << lastPlaceName
              << " is: " << std::endl
              << euclideanDistance(places[firstIndex], places[lastIndex]) << std::endl
              << std::endl;
}

void pathPrinter(char firstPlaceName, char lastPlaceName, std::vector<Place> &path)
{
    std::cout << "Path from " << firstPlaceName << " to " << lastPlaceName << " is: " << std::endl;
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i].name;
        if (i != path.size() - 1)
        {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl
              << std::endl;
}
