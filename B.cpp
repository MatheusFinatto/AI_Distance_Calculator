#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_map>

// Struct to represent a station
struct Station
{
    char name;   // Name of the station
    double x, y; // Coordinates of the station
};

// Struct to represent an edge between two stations
struct Edge
{
    char from, to; // Names of the connected stations
    double weight; // Travel time between the stations
};

// Struct to represent the priority queue for A* algorithm
struct PriorityQueue
{
    std::vector<char> elements;     // Elements in the priority queue
    std::vector<double> priorities; // Priorities associated with elements

    bool empty() const { return elements.empty(); }

    void push(char element, double priority)
    {
        elements.push_back(element);
        priorities.push_back(priority);
    }

    char pop()
    {
        auto it = std::min_element(priorities.begin(), priorities.end());
        int index = std::distance(priorities.begin(), it);
        char element = elements[index];
        elements.erase(elements.begin() + index);
        priorities.erase(priorities.begin() + index);
        return element;
    }
};

// Function to calculate Euclidean distance between two stations
double euclideanDistance(const Station &a, const Station &b)
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

// Function to find the fastest path between two stations using A*
std::vector<char> findFastestPath(
    const std::vector<Station> &stations,
    const std::vector<Edge> &edges,
    char start, char goal)
{

    std::unordered_map<char, std::vector<Edge>> adjacency_list;
    for (const auto &edge : edges)
    {
        adjacency_list[edge.from].push_back(edge);
    }

    std::vector<double> g_score(stations.size(), std::numeric_limits<double>::infinity());
    std::vector<double> f_score(stations.size(), std::numeric_limits<double>::infinity());
    std::vector<char> came_from(stations.size(), ' ');

    int start_index = start - 'A';
    int goal_index = goal - 'A';

    g_score[start_index] = 0;
    f_score[start_index] = euclideanDistance(stations[start_index], stations[goal_index]);

    PriorityQueue open_set;
    open_set.push(start, f_score[start_index]);

    while (!open_set.empty())
    {
        char current = open_set.pop();

        if (current == goal)
        {
            std::vector<char> path;
            while (current != ' ')
            {
                path.push_back(current);
                current = came_from[current - 'A'];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        int current_index = current - 'A';

        for (const auto &edge : adjacency_list[current])
        {
            char neighbor = edge.to;
            int neighbor_index = neighbor - 'A';
            double tentative_g_score = g_score[current_index] + edge.weight;
            if (tentative_g_score < g_score[neighbor_index])
            {
                came_from[neighbor_index] = current;
                g_score[neighbor_index] = tentative_g_score;
                f_score[neighbor_index] = g_score[neighbor_index] + euclideanDistance(stations[neighbor_index], stations[goal_index]);
                open_set.push(neighbor, f_score[neighbor_index]);
            }
        }
    }

    return {}; // No path found
}

int main()
{
    // Define stations and edges
    std::vector<Station> stations = {
        {'A', 0.0, 0.0},
        {'B', 1.0, 1.0},
        {'C', 2.0, 0.0},
        {'D', 3.0, 1.0},
        {'E', 4.0, 0.0}};
    std::vector<Edge> edges = {
        {'A', 'B', 1.0},
        {'A', 'C', 2.0},
        {'B', 'C', 1.5},
        {'B', 'D', 2.0},
        {'C', 'D', 1.0},
        {'C', 'E', 3.0},
        {'D', 'E', 2.5}};

    // Get user input for start and goal stations
    char start, goal;
    std::cout << "Informe a primeira estação: ";
    std::cin >> start;
    std::cout << "Informe a estação destino: ";
    std::cin >> goal;

    // Find the fastest path
    std::vector<char> path = findFastestPath(stations, edges, start, goal);

    // Print the result
    if (!path.empty())
    {
        std::cout << "Caminho mais rápido baseado na distância euclidiana: ";
        for (char station : path)
        {
            std::cout << station << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Nenhum caminho encontrado" << std::endl;
    }

    return 0;
}
