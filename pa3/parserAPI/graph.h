#ifndef _DEFINE_GRAPH_
#define _DEFINE_GRAPH_

#include <limits>
#include <vector>
// #include <queue>
#include <unordered_set>
#include <cmath>
#include <sstream>

int gridCoordToInt(int x, int y, int row_length)
{
	return y*row_length + x;
}

pair<int,int> intToGridCoord(int idx, int row_length)
{
	return pair<int,int>(idx - (idx/row_length)*row_length, idx/row_length);
}

void setEdgeWeight(int V1_idx, int V2_idx, float weight, float** graph)
{
	graph[V1_idx][V2_idx] = weight;
	graph[V2_idx][V1_idx] = weight;
	return;
}

void graphRelax(int v1_idx, int v2_idx, float weight, float* distance, int* predecessor)
{
	if (distance[v1_idx] + weight < distance[v2_idx]) {
		distance[v2_idx] = distance[v1_idx] + weight;
		predecessor[v2_idx] = v1_idx;
	}
}

void runDijkstra(ofstream& output, float** graph, int** demand,
				int num_vertices, int row_length, int capacity,
				int netPos_id, pair<int,int> net_start, pair<int,int> net_end)
{
	int end_idx = gridCoordToInt(net_start.first, net_start.second, row_length);
	int start_idx = gridCoordToInt(net_end.first, net_end.second, row_length);
	
	// distances from start_idx vertex
	float *distance = new float[num_vertices];
	for (int i = 0; i < num_vertices; ++i) {
        distance[i] = std::numeric_limits<float>::max();
    }
    distance[start_idx] = 0;

	// NOTE: predecessor will init to 0, but I guess if backtrack from end_idx, it's OK
	int *predecessor = new int[num_vertices];
	for (int i = 0; i < num_vertices; ++i) {
        predecessor[i] = 0;
    }

	// By default a min heap is created ordered by first element of pair
	// <distance, vertex_idx>
    // std::priority_queue<pair<float, int>, std::vector<std::pair<float, int>>,
    // 									std::greater<std::pair<float, int>> > vertex_minheap;
    // TODO: push vertices into priority queue

    std::unordered_set<int> visited_vertices;

    while (true) {
    	// std::pair<float, int> min_v = vertex_minheap.top();
    	// float v1_distance = min_v.first;
    	// int v1_idx = min_v.second;
    	float min_distance = std::numeric_limits<float>::max();
    	int min_idx = 0;
    	for (int i = 0; i < num_vertices; ++i) {
    		std::unordered_set<int>::const_iterator got = visited_vertices.find(i);
    		// if vertex not visited, then it qualifies as a min-distance candidate
    		if (got == visited_vertices.end() && distance[i] < min_distance) {
    			min_distance = distance[i];
    			min_idx = i;
    		}
    	}
    	if (min_distance == std::numeric_limits<float>::max()) { // all vertices visited
    		// std::cout << "All vertices visited for a NetPair!" << std::endl;
    		break;
    	}

    	visited_vertices.insert(min_idx);

    	for (int i = 0; i < num_vertices; ++i) { // check all min_idx's adjacent vertices
    		// if adjacent vertex visited before, no chance it can be relaxed, don't bother
    		std::unordered_set<int>::const_iterator got = visited_vertices.find(i);
    		if (got == visited_vertices.end() && graph[min_idx][i] < std::numeric_limits<float>::max()){
    			graphRelax(min_idx, i, graph[min_idx][i], distance, predecessor);
    		}
    	}
    }

    // backtrace from end_idx until we hit start_idx, updating edge costs along the way
    int curr_idx = end_idx;
    pair<int,int> curr_coord = intToGridCoord(end_idx, row_length);
    std::stringstream ss;
    int num_routes = 0;
    do {
    	ss << curr_coord.first << " " << curr_coord.second;
    	ss << " ";

    	demand[curr_coord.first][curr_coord.second] += 1;
    	float curr_demand = demand[curr_coord.first][curr_coord.second]; // converting int to float
    	setEdgeWeight(curr_idx, predecessor[curr_idx],
    				  std::pow(2, curr_demand/capacity)-1,
    				  graph);

    	curr_idx = predecessor[curr_idx];
    	curr_coord = intToGridCoord(curr_idx, row_length);

    	ss << curr_coord.first << " " << curr_coord.second << std::endl;

    	num_routes += 1;
    } while (curr_idx != start_idx);
    output << netPos_id << " " << num_routes << std::endl;
    output << ss.rdbuf();


    delete[] distance;
    delete[] predecessor;

	return;
}

#endif