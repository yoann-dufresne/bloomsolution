#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <cstring>

#include "seq_reader.hpp"
#include "kmer.hpp"
#include "bloom.hpp"

using namespace std;


int main(int argc, char const *argv[]) {
	// Parameters
	string filename = "data/hg_chr1.fasta";
	uint64_t k = 31;
	uint64_t num_hash = 2;
	uint64_t bloom_size = 1ul << 33;
	uint64_t r = 1000000;

	/*   #         fichier          k    n   nf   r
      ./monprog data/ecoli.fasta 31 456637 3 10000
	*/
	// parsing args
	if (argc != 6) {
		cerr << "Wrong command line. Command example:" << endl;
		// I should explain the numbers here
		cerr << "./bloom_test data/ecoli.fasta 31 456637 3 10000" << endl;
		exit(1);
	}
	filename = string(argv[1]);

	k = atoi(argv[2]);
	bloom_size = stoull(string(argv[3])); // For large value parsing
	num_hash = atoi(argv[4]);
	r = stoull(string(argv[5])); // For large value parsing

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
	cout << "Filling the bloom filter" << endl;
	uint64_t num_kmers = 0;
	while ((c = reader.next())) {
		// Construct the kmer
		manip.construct_next(c);
		// cout << manip.current_kmer << " " << manip.current_rev << endl;
		// Only keeps the first kmer/rev-kmer in the lexicographic order
		uint64_t used_kmer = min(manip.current_kmer, manip.current_rev);

		num_kmers += 1;
		// Insert the k-mer
		// cout << "add " << used_kmer << endl;
		bf.add_value(used_kmer);

		if (num_kmers % 50000000 == 0) {
			cout << (num_kmers/1000000) << "M kmers registered in the BF" << endl;
		}
	}
	cout << "Total kmer registered " << num_kmers << endl;
	cout << endl;

	// for (uint i=0 ; i<(1<<(2*k)) ; i++)
	// 	if (counts[i] == 0)
	// 		cout << i << " " << counts[i] << endl;

	cout << "Requesting random kmers" << endl;
	uint64_t nb_found = 0;
	// Random number generator
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<uint64_t> distribution(0,(1ul << (2*k))-1);
	for (uint64_t i=0 ; i<r ; i++) {
		// Generate a random number
		uint64_t kmer = distribution(generator);
		// Get the minimum with reverse complement
		kmer = min(kmer, manip.rev_comp(kmer));
		// Is the kmer present ?
		if (bf.is_present(kmer)) 
			nb_found += 1;
	}
	cout << nb_found << "/" << r << " random kmer found" << endl;
	cout << endl;
	return 0;
}
