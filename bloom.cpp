#include "hash.hpp"
#include "bloom.hpp"

BloomFilter::BloomFilter(uint64_t size, uint64_t num_hash) : num_bits(size), num_hash(num_hash) {
	// Allocate the bloom filter space
	uint64_t number_of_uint = (size + 63) / 64;
	this->array = new uint64_t[number_of_uint];
	this->hash_space = new uint64_t[num_hash];
}

BloomFilter::~BloomFilter() {
	delete[] this->array;
}

void BloomFilter::add_value(uint64_t x) {
	// Hash x (x+1 to avoid the value 0 that always hash to 0)
	multihash(x+1, this->hash_space, this->num_hash, this->num_bits-1);

	// Enter ones in the BF
	for (uint i=0 ; i<this->num_hash ; i++) {
		// Get the current hash
		h = this->hash_space[i];
		// Extract the uint idx to modify
		uint_idx = h / 64;
		// Extract the bit idx to modify
		bit_idx = h % 64;

		// Modify the BF
		uint64_t bit = 1 << bit_idx;
		this->array[uint_idx] |= bit;
	}
}

bool BloomFilter::is_present(uint64_t x) {
	// Hash x (x+1 to avoid the value 0 that always hash to 0)
	multihash(x+1, this->hash_space, this->num_hash, this->num_bits-1);

	// Looks for ones in the BF
	for (uint i=0 ; i<this->num_hash ; i++) {
		// Get the current hash
		h = this->hash_space[i];
		// Extract the uint idx to check
		uint_idx = h / 64;
		// Extract the bit idx to check
		bit_idx = h % 64;

		// Modify the BF
		uint64_t bit = this->array[uint_idx] >> bit_idx & 0b1;
		if (not bit)
			return false;
	}

	return true;
}
