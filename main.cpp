#include <iostream>

#include "seq_reader.hpp"
#include "kmer.hpp"
#include "bloom.hpp"

using namespace std;


int main(int argc, char const *argv[]) {
	// Parameters
	string filename = "data/hg_chr1.fasta";
	uint64_t k = 27;
	uint64_t num_hash = 2;
	uint64_t bloom_size = 1ul << 32;

	// Init objects and useful variables
	char c = 0;
	SeqReader reader(filename);
	KmerManipulator manip(k);
	BloomFilter bf(bloom_size, num_hash);

	// Init the first (k-1)-mer
	for (uint i=0 ; i<k-1 ; i++) {
		c = reader.next();
		manip.construct_next(c);
	}

	// Process the data
	while ((c = reader.next())) {
		// Construct the kmer
		manip.construct_next(c);
		// cout << manip.current_kmer << " " << manip.current_rev << endl;
		// Only keeps the first kmer/rev-kmer in the lexicographic order
		uint64_t used_kmer = min(manip.current_kmer, manip.current_rev);
		// Insert the k-mer
		// cout << "add " << used_kmer << endl; 
		bf.add_value(used_kmer);
	}
	// cout << endl;
	// bf.print_bloom();

	return 0;
}
