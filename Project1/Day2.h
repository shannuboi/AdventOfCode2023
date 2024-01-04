#pragma once

#include <string>
#include <fstream>
#include <sstream>

class Day2Prob1 {
public:
	static int Solve() {
		return Solve("Input.txt");
	}
	static int Solve(const  std::string& filename) {
		std::ifstream input(filename);

		int sum = 0;
		std::string line = "";
		while (std::getline(input, line)) {
			int gameNum = GameNumIfPossible(line);
			if (gameNum) sum += gameNum;
		}
		return sum;
	}
private:
	static int GameNumIfPossible(const std::string& line) {
		std::stringstream curLine(line);

		std::string buffer = "";
		std::getline(curLine, buffer, ':');
		const int gameNum = std::stoi(buffer.substr(5));

		while (std::getline(curLine, buffer, ';')) {
			if (!IsRoundPossible(buffer))
				return 0;
		}
		return gameNum;
	}
	static bool IsRoundPossible(const std::string& round) {
		std::stringstream curRound(round);

		std::string buffer = "";
		while (std::getline(curRound, buffer, ',')) {
			// Remove initial space and find index of space
			buffer = buffer.substr(1);
			const size_t spaceInd = buffer.find(" ");

			int amount = std::stoi(buffer.substr(0, spaceInd));
			std::string type = buffer.substr(spaceInd + 1);

			if (type == "red" && amount > RED_LIMIT)
				return false;
			if (type == "green" && amount > GREEN_LIMIT)
				return false;
			if (type == "blue" && amount > BLUE_LIMIT)
				return false;
		}
		return true;
	}
private:
	static constexpr int RED_LIMIT = 12;
	static constexpr int GREEN_LIMIT = 13;
	static constexpr int BLUE_LIMIT = 14;
};