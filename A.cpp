#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

// Define a structure to represent a node in the graph
struct Node
{
    char name;                   // Name of the node
    double x, y;                 // Coordinates of the node
    std::vector<char> neighbors; // Names of neighboring nodes
};

// Define a priority queue structure for A* algorithm
struct PriorityQueue
{
    std::vector<char> elements;     // Elements in the priority queue
    std::vector<double> priorities; // Priorities associated with elements

    // Check if the priority queue is empty
    bool empty() const { return elements.empty(); }

    // Insert an element into the priority queue with its priority
    void push(char element, double priority)
    {
        elements.push_back(element);
        priorities.push_back(priority);
    }

    // Remove and return the element with the lowest priority
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

// Create the graph with nodes and their connections
std::vector<Node> createGraph()
{
    std::vector<Node> graph{
        {'A', 0.0, 0.0, {'B', 'C'}},
        {'B', 1.0, 1.0, {'A', 'C', 'D'}},
        {'C', 1.0, 0.0, {'A', 'B', 'E'}},
        {'D', 2.0, 1.0, {'B', 'E', 'F'}},
        {'E', 2.0, 0.0, {'C', 'D', 'G'}},
        {'F', 3.0, 1.0, {'D', 'G'}},
        {'G', 3.0, 0.0, {'E', 'F'}}};
    return graph;
}

// Calculate the Euclidean distance between two nodes
double euclideanDistance(const Node &a, const Node &b)
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

// Implement the A* algorithm to find the shortest path between two nodes
std::vector<char> aStar(const std::vector<Node> &graph, char start, char goal)
{
    // Initialize scores and paths
    std::vector<double> g_score(graph.size(), std::numeric_limits<double>::infinity());
    std::vector<double> f_score(graph.size(), std::numeric_limits<double>::infinity());
    std::vector<char> came_from(graph.size(), ' ');

    // Convert start and goal nodes to indices
    int start_index = start - 'A';
    int goal_index = goal - 'A';

    // Initialize start node scores
    g_score[start_index] = 0;
    f_score[start_index] = euclideanDistance(graph[start_index], graph[goal_index]);

    // Initialize priority queue with start node
    PriorityQueue open_set;
    open_set.push(start, f_score[start_index]);

    // A* algorithm loop
    while (!open_set.empty())
    {
        char current = open_set.pop(); // Get the current node

        // If the goal node is reached, reconstruct and return the path
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

        // Get the index of the current node
        int current_index = current - 'A';

        // Iterate through the neighbors of the current node
        for (char neighbor : graph[current_index].neighbors)
        {
            int neighbor_index = neighbor - 'A'; // Get the index of the neighbor
            double tentative_g_score = g_score[current_index] + euclideanDistance(graph[current_index], graph[neighbor_index]);

            // If this path to the neighbor is better than previous, update scores
            if (tentative_g_score < g_score[neighbor_index])
            {
                came_from[neighbor_index] = current;
                g_score[neighbor_index] = tentative_g_score;
                f_score[neighbor_index] = g_score[neighbor_index] + euclideanDistance(graph[neighbor_index], graph[goal_index]);
                open_set.push(neighbor, f_score[neighbor_index]);
            }
        }
    }

    return {}; // No path found
}

int main()
{
    // Create the graph
    std::vector<Node> graph = createGraph();

    // Input start and goal nodes from the user
    std::cout << "Infomre origem e destino: ";
    char start = ' ';
    char goal = ' ';
    std::cin >> start >> goal;

    // Find the shortest path using A* algorithm
    std::vector<char> path = aStar(graph, start, goal);

    // Output the result
    if (!path.empty())
    {
        std::cout << "Path: ";
        for (char node : path)
        {
            std::cout << node << " ";
        }
        std::cout << std::endl;
        double distance = 0.0;
        for (size_t i = 0; i < path.size() - 1; ++i)
        {
            distance += euclideanDistance(graph[path[i] - 'A'], graph[path[i + 1] - 'A']);
        }
        std::cout << "Distância mínima: " << distance << std::endl;
    }
    else
    {
        std::cout << "Nenhum caminho encontrado" << std::endl;
    }

    return 0;
}
