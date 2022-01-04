#include <cstdint>


#ifndef BLOOM_H
#define BLOOM_H

class BloomFilter {
private:
	// uint8_t has been replaced by uint64_t for speed improvements.
	// 64 bits integer are aligned in cache not all 8-bits words.
	uint64_t * array;
	uint64_t * hash_space;
	uint64_t num_bits;
	uint64_t num_hash;
public:
	/** Construct a bloom filter of size size
	  * @param size Size in bits of the bloom filter
	  * @param num_hash Number of hash functions to use
	  **/
	BloomFilter(uint64_t size, uint64_t num_hash);
	/** Destructor needed to deallocate the bloom space */
	~BloomFilter();
	/** Add the value x to the bloom filter
	  * @param x Value to add
	  **/
	void add_value(uint64_t x);
	/** Check is a value x is in the bloom filter.
	  * @param x Value to check
	  * @retun False is the value is not there. True if the value is present or a collision occured.
	  **/
	bool is_present(uint64_t x);

	/** Print the bloom filter content.
	 * WARNING: This function should not be used in production or for large BF
	 **/
	void print_bloom();
};

#endif
