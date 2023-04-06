#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>

using namespace std;


/*
	Handles loading in resources int memeory from file.
	Loads textures, sounds, shaders, maps, and other data
*/

/*
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename) {

	std::vector<std::pair<std::string, std::vector<int>>> result;

	std::ifstream myFile(filename);

	if (!myFile.is_open()) throw std::runtime_error("Could not open file");

	std::string line, colname;
	int val;

	if (myFile.good()) {

		std::getline(myFile, line);

		std::stringstream ss(line);

		while (std::getline(ss, colname, ',')) {
			result.push_back({ colname, std::vector<int> {} });
		}
	}
	while (std::getline(myFile, line)) {

		std::stringstream ss(line);

		int colIdx = 0;

		while (ss >> val) {
			result.at(colIdx).second.push_back(val);

			if (ss.peek() == ',')
				ss.ignore();

			colIdx++;
		}
	}

	myFile.close();
	return result;
}
*/
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


/*
class ResHandler {
public:


private:


};
*/