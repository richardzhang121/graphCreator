/* Graph Creator that lets someone create a graph. The graph contains 
a number of nodes and what connects to what. Adding a vertex and edge, printing,
and deleting are possible commands. Finding the shortest path from one point to 
another is also incuded.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "Node.h"
#include "Graph.h"



using namespace std;

int main(){
  //main program loop
  Graph* graph = new Graph();
  char input[128];
  bool running = true;


  while(running){

    cin.getline(input, 128);
        
    if(input[0] == 'e' || input[0] == 'E'){
      cout << "Please put in 2 characters with a space separating them and a int weight" << endl;
      cin.getline(input,10);

      if(isdigit(input[4]) && input[1] == ' ' && input[3] == ' '){
	graph->add(input[0],input[2],atoi(&input[4]));
      }
      else cout << "Input should be character character weight" << endl;

    }
    else if(input[0] == 'v' || input[0] == 'V'){
      cout << "Please give a name for the new vertex" << endl;
      cin.getline(input,10);
      graph->add(input[0]);

    }
    else if(input[0] == 'd' || input[0] == 'D'){
      cout << "Give me one vertex to delete it or 2 vertex names to delete their edge" << endl;
      cin.getline(input,10);
      if (strlen(input) <= 2){
	graph->remove(input[0]);
    } else if (strlen(input) >= 3){
	graph->remove(input[0],input[2]);
      }else{
	cout << "This has bad formatting" << endl;
      }
    } 
    else if(input[0] == 'p' || input[0] == 'P'){
      graph->print();
    } 
    else if(input[0] == 'f' || input[0] == 'F'){
      cout << "Type two nodes or order to find the shortest distance." << endl;
      cin.getline(input,10);
      if (strlen(input) >= 3){
	graph->findPath(input[0],input[2]);
      }

    }
    else if(input[0] == 'q' || input[0] == 'Q'){
      running = false;
    }
    else{
      cout << "Please use one of the commands below" << endl;
      cout << "The possible commands are:\nEdge\nVertex\nDelete\nFind\nQuit" << endl;
    }
  }
}
