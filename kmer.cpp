#include <iostream>
#include "kmer.hpp"

using namespace std;

KmerManipulator::KmerManipulator(uint64_t k) : k(k) {
  // Create a mask of size (k-1) * 2 bits
  // If k = 3 => mask = 001111
  this->mask = (1 << (2 * (k-1))) - 1;
  cout << mask << endl;

  this->current_kmer = 0;
  this->current_rev = 0;
}


void KmerManipulator::construct_next(char nucl) {
  // --- Forward k-mer ---
  // Mask the kmer to remove the first nucleotide
  this->current_kmer &= this->mask;
  // Shift the current kmer to the left to have 2 bits available on the right for the new nucleotide
  this->current_kmer <<= 2;
  // New nucleotide
  uint64_t bin_nucl = 0;
  switch(nucl) {
    case 'A': bin_nucl=0; break;
    case 'C': bin_nucl=1; break;
    case 'G': bin_nucl=2; break;
    case 'T': bin_nucl=3; break;
  }
  this->current_kmer |= bin_nucl;

  // --- Reverse complement k-mer ---
  // No need to mask the rev. The shift will destroy the 2 bits on the right
  // Shift the current kmer to the right to have 2 bits available on the left for the new nucleotide
  this->current_rev >>= 2;
  // New nucleotide
  bin_nucl = 0;
  switch(nucl) {
    case 'A': bin_nucl=3; break;
    case 'C': bin_nucl=2; break;
    case 'G': bin_nucl=1; break;
    case 'T': bin_nucl=0; break;
  }
  // Shift the nucleotide to be on the leftmost position
  bin_nucl <<= 2 * (k - 1);
  // Merge nucleotide
  this->current_rev |= bin_nucl;
}
