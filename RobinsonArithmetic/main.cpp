#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "lexer.h"
#include "parser.h"
using namespace std;

const string filename = "source.dat";
fstream try_open_file(const string&);

int main(void) {
	fstream file = try_open_file(filename);
	vector<char> source;
	while (file.peek() != EOF) {
		if (!isgraph(file.peek())) {
			(void)file.get();
			continue;
		}
		char next = file.get();
		source.push_back(next);
	}
	file.close();

	try {
		cout << "lexing..." << endl << endl;
		Lexer lexer(source);
		cout << lexer << endl << endl;

		cout << "parsing..." << endl << endl;
		Parser parser(lexer);
		cout << parser.parse() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
}

fstream try_open_file(const string& filename) {
	fstream f(filename);
	if (!f.is_open()) {
		cerr << "Failed to open " << filename << endl;
		exit(1);
	}
	return f;
}

