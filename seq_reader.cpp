#include "seq_reader.hpp"

using namespace std;

SeqReader::SeqReader(std::string filename) : stream(filename) {};

char SeqReader::next() {
	// Reading problem or end of the file
	if (this->stream.bad() or this->steam.eof())
		return 0;

	// Read a useful char
	char c = 'N';
	this->stream >> c;
	// Problem or end of the stream
	if (this->stream.bad() or this->steam.eof())
		return 0;
	// Header detected
	else if (c == '>')
		// Read the full line
		while (c != '\n') this->stream >> c;
		return this->next();
	// Unwanted char
	else if (c == 'N' or c == '\n')
		return this->next();

	return c;
}
