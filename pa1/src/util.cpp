#include <string>
#include <iostream>

using namespace std;

int compare2strings(string a, string b) {
	// outputs smaller string's index
	// outputs smaller string's index
	if (a == b) {
	    return 0;
	}
	else {
	    for (int i = 0; i < a.length(); ++i) {
	        if (int(a[i]) < int(b[i])) {
	            return -1;
	        }
	        else if (int(a[i]) > int(b[i])) {
	            return 1;
	        }
	        else if ( i == a.length()-1 ) { // two chars are equal, len(a) < len(b)
	            return -1;
	        }
	        else if ( i == b.length()-1 ){ // two chars are equal, len(a) > len(b)
	            return 1;
	        }

	    }
	}
	cout << "Should not jump here!!!" << endl;
	return 0;
}