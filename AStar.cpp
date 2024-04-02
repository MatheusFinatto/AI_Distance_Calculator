#include <iostream>
#include <algorithm>
#include "functions.h"

std::vector<Place> AStar(const std::vector<Place> &places, char start, char end)
{
    // Convert start and end characters to indices based on a predefined constant FIRST_PLACE
    int startIndex = start - FIRST_PLACE;
    int endIndex = end - FIRST_PLACE;

    // Lists to keep track of nodes to be evaluated and already evaluated
    std::vector<Place> openList;
    std::vector<Place> closedList;

    // Start with the starting point in the open list
    openList.push_back(places[startIndex]);

    // Continue searching until there are no more nodes to evaluate
    while (!openList.empty())
    {
        // Find the node with the lowest fCost (distanceFromOriginPlace + euclideanDistanceToEnd)
        auto currentNode = openList.begin();
        for (auto it = openList.begin() + 1; it != openList.end(); ++it)
        {
            // Update currentNode if this node has a lower fCost
            if (it->distanceFromOriginPlace + it->euclideanDistanceToEnd < currentNode->distanceFromOriginPlace + currentNode->euclideanDistanceToEnd)
            {
                currentNode = it;
            }
        }

        // Move the currentNode from open list to closed list
        closedList.push_back(*currentNode);
        openList.erase(currentNode);

        // If the current node is the target, build the path by following parent pointers
        if (currentNode->name == end)
        {
            std::vector<Place> path;
            const Place *pathNode = &(*currentNode);
            while (pathNode != nullptr)
            {
                path.push_back(*pathNode);
                pathNode = pathNode->parent; // Move to the parent node
            }
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            return path;
        }

        // Explore the neighbors of the current node
        for (Place &adjacentPlace : currentNode->adjacentPlaces)
        {
            // Skip if this neighbor is already in the closed list
            if (std::find_if(closedList.begin(), closedList.end(),
                             [&](const Place &p)
                             { return p.name == adjacentPlace.name; }) != closedList.end())
            {
                continue;
            }

            // Check if the neighbor is in the open list
            auto it = std::find_if(openList.begin(), openList.end(),
                                   [&](const Place &p)
                                   { return p.name == adjacentPlace.name; });
            if (it == openList.end()) // Not in open list
            {
                // Set the distances and parent, then add to open list
                adjacentPlace.distanceFromOriginPlace = currentNode->distanceFromOriginPlace;
                adjacentPlace.euclideanDistanceToEnd = euclideanDistance(adjacentPlace, places[endIndex]);
                adjacentPlace.parent = &(*currentNode);
                openList.push_back(adjacentPlace);
            }
            else // Already in open list
            {
                // Check if the new path to the neighbor is shorter
                float newDist = currentNode->distanceFromOriginPlace;
                if (newDist < it->distanceFromOriginPlace)
                {
                    // Update the neighbor's cost and parent
                    it->distanceFromOriginPlace = newDist;
                    it->parent = &(*currentNode);
                }
            }
        }
    }

    // No path found
    return std::vector<Place>();
}

float shortestPath(char firstPlaceName, char lastPlaceName, const std::vector<Place> &places)
{
    std::vector<Place> path = AStar(places, firstPlaceName, lastPlaceName);
    // Calculate total distance of the path
    float totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        totalDistance += euclideanDistance(path[i], path[i + 1]);
    }
    return totalDistance;
}