#include <iostream>

#include "seq_reader.hpp"
#include "kmer.hpp"

using namespace std;


int main(int argc, char const *argv[]) {
	// Parameters
	string filename = "data/test.fasta";
	uint64_t k = 3;

	// Init objects and useful variables
	char c = 0;
	SeqReader reader(filename);
	KmerManipulator manip(k);

	// Init the first (k-1)-mer
	for (uint i=0 ; i<k-1 ; i++) {
		c = reader.next();
		cout << c << " ";
		manip.construct_next(c);
		cout << manip.current_kmer << " " << manip.current_rev << endl;
	}
	cout << endl;

	// Process the data
	while ((c = reader.next())) {
		cout << c << " ";
		manip.construct_next(c);
		cout << manip.current_kmer << " " << manip.current_rev << endl;
	}
	cout << endl;

	return 0;
}
