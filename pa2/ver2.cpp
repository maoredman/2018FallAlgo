#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void print_chords(int i, int j, map< pair<int,int>, vector<pair<int,int>> > &saved_mps_chords, ofstream &outfile) {
    if (saved_mps_chords[make_pair(i,j)].size() == 3) {
        print_chords(saved_mps_chords[make_pair(i,j)][0].first, saved_mps_chords[make_pair(i,j)][0].second, saved_mps_chords, outfile);
        outfile << endl << saved_mps_chords[make_pair(i,j)][1].first << " " << saved_mps_chords[make_pair(i,j)][1].second;
        print_chords(saved_mps_chords[make_pair(i,j)][2].first, saved_mps_chords[make_pair(i,j)][2].second, saved_mps_chords, outfile);
    }
    else if (saved_mps_chords[make_pair(i,j)].size() == 1) {
        print_chords(saved_mps_chords[make_pair(i,j)][0].first, saved_mps_chords[make_pair(i,j)][0].second, saved_mps_chords, outfile);
    }
    return;
}

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
    saved_mps_chords[pair1] = {};
    saved_mps_chords[pair2] = {};
  }

  for (int j=1; j<two_times_N; j++) {
    int k = point2point[j];
    for (int i=0; i < j; i++) {
        if ((i <= k) && (k <= j-1) && (saved_mps[make_pair(i,k-1)]+1+saved_mps[make_pair(k+1,j-1)] > saved_mps[make_pair(i,j-1)])) {
            saved_mps[make_pair(i,j)] = saved_mps[make_pair(i,k-1)]+1+saved_mps[make_pair(k+1,j-1)];
            saved_mps_chords[make_pair(i,j)] = {make_pair(i,k-1), make_pair(k,j), make_pair(k+1, j-1)};
        }
        else {
            saved_mps[make_pair(i,j)] = saved_mps[make_pair(i,j-1)];
            saved_mps_chords[make_pair(i,j)] = {make_pair(i, j-1)};
        }
    }
  }
  
  ofstream outfile;
  outfile.open(argv[2]);
  cout << "Max: " << saved_mps[make_pair(0,two_times_N-1)] << endl;
  outfile << saved_mps[make_pair(0,two_times_N-1)];
  print_chords(0,two_times_N-1, saved_mps_chords, outfile);

  // for(auto& x : point2point) {
  //     std::cout << x.first << "," << x.second << endl;
  // }

  return 0;
}