#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <climits>
#include <numeric>

using namespace std;

struct point {
public:
	int pointID;
	int dist;
	int prev;

	point(int id, int distFromOrigin) : pointID(id), dist(distFromOrigin) {};

};

struct cmpFunction
{
	bool operator()(const point& a, const point& b)
	{
		return a.dist > b.dist;
	}
};

class graph {
private:
	vector<vector<int>> graph_;
public:
	//constructor
	graph(vector<vector<int>> adj_matrix) : graph_(adj_matrix) {}

	void printgraph() { //print graph  
		for (size_t i = 0; i < graph_.size(); ++i) {
			for (size_t j = 0; j < graph_[0].size(); ++j) {
				cout << graph_[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	int getSize() { return graph_.size();} //return # of vertices

	int getEdge() { //return # of edges
		int num_edge = 0;
		for (size_t i = 0; i < graph_.size(); ++i) {
			for (size_t j = i + 1; j < graph_[0].size(); ++j) {
				if (graph_[i][j]) num_edge++;
			}
		}
		return num_edge;
	}

	bool adjacent(int x, int y) { return (graph_[x][y] != 0);}

	vector<int> neighbors(int x) { //return the neighbors of vertice x
		vector<int> res;
		for (size_t i = 0; i < graph_[x].size(); ++i) {
			if (graph_[x][i] != 0) res.push_back(i);
		}
		return res;
	}

	int distance(int s, int t) {
		// initialize priority queue, overload compare function
		priority_queue <point, vector<point>, cmpFunction> myqueue; 
		vector<int> distance(graph_.size());
		int longest_path = 0;
		for (size_t i = 0; i < graph_.size(); ++i) {
			longest_path += accumulate(graph_[i].begin(), graph_[i].end(), 0);
		}
		longest_path++;

		/*use a priority queue to compute the distance in an order of increasing distance 
		from start vertice. We firstly set distance of start vertice as 0 and others as a big number,
		then pop out the vertice having shortest distance, and updata all its neighbors' distances.
		Keep pushing in these updated vertices and updating until the queue is empty.
		*/
		for (size_t i = 0; i < graph_.size(); ++i) {
			if (i == s) {
				myqueue.push(point(i, 0));
				distance[i] = 0;
			}
			else {
				myqueue.push(point(i, longest_path));
				distance[i] = longest_path;
			}
		}

		point tmp_point = myqueue.top();;
		while (!myqueue.empty()) {
			tmp_point = myqueue.top();
			myqueue.pop();
			if (tmp_point.dist <= distance[tmp_point.pointID]) {
				for (size_t i = 0; i < graph_[tmp_point.pointID].size(); ++i) {
					if (adjacent(tmp_point.pointID, i)) {
						/* updata if distance of vertice i from origin is longer than dist of temporary vertice 
						from origin plus the weight of edge between temporary vertice and vertice i*/  
						if (distance[i] > tmp_point.dist + graph_[tmp_point.pointID][i]) {
							distance[i] = tmp_point.dist + graph_[tmp_point.pointID][i];
							myqueue.push(point(i, distance[i]));
						}
					}
				}
			}
		}
		return distance[t] == longest_path ? -1 : distance[t];
	}
};
