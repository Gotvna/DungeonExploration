#include "FleePathfinder.h"

#include "Game/Map/Map.h"

#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>

FleePathfinder::FleePathfinder() {}

int FleePathfinder::calculateHeuristic(int x1, int y1, int playerX, int playerY, Map& map) {
    return std::abs(x1 - playerX) + std::abs(y1 - playerY);
}

std::vector<FleePathfinder::Node*> FleePathfinder::findFleePath(int startX, int startY, int playerX, int playerY, int movementPoints, Map& map) {
    auto compare = [](Node* a, Node* b) {
        return a->getFCost() < b->getFCost();
        };

    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
    std::unordered_set<int> closedSet;

    Node* startNode = new Node{ startX, startY, 0, calculateHeuristic(startX, startY, playerX, playerY, map), nullptr };
    openSet.push(startNode);

    std::unordered_map<int, Node*> allNodes;
    allNodes[startY * map.getWidth() + startX] = startNode;

    while (!openSet.empty()) {
        Node* currentNode = openSet.top();
        openSet.pop();

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
                neighbor->hCost = calculateHeuristic(neighbor->x, neighbor->y, playerX, playerY, map);
                neighbor->parent = currentNode;

                openSet.push(neighbor);
                allNodes[neighborPos] = neighbor;
            }
            else {
                delete neighbor;
            }
        }
    }

    std::vector<Node*> bestPath;
    int maxDistance = -1;

    for (const auto& pair : allNodes) {
        Node* node = pair.second;
        int distance = std::abs(node->x - playerX) + std::abs(node->y - playerY);
        if (distance > maxDistance && node->gCost <= movementPoints) {
            maxDistance = distance;
            bestPath = reconstructPath(node);
        }
    }


    return bestPath;
}

std::vector<FleePathfinder::Node*> FleePathfinder::reconstructPath(Node* currentNode) {
    std::vector<Node*> path;
    while (currentNode != nullptr) {
        path.push_back(currentNode);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<FleePathfinder::Node*> FleePathfinder::getNeighbors(Node* node, Map& map) {
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

bool FleePathfinder::isWalkable(int x, int y, Map& map) {
    return !map.isTileOccupied(x, y);
}
