#ifndef ASTARPATHFINDER_H
#define ASTARPATHFINDER_H

#include <vector>
#include <queue>
#include <unordered_set>

class Map;

class AStarPathfinder {
public:
    struct Node {
        int x, y;
        int gCost;
        int hCost;
        Node* parent;

        int getFCost() const { return gCost + hCost; }
        bool operator==(const Node& other) const {
            return x == other.x && y == other.y;
        }
    };

    AStarPathfinder(bool ascend = true);

    std::vector<Node*> findPath(int startX, int startY, int goalX, int goalY, Map& map);

private:
    bool ascending;

    int calculateHeuristic(int x1, int y1, int goalX, int goalY, Map& map);

    std::vector<Node*> getNeighbors(Node* node, Map& map);

    bool isWalkable(int x, int y, Map& map);

    std::vector<Node*> reconstructPath(Node* currentNode);
};

struct NodeComparator {
    bool ascending;
    NodeComparator(bool asc) : ascending(asc) {}

    bool operator()(const AStarPathfinder::Node* a, const AStarPathfinder::Node* b) {
        return ascending ? a->getFCost() > b->getFCost() : a->getFCost() < b->getFCost();
    }
};

#endif
