//Can hold links with one vertex to another

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>

using namespace std;

class Node;

struct Link{
  int weight;
  Node* next;
  Node* last;
};


class Node{
private:
  vector<Link> links;
public:
  Node(char newName);

  char name;

  vector<Link*> getLinks();
  bool remove(Node* toRemove);
  bool add(Node* toAdd, int newWeight);
  void print();
};

#endif
