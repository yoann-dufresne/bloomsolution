#include <fstream>
#include <string>


#ifndef SEQ_READ_H
#define SEQ_READ_H

class SeqReader {
private:
	std::ifstream stream;
public:
	/** Construct a sequence reader.
	  * Read the char one by one when next is called.
	  **/
	SeqReader(std::string filename);
	/** Get the next nucleotide in the sequence.
	  * Jump over the title, \n and N nucleotides
	  * @return Next nucleotide or 0 if eof
	  **/ 
	char next();
};

#endif
