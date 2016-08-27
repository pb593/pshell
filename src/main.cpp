#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<iterator>
#include<vector>
#include<cstdlib>

#include<sys/wait.h>
#include<unistd.h>

using namespace std;

int main() {

	string PATH = getenv("PATH"); 
	cout << PATH << endl;


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
		else if(pid > 0) { // parent pshell
			int status;
			waitpid(pid, &status, 0); // wait on the child process to finish
		}
		else { // child process
			//execve()		
			exit(-1); // exec never returns, so this gets called only if error happens
		}

	}

	return 0;

}
