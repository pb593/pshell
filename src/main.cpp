#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<iterator>
#include<vector>

#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main() {

	string PATH("/bin:/usr/bin"); 
		
	// main loop
	while(true) {
		
		cout << "> "; // prompt
			
		// Command input
		string input;  
		getline(cin, input); // get input line from STDIN

		// Tokenization
		istringstream iss(input); // open an stream into the input
		vector<string> tokens; // container for tokens
		copy(istream_iterator<string>(iss),
			 istream_iterator<string>(),
			 back_inserter(tokens)); // tokenize

		// Expansion
		// TODO: aliases, wildcards
		

		// Fork a new process and wait on it
		pid_t parent = getpid();
		cout << "Parent: pid=" << parent << ". Ready to fork!" << endl;
		pid_t pid = fork();
		if(pid < 0) { // failed to fork
			cerr << "Failed to fork!" << endl;
		}
		else if(pid > 0) { // parent
			int status;
			cout << "Parent: forked OK. Waiting for child." << endl;
			waitpid(pid, &status, 0);
			cout << "Parent: Child done. Status = " << status << ". Continuing." << endl;
		}
		else { // child
			cout << "Child: Hello! I am here. pid=" << getpid() << endl;
			exit(500);
		}

	}

	return 0;

}
