#include <cstdint>

#ifndef KMER_H
#define KMER_H

class KmerManipulator {
private:
	uint64_t k;
	uint64_t mask;

public:
	// Where the current kmer is stored
	uint64_t current_kmer;
	// Where the current reverse complement kmer is stored
	uint64_t current_rev;

	/** Constructor for a kmer manipulator with the encoding A:0, C:1, G:2, T:3
	 * Always keeps up to date the current kmer and its reverse complement
	 */
	KmerManipulator(uint64_t k);
	/** Construct a kmer from the previous one + the last char.
	 * 1 - Remove the useless nucleotide by masking + shifting
	 * 2 - Add the new nucleotide
	 * @param nucl The new nucleotide to add
	 **/
	void construct_next(char nucl);

	/** Generate the reverse complement of a kmer
	 * @param Kmer to reverse complement
	 * @return reverse complement
	 */
	uint64_t rev_comp(uint64_t kmer);
};

#endif