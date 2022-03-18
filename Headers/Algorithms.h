#pragma once

#include <utility>
#include <string>
#include <vector>
#include "Node.h"

typedef std::pair<std::string, int> pair;

namespace ai {

    std::vector<Node> createDB(std::istream &str);

    std::vector<Node> createTestDB(std::ifstream &str);

    std::vector<pair> makeVector(std::vector<Node>& data, int begin , int knn);

    void countDistance(Node &first, Node &second);

    void findClass(std::vector<Node> &data, Node &node, int knn, int begin = 0);

    void knnAlgorithm(std::vector<Node> &dataBase, std::vector<Node> &testDataBase, int k);

    void printVec(const std::vector<pair>&vec);

    void setNodesColor(std::vector<Node> &dataBase);
}