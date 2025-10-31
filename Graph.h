#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

class Graph {
public:
    struct Edge {
        int to;
        int weight;
    };

    void addNode(int node);
    void addEdge(int from, int to, int weight);
    std::vector<int> shortestPath(int start, int end);
    void displayGraph();

private:
    std::unordered_map<int, std::vector<Edge>> adjList;
};

void Graph::addNode(int node) {
    if (adjList.find(node) == adjList.end()) {
        adjList[node] = {};
    }
}

void Graph::addEdge(int from, int to, int weight) {
    adjList[from].push_back({to, weight});
    adjList[to].push_back({from, weight}); // Assuming undirected graph
}

std::vector<int> Graph::shortestPath(int start, int end) {
    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;
    for (const auto& pair : adjList) {
        dist[pair.first] = std::numeric_limits<int>::max();
    }
    dist[start] = 0;

    auto cmp = [&dist](int left, int right) { return dist[left] > dist[right]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
    pq.push(start);

    while (!pq.empty()) {
        int current = pq.top();
        pq.pop();

        if (current == end) break;

        for (const Edge& edge : adjList[current]) {
            int newDist = dist[current] + edge.weight;
            if (newDist < dist[edge.to]) {
                dist[edge.to] = newDist;
                prev[edge.to] = current;
                pq.push(edge.to);
            }
        }
    }

    std::vector<int> path;
    for (int at = end; at != 0; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void Graph::displayGraph() {
    for (const auto& pair : adjList) {
        std::cout << "Node " << pair.first << ": ";
        for (const Edge& edge : pair.second) {
            std::cout << " -> " << edge.to << " (weight: " << edge.weight << ")";
        }
        std::cout << std::endl;
    }
}

#endif // GRAPH_H
