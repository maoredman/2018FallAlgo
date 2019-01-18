/**************************************************************************
 * File       [ main.cpp ]
 * Author     [ wlkb83 ]
 * Synopsis   [ demonstration for the usage of parser.h ]
 * Usage      [ ./parser [inputfileName] ]
 * Date       [ 2014/12/28 created ]
/**************************************************************************/

#include "parser.h"
#include "graph.h"
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>

int main(int argc, char **argv)
{
    if( argc < 3 ){ cout << "Usage: ./router <input_file_name> <output_file_name>" << endl; return 1; }

    AlgParser parser;

    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { return 1; }

    // show the information of the input
    cout << "grid " << parser.gNumHTiles() << " " << parser.gNumVTiles() << endl;
    cout << "capacity " << parser.gCapacity() << endl;
    cout << "num net " << parser.gNumNets() << endl;
    for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );
        cout << idNet << " " << posS.first << " " << posS.second << " "
                             << posE.first << " " << posE.second << endl;
    }
    
	cout << "----------------------" << endl;
	cout << "-- Complete parsing --" << endl;
	cout << "----------------------" << endl;

    int num_vertices = parser.gNumHTiles() * parser.gNumVTiles();
    // initialize cost graph (cost infinity)
    float** graph = new float*[num_vertices]; // have to use array of pointers to pass by reference
    for (int i = 0; i < num_vertices; ++i) {
        graph[i] = new float[num_vertices];
        for (int j = 0; j < num_vertices; ++j) {
            graph[i][j] = numeric_limits<float>::max();
        }
    }
    // initialize demand graph (demand 0)
    int** demand = new int*[num_vertices]; // have to use array of pointers to pass by reference
    for (int i = 0; i < num_vertices; ++i) {
        demand[i] = new int[num_vertices];
        for (int j = 0; j < num_vertices; ++j) {
            demand[i][j] = 0;
        }
    }

    // modify edge costs (to 0)
    for (int x = 0; x < parser.gNumVTiles(); ++x) {
        for (int y = 0; y < parser.gNumHTiles(); ++y) {
            int curr_V_idx = gridCoordToInt(x, y, parser.gNumVTiles());
            int neighbor_right_idx = gridCoordToInt(x+1, y, parser.gNumVTiles());
            int neighbor_up_idx = gridCoordToInt(x, y+1, parser.gNumVTiles());
            if (x+1 < parser.gNumVTiles()) {
                setEdgeWeight(curr_V_idx, neighbor_right_idx, 0, graph);
            }
            if (y+1 < parser.gNumHTiles()) {
                setEdgeWeight(curr_V_idx, neighbor_up_idx, 0, graph);
            }
        }
    }

    // printing graph
    // for (int i = 0; i < num_vertices; ++i) {
    //     for (int j = 0; j < num_vertices; ++j) {
    //         cout << graph[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // run Dijkstra's algorithm on each pair of points
    ofstream output;
    output.open(argv[2]);

    for (int netPos_id = 0; netPos_id < parser.gNumNets(); ++netPos_id) {
        pair<int,int> net_start = parser.gNetStart(netPos_id);
        pair<int,int> net_end = parser.gNetEnd(netPos_id);
        runDijkstra(output, graph, demand, num_vertices, parser.gNumVTiles(), parser.gCapacity(), netPos_id, net_start, net_end);
    }

    // output << "Writing this to a file.\n";
    output.close();

    // free graph memory
    for(int i = 0; i < parser.gNumHTiles(); ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    for(int i = 0; i < parser.gNumHTiles(); ++i) {
        delete[] demand[i];
    }
    delete[] demand;

    return 0;
}

