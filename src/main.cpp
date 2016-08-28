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


	// main loop
	while(true) {
		
		cout << "> "; // prompt
			
		// Command input
		string input;  
		getline(cin, input); // get input line from STDIN

		// Tokenization, just on whitespace for now
		istringstream iss(input); // open an stream into the input
		vector<string> tokens; // container for tokens
		copy(istream_iterator<string>(iss),
			 istream_iterator<string>(),
			 back_inserter(tokens)); // tokenize
		
		// prepare char *const[] to pass to exec
		vector<char*> ctokens;
		for(auto t: tokens)
			ctokens.push_back(const_cast<char*>(t.c_str()));
		ctokens.push_back(static_cast<char*>(NULL));	
		/*
		unsigned nargs = tokens.size();
		char** args = new char*[nargs+1];
		for(int i = 0; i < tokens.size(); ++i)
			args[i] = (char*)&tokens[i]; // assign the pointers
		args[nargs] = (char*)NULL;
	

		for(int i = 0; i < nargs; ++i)
			cout << i << ": " << args[i] << endl;

		if(args[nargs]==NULL)
				cout << "YESSSS!" << endl;
		*/

		// Expansion
		// TODO: aliases, wildcards
		

		// Fork a new process and wait on it
		// pid_t parent = getpid();
		pid_t pid = fork();
		if(pid < 0) { // failed to fork
			cerr << "Failed to fork!" << endl;
		}
		else if(pid > 0) { // parent pshell
			int status;
			waitpid(pid, &status, 0); // wait on the child process to finish
			// delete[] args; // delete the memory allocated
		}
		else { // child process	
			execvp(ctokens[0], &ctokens[0]);
			cout << "execvp failed!" << endl;
			exit(-1); // exec never returns, so this gets called only if error happens
		}

	}

	return 0;

}
