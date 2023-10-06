/* Program 6: LinkedList
Course: CS 141, Spring 2023, UIC
System: DevC++ on Windows 11
Author: Zeehan Sharif */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// I am making a linked list that holds integers etc.
struct LinkedList {
  
    LinkedList(int value) : value(value), next(nullptr) {}
  
    // I am making a function that returns the value of the list
    void append(int value) {
      if (next == nullptr) {
        next = new LinkedList(value);
      } else {
        next->append(value);
      }
    }
  
    // I am making a function that returns the value of the list
    int value;
    LinkedList *next;
};

class Graph {

  public:
    vector<LinkedList *> createAdjacencyList(string fileName);
    void printAdjList(const vector<LinkedList *> &adjList);
    void saveToFile(const vector<LinkedList *> &adjList, string fileName);
    void printGraphStats(const vector<LinkedList *> &adjList);
  
  private:
    // I am making a graph that holds the adjacency list
    unordered_set<string> visitedEdges;
};

// I am making a function that returns the value of the list
vector<LinkedList *> Graph::createAdjacencyList(string fileName) {
  
  ifstream file_in(fileName);
  vector<LinkedList *> adjList;
  string line;

  // I am making a variable that holds the value of the line
  while (getline(file_in, line)) {

    istringstream iss(line);
    int source, target;

    // I am making a variable that holds the value of the line
    if (!(iss >> source >> target)) {
      break;
    }

    // I am making a variable that holds the value of the line
    string edgeKey =
        to_string(min(source, target)) + "," + to_string(max(source, target));

    if (visitedEdges.find(edgeKey) != visitedEdges.end()) {
      continue;
    }

    else {
      visitedEdges.insert(edgeKey);
    }

    // Resize adjacency_list vector if necessary
    while (adjList.size() < max(source, target) + 1) {
      adjList.push_back(nullptr);
    }

    // Add edge to adjacency list
    if (adjList[source] == nullptr) {
      adjList[source] = new LinkedList(target);
    } else {
      adjList[source]->append(target);
    }

    // Add inverse edge to adjacency list
    if (adjList[target] == nullptr) {
      adjList[target] = new LinkedList(source);
    } else {
      adjList[target]->append(source);
    }
  }
  file_in.close();
  return adjList;
}

// Ignore this function, this was used when I was testing the Adjacency List
void Graph::printAdjList(const vector<LinkedList *> &adjList) {
  
  // Iterate over all non-null linked lists
  for (int i = 0; i < adjList.size(); i++) {
    LinkedList *node = adjList[i];

    // Skip non-existing nodes
    if (node == nullptr) {
      continue;
    }

    // Print the node ID
    cout << i << ": ";

    // Iterate over the node's linked list of edges and print them
    while (node != nullptr) {
      cout << node->value << " ";
      node = node->next;
    }

    cout << endl;
  }
}

// I am making a function that returns the value of the list
void Graph::saveToFile(const vector<LinkedList *> &adjList, string fileName) {

  //open up the file
  ofstream file_out(fileName);

  // Iterate over all not null linked lists
  for (int i = 0; i < adjList.size(); i++) {
    
    if (adjList[i] == nullptr) {
      continue;
    }

    // Print the node's ID
    file_out << i << ": ";

    // Collect edges into a vector and sort them in ascending order
    vector<int> edges;
    LinkedList *node = adjList[i];
    while (node != nullptr) {
      edges.push_back(node->value);
      node = node->next;
    }
    sort(edges.begin(), edges.end());

    // Print edges in sorted order
    for (int i = 0; i < edges.size(); i++) {

      file_out << edges.at(i);
      // Add space if not last edge in vector
      if (i != edges.size() - 1) {
        file_out << " ";
      }
    }

    file_out << endl;
  }
  file_out.close();
}

// I am making a function that returns the value of the list
void Graph::printGraphStats(const vector<LinkedList *> &adjList) {

  int nNodes = 0, nEdges = 0, maxDegree = 0;

  for (int i = 0; i < adjList.size(); i++) {
    LinkedList *node = adjList[i];
    int degree = 0;

    // Skip null nodes
    if (node == nullptr) {
      continue;
    }

    // Count number of edges and get degree of the node
    while (node != nullptr) {
      nEdges++;
      degree++;
      node = node->next;
    }

    nNodes++;
    maxDegree = max(maxDegree, degree);
  }

  cout << "Number of nodes: " << nNodes << endl;
  cout << "Number of edges: " << nEdges / 2 << endl;
  cout << "Maximum degree: " << maxDegree << endl;
}

void run(const string &src_path, const string &dst_path) {

  Graph g;
  vector<LinkedList *> adjList = g.createAdjacencyList(src_path);
  g.saveToFile(adjList, dst_path);
  g.printGraphStats(adjList);

  // Clean up adjList
  for (int i = 0; i < adjList.size(); i++) {
    delete adjList[i];
  }
}

int main() {
  run("toy.txt",  "AdList.txt");
}