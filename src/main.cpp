#include<iostream> // import new 
#include<string>
#include<sstream>
#include<algorithm>
#include<iterator>
#include<vector>

using namespace std;

int main() {

	// main loop
	while(true) {
		
		// Command input
		string input;  
		getline(cin, input); // get input line from STDIN

		// Tokenization
		istringstream iss(input); // open an stream into the input
		vector<string> tokens; // container for tokens
		copy(istream_iterator<string>(iss),
			 istream_iterator<string>(),
			 back_inserter(tokens)); // tokenize

		// Test tokenization
		for(auto t: tokens)
			cout  << t << endl;
		

	}

	return 0;

}
