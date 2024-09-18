#include "AStarPathfinder.h"
#include "Map.h"
#include <cmath>
#include <algorithm>

AStarPathfinder::AStarPathfinder(bool ascend) : ascending(ascend) {}

int AStarPathfinder::calculateHeuristic(int x1, int y1, int goalX, int goalY) {
    int distance = std::abs(x1 - goalX) + std::abs(y1 - goalY);
    return ascending ? distance : -distance;
}

std::vector<AStarPathfinder::Node*> AStarPathfinder::findPath(int startX, int startY, int goalX, int goalY, Map& map) {
    auto compare = [this](Node* a, Node* b) {
        return ascending ? a->getFCost() > b->getFCost() : a->getFCost() < b->getFCost();
        };

    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
    std::unordered_set<Node*> openSetTracker;
    std::unordered_set<int> closedSet;

    Node* startNode = new Node{ startX, startY, 0, calculateHeuristic(startX, startY, goalX, goalY), nullptr };
    openSet.push(startNode);
    openSetTracker.insert(startNode);

    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();
        openSetTracker.erase(currentNode);

        // Si on atteint la position cible
        if (currentNode->x == goalX && currentNode->y == goalY) {
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
                neighbor->hCost = calculateHeuristic(neighbor->x, neighbor->y, goalX, goalY);
                neighbor->parent = currentNode;

                openSet.push(neighbor);
                openSetTracker.insert(neighbor);
            }
        }
    }

    return std::vector<Node*>();
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
    return !map.isTileOccupied(x, y);
}
