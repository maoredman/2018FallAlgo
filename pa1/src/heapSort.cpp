#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <assert.h>
#include "parser.h"
#include "util.h"

using namespace std;

// merge left_ & right_sorted into A
void max_heapify(vector<tuple<string, int>> &A, int curr_idx, int end_idx) {
    if (curr_idx*2+1 > end_idx) { // current_idx has no children
        return;
    }
    // has at least left child
    int max_idx = curr_idx;
    if (compare2strings(get<0>(A[curr_idx*2+1]), get<0>(A[max_idx])) == 1) {
        max_idx = curr_idx*2+1;
    }
    if (curr_idx*2+2 <= end_idx) { // has right child
        if (compare2strings(get<0>(A[curr_idx*2+2]), get<0>(A[max_idx])) == 1) {
            max_idx = curr_idx*2+2;
        }
    }

    // swap current_node with max_child
    if (max_idx != curr_idx) {
        tuple<string, int> max_element = A[max_idx];
        A[max_idx] = A[curr_idx];
        A[curr_idx] = max_element;
        max_heapify(A, max_idx, end_idx);
    }
}

// end_idx is "inclusive", i.e. should be length-1
vector<tuple<string, int>> heapSort(vector<tuple<string, int>> A) {
    // sort A inplace

    // Inplace transform A into maxheap
    for (int i = A.size()-1; i >= 0; i--) {
        max_heapify(A, i, A.size()-1);
    }

    // Extract max element, swap it with last element, decrease "range" of array, heapify array
    for (int end_idx = A.size()-1; end_idx >= 1; end_idx--) {
        tuple<string, int> max = A[0];
        A[0] = A[end_idx];
        A[end_idx] = max;
        max_heapify(A, 0, end_idx-1);
    }
    
    return A; // can modify A, since it is a copy of original array
}

int main( int argc, char** argv )
{	
    AlgParser parser;
    parser.Parse(argv[1]);
    cout << "Number of words: " << parser.QueryTotalStringCount() << endl;

    ofstream outfile;
    outfile.open(argv[2]);

    // STORE STRINGS AND THEIR POSITIONS INTO ARRAY (VECTOR)
    vector< tuple<string, int> > string_and_id;
    for( int i = 0 ; i < parser.QueryTotalStringCount() ; i++ ) {
		string_and_id.push_back(make_tuple(parser.QueryString(i), i+1));
	}

    // SORT
    vector<tuple<string, int>> sorted_string_and_id = heapSort(string_and_id);

    outfile << parser.QueryTotalStringCount() << endl;
    for (int i = 0; i < sorted_string_and_id.size(); ++i) {
        outfile << get<0>(sorted_string_and_id[i]) << " " << get<1>(sorted_string_and_id[i]) << endl;
    }
    // cout << compare2strings("z", "za") << endl;
    // outfile << parser.QueryString(i) << " " << i << endl;

    outfile.close();

	cout << "DONE!" << endl;
    return 0;
}