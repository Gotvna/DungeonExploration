#include "AStarPathfinder.h"
#include "Map.h"
#include <cmath>
#include <algorithm>

AStarPathfinder::AStarPathfinder(bool ascend) : ascending(ascend) {}

int AStarPathfinder::calculateHeuristic(int x1, int y1, int goalX, int goalY, Map& map) {
    int distance = std::abs(x1 - goalX) + std::abs(y1 - goalY);

    int fleeOptions = 0;
    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    for (auto dir : directions) {
        int newX = x1 + dir.first;
        int newY = y1 + dir.second;
        if (newX >= 0 && newX < map.getWidth() && newY >= 0 && newY < map.getHeight() && !map.isTileOccupied(newX, newY)) {
            fleeOptions++;
        }
    }

    return distance - fleeOptions * 2;
}

#include <iostream>
std::vector<AStarPathfinder::Node*> AStarPathfinder::findPath(int startX, int startY, int goalX, int goalY, Map& map) {
    auto compare = [this](Node* a, Node* b) {
        return ascending ? a->getFCost() > b->getFCost() : a->getFCost() < b->getFCost();
        };

    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
    std::unordered_set<Node*> openSetTracker;
    std::unordered_set<int> closedSet;

    Node* startNode = new Node{ startX, startY, 0, calculateHeuristic(startX, startY, goalX, goalY, map), nullptr };
    openSet.push(startNode);
    openSetTracker.insert(startNode);

    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();
        openSetTracker.erase(currentNode);

        // Vérifie si on atteint la position cible
        if (currentNode->x == goalX && currentNode->y == goalY) {
            std::cout << "Chemin trouvé vers (" << goalX << ", " << goalY << ")" << std::endl;
            return reconstructPath(currentNode);
        }

        closedSet.insert(currentNode->x * map.getWidth() + currentNode->y);

        std::vector<Node*> neighbors = getNeighbors(currentNode, map);
        for (Node* neighbor : neighbors) {
            if (closedSet.find(neighbor->x * map.getWidth() + neighbor->y) != closedSet.end()) {
                continue;
            }

            int tentativeGCost = currentNode->gCost + 1;
            if (tentativeGCost < neighbor->gCost || openSetTracker.find(neighbor) == openSetTracker.end()) {
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = calculateHeuristic(neighbor->x, neighbor->y, goalX, goalY, map);
                neighbor->parent = currentNode;

                openSet.push(neighbor);
                openSetTracker.insert(neighbor);
            }
        }
    }

    std::cout << "Aucun chemin trouvé de (" << startX << ", " << startY << ") à (" << goalX << ", " << goalY << ")" << std::endl;
    return std::vector<Node*>();  // Aucun chemin trouvé
}

std::vector<AStarPathfinder::Node*> AStarPathfinder::reconstructPath(Node* currentNode) {
    std::vector<Node*> path;
    while (currentNode != nullptr) {
        path.push_back(currentNode);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<AStarPathfinder::Node*> AStarPathfinder::getNeighbors(Node* node, Map& map) {
    std::vector<Node*> neighbors;
    int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (int i = 0; i < 4; i++) {
        int newX = node->x + directions[i][0];
        int newY = node->y + directions[i][1];

        if (newX >= 0 && newX < map.getWidth() && newY >= 0 && newY < map.getHeight()) {
            if (isWalkable(newX, newY, map)) {
                Node* neighbor = new Node{ newX, newY, 0, 0, nullptr };
                neighbors.push_back(neighbor);
            }
        }
    }
    return neighbors;
}
bool AStarPathfinder::isWalkable(int x, int y, Map& map) {
    // Vérifie si les coordonnées sont dans les limites de la carte
    if (x < 0 || x >= map.getWidth() || y < 0 || y >= map.getHeight()) {
        return false;
    }

    bool occupied = map.isTileOccupied(x, y);

    return !occupied;  // Une case est considérée comme "walkable" si elle n'est pas occupée
}

