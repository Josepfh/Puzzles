/*
  Implementation and Main File
  Required functions are implemented in this file, and testing is done.
*/
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;
/*
  Search
  This function takes a state as a parameter and does a breadth-first search, outward from source node.
*/
void search(state source_node)
{
  //A generic breadth-first search for a graph is used.
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}
/*
  Print Path
  This function takes two states as parameters and prints a path from state s to state t.
*/
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}
/*
  Is Neighbor
  This function takes two states as parameters and returns a string based on the action performed.
*/
string is_neighbor(state i, state y) {
  //The step to reach y from i is determined here.
  if(y.first==3 && y.second == i.second - (3-i.first)) return "Pour B->A";
  else if(y.second == 0 && y.first == i.first + i.second) return "Pour B->A";
  else if(y.second == 4 && y.first == i.first - (4-i.second)) return "Pour A->B";
  else if(y.first == 0 && y.second == i.first + i.second) return "Pour A->B"; 
  else if(y.first == 0 && i.first != 0 && y.second == i.second) return "Empty A";
  else if(y.second == 0 && y.second != 0 && y.first == i.first) return "Empty B";
  else if(y.first == 3 && i.first != 3 && y.second == i.second) return "Fill A";
  else if(y.second == 4 && i.second != 4 && y.first == i.first) return "Fill B";
  else return ""; //If there is no way to reach from i to y
}
/*
  Build Graph
  This function builds the graph to be used to solve the problem at hand.
*/
void build_graph(void)
{
  //Nested loop structure to find the neighbor states.
  for(int i = 0; i <= 3; i++) {
    for(int y= 0;y<=4;y++) {
      state first = make_pair(i,y);
      for(int a = 0; a<= 3;a++) {
        for(int b = 0; b <=4;b++) {
          state second = make_pair(a,b);
          edge_label[make_pair(first,second)] = is_neighbor(first,second); //For a state first check for the action to be performed to reach state second
          if(is_neighbor(first,second) != "") { // If it is possible add it to the vector in nbrs
            nbrs[first].push_back(second);
          }
        }
      }
    }
  }

}
/*
  Main Function
  This function tests the functions above.
*/
int main(void)
{
  build_graph();
  
  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
