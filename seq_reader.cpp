#include <iostream>

#include "seq_reader.hpp"

using namespace std;

SeqReader::SeqReader(std::string filename) : stream(filename) {
	if (not this->stream.is_open()) {
		cerr << "File " << filename << " cannot be open" << endl;
		exit(1);
	}
};

char SeqReader::next() {
	// Reading problem or end of the file
	if (this->stream.bad() or this->stream.eof())
		return 0;

	// Read a useful char
	char c = 'N';
	this->stream.get(c);
	// Problem or end of the stream
	if (this->stream.bad() or this->stream.eof())
		return 0;
	// Header detected
	else if (c == '>') {
		// Read the full line
		while (c != '\n') this->stream.get(c);
		return this->next();
	}
	// Unwanted char
	else if (c == 'N' or c == '\n') {
		return this->next();
	}

	return c;
}
