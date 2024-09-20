#pragma once
#include <vector>

class Map;

class FleePathfinder {
public:
    struct Node {
        int x, y;
        int gCost, hCost;
        Node* parent;
        int getFCost() const { return gCost + hCost; }
    };

    FleePathfinder();
    std::vector<Node*> findFleePath(int startX, int startY, int playerX, int playerY, int movementPoints, Map& map);

private:
    int calculateHeuristic(int x1, int y1, int playerX, int playerY, Map& map);
    std::vector<Node*> getNeighbors(Node* node, Map& map);
    std::vector<Node*> reconstructPath(Node* currentNode);
    bool isWalkable(int x, int y, Map& map);
};
