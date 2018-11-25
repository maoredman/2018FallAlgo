#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main (int argc, char** argv) {  
  int two_times_N;
  map<int, int> point2point;

  ifstream myfile (argv[1]);
  if (myfile.is_open()) {
    string line;
    getline(myfile,line);
    two_times_N = stoi(line);
    // cout << "2n is " << two_times_N << '\n';
    while ( getline (myfile,line) ) {
      if (line == "0") break;
      size_t pos = line.find(" ");
      int point1 = stoi(line.substr(0, pos));
      int point2 = stoi(line.substr(pos+1, string::npos));
      point2point[point1] = point2;
      point2point[point2] = point1;
      // cout << point1 << "," << point2 << '\n';
    }
    myfile.close();
  } else {
    cout << "Unable to open file\n";
  }

  map<pair<int,int>, int> saved_mps;
  map<pair<int,int>, vector<pair<int,int> > > saved_mps_chords;
  for (int idx=0; idx < two_times_N; idx++) { // initialize
    pair<int, int> pair1 = make_pair(idx, idx);
    pair<int, int> pair2 = make_pair(idx, idx-1);
    saved_mps[pair1] = 0;
    saved_mps[pair2] = 0;
    saved_mps_chords[pair1] = vector<pair<int,int> > ();
    saved_mps_chords[pair2] = vector<pair<int,int> > ();
  }

  for (int l=1; l < two_times_N; l++) { // "length" of chord, 1~(2n-1)
    for (int start_idx=0; start_idx < two_times_N - l; start_idx++) {
        int end_idx = start_idx+l;
        int k = point2point[end_idx];
        // pair<int, int> this_pair = make_pair(start_idx, end_idx);
        if (k == start_idx) { // case 3
            saved_mps[make_pair(start_idx, end_idx)] = saved_mps[make_pair(start_idx+1, end_idx-1)] + 1;

            // vector<pair<int,int> > this_vector;
            // this_vector.push_back(make_pair(start_idx, end_idx));
            // vector<pair<int,int> > other_vector = saved_mps_chords[make_pair(start_idx+1, end_idx-1)];
            // this_vector.insert(this_vector.end(), other_vector.begin(), other_vector.end() );
            // saved_mps_chords[make_pair(start_idx, end_idx)] = this_vector;
        }
        else if (k > start_idx && k < end_idx) { // case 2
            int candidate = saved_mps[make_pair(start_idx, k-1)] + 1 + saved_mps[make_pair(k+1, end_idx-1)];
            if (candidate > saved_mps[make_pair(start_idx, end_idx-1)]) {
                saved_mps[make_pair(start_idx, end_idx)] = candidate;

                // vector<pair<int,int> > this_vector = saved_mps_chords[make_pair(start_idx, k-1)];
                // this_vector.push_back(make_pair(k, end_idx));
                // vector<pair<int,int> > other_vector = saved_mps_chords[make_pair(k+1, end_idx-1)];
                // this_vector.insert(this_vector.end(), other_vector.begin(), other_vector.end() );
                // saved_mps_chords[make_pair(start_idx, end_idx)] = this_vector;
            }
            else {
                saved_mps[make_pair(start_idx, end_idx)] = saved_mps[make_pair(start_idx, end_idx-1)];
                // saved_mps_chords[make_pair(start_idx, end_idx)] = saved_mps_chords[make_pair(start_idx, end_idx-1)];
            }
        }
        else { // case 1
            saved_mps[make_pair(start_idx, end_idx)] = saved_mps[make_pair(start_idx, end_idx-1)];
            // saved_mps_chords[make_pair(start_idx, end_idx)] = saved_mps_chords[make_pair(start_idx, end_idx-1)];
        }
    }
  }

  ofstream outfile;
  outfile.open(argv[2]);
  cout << "Max: " << saved_mps[make_pair(0,two_times_N-1)] << endl;
  outfile << saved_mps[make_pair(0,two_times_N-1)];
  // for (int i=0; i < saved_mps_chords[make_pair(0,two_times_N-1)].size(); i++) {
  //     // pair<int,int> this_pair = saved_mps_chords[make_pair(0,two_times_N-1)][i];
  //     // cout << saved_mps_chords[make_pair(0,two_times_N-1)][i].first << ' ' << saved_mps_chords[make_pair(0,two_times_N-1)][i].second << '\n';
  //     outfile << endl << saved_mps_chords[make_pair(0,two_times_N-1)][i].first << ' ' << saved_mps_chords[make_pair(0,two_times_N-1)][i].second;
  // }

  // for(auto& x : point2point) {
  //     std::cout << x.first << "," << x.second << endl;
  // }

  return 0;
}