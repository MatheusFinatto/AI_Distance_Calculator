#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <vector>

struct Place
{
    char name;
    int x;
    int y;
    int distanceFromOriginPlace;
    int euclideanDistanceToEnd;
    std::vector<Place> adjacentPlaces;
    Place *parent;
};

const int NUMBER_OF_PLACES = 7;
const int COORDINATES_LOWER_LIMIT = -100;
const int COORDINATES_UPPER_LIMIT = 100;
const char FIRST_PLACE = 'A';
const char LAST_PLACE = FIRST_PLACE + NUMBER_OF_PLACES - 1;

void getInputs(char &firstPlaceName, char &lastPlaceName);
void generatePlaces(std::vector<Place> &places);
void printPlaces(const std::vector<Place> &places);
bool isInputValid(char firstPlaceName, char lastPlaceName);
bool shouldContinue(char &finished);
float euclideanDistance(const Place &firstPlace, const Place &lastPlace);
void pathPrinter(char firstPlaceName, char lastPlaceName, std::vector<Place> &path);
void printEuclidianDistanceFromOriginToGoal(char firstPlaceName, char lastPlaceName, std::vector<Place> &places, int firstIndex, int lastIndex);

#endif
