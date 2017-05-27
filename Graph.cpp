//Can add and remove and print and lookup existing nodes

#include "Node.h"
#include "Graph.h"


 
void Graph::add(char a, char b, int newWeight){ //allows user to input two vertexes and add them together by a set weight
  Node* node1 = nodeLookup(a);
  Node* node2 = nodeLookup(b); //look up nodes

  if ( node1 && node2 ){ //adds the nodes together
    node1->add(node2,newWeight); 
  } 
}
void Graph::add(char a){ // adds a single node to the graph
  bool isNew = true;
  //make sure its not already there
  for(vector<Node*>::iterator it = nodes.begin(); it!=nodes.end();it++){
    if ((*it)->name == a){
      isNew = false;
    }
  }
  if (isNew) nodes.push_back(new Node(a));
}
void Graph::remove(char a, char b){
  //remove an edge

  Node* node1 = nodeLookup(a);
  Node* node2 = nodeLookup(b);
 
  if ( node1 && node2 ){
    node1->remove(node2); 
  } 
}
void Graph::remove(char a){
  
  Node* removeNode = nodeLookup(a);
  if(!removeNode) return; //looks up node to make sure one exists
  //remove any connections to the node
  for(vector<Node*>::iterator it =  nodes.begin(); it != nodes.end();it++) {
      (*it)->remove(removeNode);
    }
  //remove the node itself
  for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
      if ((*it) == removeNode){
	nodes.erase(it);
	break;
      }
  }
}
void Graph::print(){
  for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
    (*it)->print();
  }
}

Node* Graph::nodeLookup(char a){
  //lookup the node by its name
  for(vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
    if ( (*it)->name == a){
      return (*it);
    }
  }
  return NULL;
}
bool removeSmaller(vector<Link*>* links, Link* link){
  //if there are two links to the same node and the bigger one is in the list, remove it
  for(vector<Link*>::iterator it = links->begin(); it != links->end(); it++){
    if((*it)->next == link->next){
      if((*it)->weight > link->weight){
	links->erase(it);
	return true;
     
      }else return false;
    }
    
  }
  return true;

}
void orderedAdd(vector<Link*>* links,Link* link){
  //add things making sure that it stays in decending order
  
  if(removeSmaller(links,link)){
    bool inserted = false;
    for(vector<Link*>::reverse_iterator it = links->rbegin(); it != links->rend(); it++){      
      if(link->weight < (*it)->weight){
	links->insert(it.base(),link);
	inserted = true;
      }
    }
    if (!inserted){
      links->insert(links->rend().base(),link);
    }
  }
}
 void Graph::findPath(char a, char b){
   //find the shortest path through the grid
   Node* start = nodeLookup(a);
   Node* end = nodeLookup(b);
   //find the nodes and make sure they exist
   if(!start || !end){
     cout << "Those Nodes dont exist" << endl;

   }
   vector<Link*> active;
   vector<Link*> complete;
   
   Link* first = new Link();
   //add the first link to the active list
   first->next = start;
   first->weight = 0;
   first->last = NULL;
   
   active.push_back(first);
   
   while((active.size()) > 0){
     //while theres still more links to look at and you haven't already done the end node
     if (complete.size() > 0){
       if((*complete.back()).next == end){
	 break;
       }
     }
     //take the next node in the list
     Link* current = (*active.rbegin());
     //grab its links
     vector<Link*> newLinks = current->next->getLinks();
     //add them to the active list if they are either new or smaller than the current smallest link to the node
     for(vector<Link*>::iterator it = newLinks.begin(); it != newLinks.end(); it++){
       Link* newLink = (*it);
       
       bool isDone = false;
       
       for(vector<Link*>::iterator it = complete.begin(); it != complete.end(); it++){
	 if ((*it)->next == newLink->next){
	   isDone = true;
	   cout << "no" << endl;
	   break;
	 }
       }
       if(!isDone){
	 newLink->weight += current->weight;
	 orderedAdd(&active,newLink);
       }
     }
     //add the current link to the complete list
     complete.push_back(current);
     active.pop_back();
    
   }
   //if you found the last node, print out the path
   if((*complete.rbegin())->next == end){
     Node* nextPrint = end;
     cout << "The total weight was " << (*complete.rbegin())->weight << endl;
     
      for(vector<Link*>::reverse_iterator it = complete.rbegin(); it != complete.rend(); it++){
	 if ((*it)->next == nextPrint){
	   cout << nextPrint->name << "<-";
	   nextPrint = (*it)->last;
	 }
       }
      cout << endl;
   }
   else cout << "No posible path" << endl;
 }
