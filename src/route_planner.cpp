#include "route_planner.h"
#include <algorithm>

// Constructor
RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y)
    : m_Model(model)
{
    // Convert inputs to percentage
    start_x *= 0.01;
    start_y *= 0.01;
    end_x   *= 0.01;
    end_y   *= 0.01;

    // Find the closest nodes to the start and end coordinates
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node   = &m_Model.FindClosestNode(end_x, end_y);
}

// Calculate the heuristic value (h = distance to goal)
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}

// Expand current node by adding unvisited neighbors
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    // Populate current_node->neighbors
    current_node->FindNeighbors();

    // Iterate over neighbors
    for (auto *neighbor : current_node->neighbors) {
        if (!neighbor->visited) {
            neighbor->parent = current_node; // set parent
            neighbor->h_value = CalculateHValue(neighbor); // heuristic
            neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
            neighbor->visited = true; // mark visited
            open_list.push_back(neighbor); // add to open list
        }
    }
}

// Select the next node (lowest f = g + h)
RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(open_list.begin(), open_list.end(),
              [](RouteModel::Node *a, RouteModel::Node *b) {
                  return (a->g_value + a->h_value) < (b->g_value + b->h_value);
              });

    RouteModel::Node *lowest_node = open_list.front();
    open_list.erase(open_list.begin());
    return lowest_node;
}

// Construct the final path (backtrack from end to start)
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while (current_node != nullptr) {
        path_found.push_back(*current_node);
        if (current_node->parent != nullptr) {
            distance += current_node->distance(*current_node->parent);
        }
        current_node = current_node->parent;
    }

    // Reverse path to start → end
    std::reverse(path_found.begin(), path_found.end());

    // Scale distance to meters
    distance *= m_Model.MetricScale();
    return path_found;
}

// Main A* Search Algorithm
void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // Initialize
    start_node->visited = true;
    open_list.push_back(start_node);

    // Loop until open_list is empty or goal is found
    while (!open_list.empty()) {
        current_node = NextNode();

        // Check if reached the goal
        if (current_node == end_node) {
            m_Model.path = ConstructFinalPath(current_node);
            return; // path found ✅
        }

        // Add all neighbors
        AddNeighbors(current_node);
    }
}

