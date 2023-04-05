#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>

using namespace std;

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

void read_ints(std::string file_name) {
	std::vector<int> v;
	std::string line{};
	std::ifstream f(file_name);
	const char delim = 0;

}

/*
class ResManager
{
	
};

*/