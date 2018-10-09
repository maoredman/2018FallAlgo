#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.h"
#include "util.h"

using namespace std;

int main( int argc, char** argv )
{	
    AlgParser parser;
    parser.Parse(argv[1]);

    ofstream outfile;
    outfile.open(argv[2]);

    // STORE STRINGS AND THEIR POSITIONS INTO ARRAY (VECTOR)
    vector< tuple<string, int> > string_and_id;
    for( int i = 0 ; i < parser.QueryTotalStringCount() ; i++ ) {
		string_and_id.push_back(make_tuple(parser.QueryString(i), i+1));
	}


    // Start timer
    AlgTimer timer;
    timer.Begin();

    // SORT
    tuple<string, int> key;
    int swap_idx;
    for (int i = 1; i < string_and_id.size(); ++i) { // select current word
        key = string_and_id[i];
        swap_idx = i-1;
        while (swap_idx >= 0) {
            if (compare2strings(get<0>(key), get<0>(string_and_id[swap_idx])) == -1) {
                string_and_id[swap_idx+1] = string_and_id[swap_idx];
                swap_idx--;
            }
            else {
                break;
            }
        }
        string_and_id[swap_idx+1] = key;
    }

    outfile << parser.QueryTotalStringCount() << endl;
    for (int i = 0; i < string_and_id.size(); ++i) {
        outfile << get<0>(string_and_id[i]) << " " << get<1>(string_and_id[i]) << endl;
    }
    // cout << compare2strings("z", "za") << endl;
    // outfile << parser.QueryString(i) << " " << i << endl;

    outfile.close();
	double time = timer.End();
	cout << "Finished after time: " << time << endl;
    getchar();
    return 0;
}