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
void merge(vector<tuple<string, int>> &A,
            vector<tuple<string, int>> &left_sorted,
            vector<tuple<string, int>> &right_sorted) {

    int i = 0, j = 0, a_idx = 0;
    while ((i < left_sorted.size()) && (j < right_sorted.size())) {
        if (compare2strings(get<0>(left_sorted[i]), get<0>(right_sorted[j])) < 1) {
            // cout << "push left: " << get<0>(left_sorted[i]) << endl;
            // merged_A.push_back(left_sorted[i]);
            A[a_idx] = left_sorted[i];
            i++;
        }
        else {
            // cout << "push right: " << get<0>(right_sorted[j]) << endl;
            // merged_A.push_back(right_sorted[j]);
            A[a_idx] = right_sorted[j];
            j++;
        }
        a_idx++;
    }

    if (i >= left_sorted.size()) { // left array exhausted, right array still has stuff left
        while (j < right_sorted.size()) {
            // cout << "left done, push right: " << get<0>(right_sorted[j]) << endl;
            // merged_A.push_back(right_sorted[j]);
            A[a_idx] = right_sorted[j];
            j++;
            a_idx++;
        }
    }
    else { // right array exhausted, left array still has stuff left
        while (i < left_sorted.size()) {
            // cout << "right done, push left: " << get<0>(left_sorted[i]) << endl;
            // merged_A.push_back(left_sorted[i]);
            A[a_idx] = left_sorted[i];
            i++;
            a_idx++;
        }
    }

    assert(left_sorted.size() + right_sorted.size() == A.size());
}

// end_idx is "inclusive", i.e. should be length-1
vector<tuple<string, int>> mergeSort(vector<tuple<string, int>> A) {
    if (A.size() == 1) {
        return A;
    }
    int mid_idx = A.size() / 2;

    // vector<tuple<string, int>> left, right;
    // for (int i = 0; i < mid_idx; ++i) {
    //     left.push_back(A[i]);
    // }
    // for (int i = mid_idx; i < A.size(); ++i) {
    //     right.push_back(A[i]);
    // }
    // assert(left.size() + right.size() == A.size());
    
    // vector<tuple<string, int>> left_sorted = mergeSort(left);
    // vector<tuple<string, int>> right_sorted = mergeSort(right);

    vector<tuple<string, int>> left_sorted = mergeSort(vector<tuple<string, int>>(A.begin(), A.begin() + mid_idx));
    vector<tuple<string, int>> right_sorted = mergeSort(vector<tuple<string, int>>(A.begin() + mid_idx, A.begin() + A.size()));
    
    merge(A, left_sorted, right_sorted); // merge left_ & right_sorted into A
    
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

    // Start timer
    // AlgTimer timer;
    // timer.Begin();

    // SORT
    vector<tuple<string, int>> sorted_string_and_id = mergeSort(string_and_id);

    outfile << parser.QueryTotalStringCount() << endl;
    for (int i = 0; i < sorted_string_and_id.size(); ++i) {
        outfile << get<0>(sorted_string_and_id[i]) << " " << get<1>(sorted_string_and_id[i]) << endl;
    }
    // cout << compare2strings("z", "za") << endl;
    // outfile << parser.QueryString(i) << " " << i << endl;

    outfile.close();

	// double time = timer.End();
	// cout << "Finished after time: " << time << endl;
 //    getchar();
    cout << "DONE!" << endl;
    return 0;
}