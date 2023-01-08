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
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

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
  State String
  This function takes a state as a parameter and returns a string representing the current state.
*/
string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  // Items on the left side of the river.
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  //Items on the right side of the river.
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}
/*
  Print Path
  This function takes two states as parameters and prints a path from state s to state t.
*/
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}
/*
  Neighbor Label
  This function takes two integers, representing two different states, and returns a string based on what the person should do to reach state t from state s.
*/
string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; } // Counts the number of items to cross with.
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return ""; 
  else return "Cross with " + which_cross;
}
/*
  Build Graph
  This function builds the graph to be used to solve the problem at hand.
*/
void build_graph(void)
{
  for(int i = 0; i < 16;i++) {
    for(int y = 0; y < 16;y++) {
      pair<state,state> helper(i,y);
      edge_label[helper] = neighbor_label(i,y);
    }
  }
  //From every state to another 
  for(int i = 0; i < 16; i++) {
    for(int y = 0; y < 16; y++) {
      state first, second;
      first = i;
      second = y;
      pair<state,state> helper(first,second);
      //Check for states that are not possible such as goat and wolf on the same side or goat and cabbage on the same side
      bool bad_state = false;
      if(first == 7 || first == 3 || first == 8 || first == 9 || first == 12 || first == 6) bad_state = true;
      if(second == 7 || second == 3 || second == 8 || second == 9 || second == 12 || second == 6) bad_state = true;
      //If it is possible from first state to second push it back to nbrs for both of the states
      if(edge_label[helper] != "" && !bad_state) {
        nbrs[first].push_back(second);
        nbrs[second].push_back(first);
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
  
  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
