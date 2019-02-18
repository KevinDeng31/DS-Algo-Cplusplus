#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	bool isCyclic(int nodeID, vector<bool>& visited, vector<bool>& rs, vector<vector<int>>& preq) {

		if (!visited[nodeID]) {	//if we haven't visited this node
			visited[nodeID] = true;
			rs[nodeID] = true;
			/*iteratively visit all connected nodes
			  also check if connected nodes are in cycle */

			vector<int>::iterator it;
			/*if the node has been in recursion stack OR 
			it has not been visted but contains a cycle
			return true*/
			for (it = preq[nodeID].begin(); it != preq[nodeID].end(); ++it) {
				if (rs[*it] || !visited[*it] && isCyclic(*it, visited, rs, preq)) return true;
			}
		}
		rs[nodeID] = false; //pop node out
		return false;
	}

	bool canFinish(int numCourses, vector<pair<int, int>>& edge) {

		/* Create 2 vectors to store the nodes have been visited and which are in recursion stack
		   Create one 2-D vectors to store the edges in the graph */
		vector<bool> visited(numCourses, false);
		vector<bool> rs(numCourses, false);
		vector<vector<int>> preq(numCourses, vector<int>(0));

		for (pair<int, int> p : prerequisites) {
			preq[p.second].push_back(p.first);
		}

		for (size_t i = 0; i < preq.size(); ++i) {
			if (isCyclic(i, visited, rs, preq)) return false;
		}

		return true;

	}
};

int main() {
	return 0;
}
