//Allows there to be links

#include "Node.h"

Node::Node(char newName){
  name = newName;
}

bool Node::add(Node* toAdd, int newWeight){ //add a link

  bool linkExists = false;
  if(toAdd == this){
    cout << "You cant link a node to itself" << endl;
    return false;
  }
  for(vector<Link>::iterator it = links.begin(); it != links.end(); it++){
    if((*it).next == toAdd){
      linkExists = true;
      break;
    }
  }
  if (!linkExists){
    Link newLink;
    newLink.weight = newWeight;
    newLink.next = toAdd;
    newLink.last = this;
    links.push_back(newLink);
    return true;
  } else{
    cout << "The link from " << name << " to " << toAdd->name << " already exists."<< endl;
    return false; 
  }
}
//remove a link
bool Node::remove(Node* toRemove){
  for(vector<Link>::iterator it = links.begin(); it != links.end(); it++){
    if((*it).next == toRemove){
      links.erase(it);
      return true;
    }
  }
  return false;
} 
void Node::print(){
  bool noLinks = true;
  cout << name << " :: ";
  
  for(vector<Link>::iterator it = links.begin(); it != links.end(); it++){
    cout << (*it).next->name << ": " << (*it).weight << " ";
    noLinks = false;
  }
  if (noLinks) cout << "No Links";
  cout << endl;
}
vector<Link*> Node::getLinks(){
  vector<Link*> duplicate;
  for(vector<Link>::iterator it = links.begin(); it != links.end(); it++){
    Link* newLink = new Link();
    newLink->last = this;
    newLink->weight = (*it).weight;
    newLink->next = (*it).next;
    duplicate.push_back(newLink);
  }
  return duplicate;
}
