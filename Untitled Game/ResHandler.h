#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>

using namespace std;

inline void read_ints(std::string file_name, int* writeTo) {
	// create output from file stream object
	std::ifstream myFile(file_name);

	std::string line, word;
	int i = 0;

	if (myFile.is_open()) {
		while (!myFile.eof()) {

			// get individual line
			getline(myFile, line);

			// create stringstream object from line
			stringstream s(line);

			// choose delimeter
			char delim = ',';

			while (getline(s, word, delim)) {
				if (word == " " || word == "\n" || word == "\t")
					continue;
				// converte string to int
				int num = stoi(word);

				// write int to array
				writeTo[i] = num;
				i++;
			}
		}
		// close the file
		myFile.close();
	}
}
