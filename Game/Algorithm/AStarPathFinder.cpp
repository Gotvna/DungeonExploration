#include "AStarPathfinder.h"
#include "Map.h"
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

AStarPathfinder::AStarPathfinder(bool ascend) : ascending(ascend) {}

int AStarPathfinder::calculateHeuristic(int x1, int y1, int goalX, int goalY, Map& map) {
    return std::abs(x1 - goalX) + std::abs(y1 - goalY);
}

std::vector<AStarPathfinder::Node*> AStarPathfinder::findPath(int startX, int startY, int goalX, int goalY, Map& map) {
    auto compare = [this](Node* a, Node* b) {
        return ascending ? a->getFCost() > b->getFCost() : a->getFCost() < b->getFCost();
        };

    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
    std::unordered_set<int> closedSet;

    Node* startNode = new Node{ startX, startY, 0, calculateHeuristic(startX, startY, goalX, goalY, map), nullptr };
    openSet.push(startNode);

    std::unordered_map<int, Node*> allNodes;

    allNodes[startY * map.getWidth() + startX] = startNode;

    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();

        if (currentNode->x == goalX && currentNode->y == goalY) {
            return reconstructPath(currentNode);
        }

        closedSet.insert(currentNode->y * map.getWidth() + currentNode->x);

        std::vector<Node*> neighbors = getNeighbors(currentNode, map);
        for (Node* neighbor : neighbors) {
            int neighborPos = neighbor->y * map.getWidth() + neighbor->x;

            if (closedSet.find(neighborPos) != closedSet.end()) {
                delete neighbor;
                continue;
            }

            int tentativeGCost = currentNode->gCost + 1;

            if (allNodes.find(neighborPos) == allNodes.end() || tentativeGCost < allNodes[neighborPos]->gCost) {
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = calculateHeuristic(neighbor->x, neighbor->y, goalX, goalY, map);
                neighbor->parent = currentNode;

                openSet.push(neighbor);
                allNodes[neighborPos] = neighbor;
            }
            else {
                delete neighbor;
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
