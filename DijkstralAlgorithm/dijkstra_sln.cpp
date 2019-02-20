#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "graph.h"

using namespace std;

int main() {

	// 50 vertices in total with 0.2 density
	// adjacency matrix stores if there is a edge between 2 vertices and the value of edge  
	int vertices = 4;    
	double density = 0.8;
	vector<vector<int>> adj_matrix(vertices, vector<int>(vertices, 0)); 

	srand(time(NULL)); // to randomly generate numbers  
	/*initialize a directed graph contains n vertices, we allowed 
	2 reverse edges between 2 vertices have different weights*/
	for (size_t i = 0; i < adj_matrix.size(); ++i) {
		for (size_t j = 0; j < adj_matrix[0].size(); ++j) {
			if (i == j) adj_matrix[i][j] = 0;
			else if ((rand() % 10 + 1) / 10.0 <= density) {
				adj_matrix[i][j] = rand() % 10 + 1;
			}
		}
	}
	


	graph tmp_graph = graph(adj_matrix);
	cout << "There are " << tmp_graph.getSize() << " vertices in this graph.\n";
	cout << "There are " << tmp_graph.getEdge() << " vertices in this graph.\n";
	tmp_graph.printgraph();
	vector<int> nerb = tmp_graph.neighbors(0);
	//for (size_t i = 0; i < nerb.size(); ++i) cout << nerb[i] << ' ';
	cout << tmp_graph.distance(0, 2) << '\n';

	return 0;
}