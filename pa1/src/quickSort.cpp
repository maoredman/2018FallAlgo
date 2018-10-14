#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "util.h"

using namespace std;

// partitions A in-place, and returns index of partition
int partition(vector<tuple<string, int>> &A, int start_idx, int end_idx) {
    assert(start_idx < end_idx);

    int key_idx = rand()%(end_idx-start_idx+1) + start_idx;
    assert(key_idx >= start_idx && key_idx <= end_idx);
    tuple<string, int> key = A[key_idx];

    int i = start_idx-1, j = end_idx+1;
    while (true) {
        j--;
        while (compare2strings(get<0>(A[j]), get<0>(key)) == 1) { // >
            j--;
        }
        i++;
        while (compare2strings(get<0>(A[i]), get<0>(key)) == -1) { // <
            i++;
        }
        if (i < j) {
            tuple<string, int> temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
        else {
            return j;
        }
    }
}

// sorts A in-place
void quickSort(vector<tuple<string, int>> &A, int start_idx, int end_idx) {
    // sort A inplace
    if (start_idx >= end_idx) {
        return;
    }

    int q = partition(A, start_idx, end_idx);
    quickSort(A, start_idx, q);
    quickSort(A, q+1, end_idx);
    
    return;
}

int main( int argc, char** argv )
{	
    srand (time(NULL));

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
    quickSort(string_and_id, 0, string_and_id.size()-1);

    outfile << parser.QueryTotalStringCount() << endl;
    for (int i = 0; i < string_and_id.size(); ++i) {
        outfile << get<0>(string_and_id[i]) << " " << get<1>(string_and_id[i]) << endl;
    }
    // cout << compare2strings("z", "za") << endl;
    // outfile << parser.QueryString(i) << " " << i << endl;

    outfile.close();

	cout << "DONE!" << endl;
    return 0;
}