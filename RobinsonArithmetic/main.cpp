#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "nat.h"
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
		cout << "lexing..." << endl;
		for (char c : source) cout << c;
		cout << endl;

		Lexer lexer(source);
		cout << lexer << endl;

		cout << "parsing..." << endl;
		Parser parser(lexer);
		Node* tree = parser.parse();
		cout << endl;
		cout << "parse succeeded: " << (tree!=nullptr) << endl;

		if (tree) {
			Interpreter bob(tree);
			delete tree;
		}
		
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

