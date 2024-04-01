

#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <vector>

const int NUMBER_OF_PLACES = 7;
const int COORDINATES_LOWER_LIMIT = -100;
const int COORDINATES_UPPER_LIMIT = 100;
const char FIRST_PLACE = 'A';
const char LAST_PLACE = FIRST_PLACE + NUMBER_OF_PLACES - 1;

struct Place
{
    char name;
    int x;
    int y;
    std::vector<Place> adjacentPlaces;
};

void getInputs(char &firstPlaceName, char &lastPlaceName);
void generatePlaces(std::vector<Place> &places);
void printPlaces(const std::vector<Place> &places);
bool isInputValid(char firstPlaceName, char lastPlaceName);
bool shouldContinue(char &finished);
float euclideanDistance(const Place &firstPlace, const Place &lastPlace);
float shortestPath(char firstPlaceName, char lastPlaceName);
std::vector<char> generatePathNodes(const std::vector<Place> &places, int firstIndex, int lastIndex);

#endif
