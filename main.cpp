#include <iostream>

#include "seq_reader.hpp"

using namespace std;


int main(int argc, char const *argv[]) {
	string filename = "data/test.fasta";

	SeqReader reader(filename);
	char c = 0;
	while ((c = reader.next())) {
		cout << c;
	}
	cout << endl;

	return 0;
}
