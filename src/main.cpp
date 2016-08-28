#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<iterator>
#include<vector>
#include<cstdlib>
#include<numeric>

#include<sys/wait.h>
#include<unistd.h>

using namespace std;

template<class T>
void print_vector(vector<T> v) {
	for(int i = 0; i < v.size(); ++i)
		cout << i << ": " << v[i] << endl;
}


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
		

		// Expansion
		// TODO: aliases, wildcards
		
		// Built-in commands
		if(!tokens[0].compare("exit")) { // EXIT commands
			int status = 0;
			// add custom exit status later
			exit(status);
		}
		// Fork a new process and wait on it
		// pid_t parent = getpid();
		pid_t pid = fork();
		if(pid < 0) { // failed to fork
			cerr << "Failed to fork!" << endl;
		}
		else if(pid > 0) { // parent pshell
			int status;
			waitpid(pid, &status, 0); // wait on the child process to finish
		}
		else { // child process	
			
			// prepare char *const[] to pass to exec
			vector<char*> ctokens;
			for(auto t: tokens)
				ctokens.push_back(const_cast<char*>(t.c_str()));
			ctokens.push_back(static_cast<char*>(NULL));	
				
			
			// print_vector(tokens);
			

			execvp(ctokens[0], &ctokens[0]);
			perror("error"); // exec never returns, so this gets called only if error happens
			exit(-1); 
		}

	}

	return 0;

}
