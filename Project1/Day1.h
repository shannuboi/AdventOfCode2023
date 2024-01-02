#pragma once

#include <string>
#include <fstream>
#include <iterator>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>

int Day1Prob1() {
	std::ifstream input("Input.txt");

	int sum = 0;
	std::string line;
	while (std::getline(input, line)) 
	{
		char first = 0;
		for (char c : line) 
		{
			if (std::isdigit(c)) {
				first = c;
				break;
			}
		}

		char last = 0;
		for (auto riter = line.rbegin(); riter != line.rend(); riter++) 
		{
			const char c = *riter;
			if (std::isdigit(c)) {
				last = c;
				break;
			}
		}

		const std::string digits = { first, last };
		const int calibrationVal = std::stoi(digits);
		sum += calibrationVal;
	}
	return sum;
}

class Day1Prob2 {
private:
	typedef std::pair<char, int> digitNpos;
public:
	static int Solve() {
		return Solve("Input.txt");
	}
	static int Solve(const std::string& filename) {
		std::ifstream input(filename);

		int sum = 0;
		std::string line;
		while (std::getline(input, line)) {
			const digitNpos firstNumeric = GetFirstNumericDigit(line);
			const digitNpos lastNumeric = GetLastNumericDigit(line);
			const digitNpos firstWordy = GetFirstWordyDigit(line);
			const digitNpos lastWordy = GetLastWordyDigit(line);
			
			const char first = 
				firstNumeric.second > firstWordy.second ? 
				firstWordy.first : firstNumeric.first;
			const char last =
				lastNumeric.second < lastWordy.second ?
				lastWordy.first : lastNumeric.first;

			const std::string digits = { first, last };
 			const int calibrationVal = std::stoi(digits);
			sum += calibrationVal;
		}
		return sum;
	}
private:
	static digitNpos GetFirstNumericDigit(const std::string& line) {
		char first = 0;
		int firstpos = (int)line.length();
		for (int i = 0; i < line.size(); i++)
		{
			const char c = line[i];
			if (std::isdigit(c)) {
				first = c;
				firstpos = i;
				break;
			}
		}
		return { first, firstpos };
	}
	static digitNpos GetLastNumericDigit(const std::string& line) {
		char last = 0;
		int lastpos = -1;
		for (auto riter = line.rbegin(); riter != line.rend(); riter++)
		{
			const char c = *riter;
			if (std::isdigit(c)) {
				last = c;
				lastpos = (int)std::distance(riter, line.rend()) - 1;
				break;
			}
		}
		return { last, lastpos };
	}
	static digitNpos GetFirstWordyDigit(const std::string& line) {
		digitNpos earliest = { 0, line.size()};
		for (auto i = std::begin(digitNames); 
			i != std::end(digitNames); i++) 
		{
			std::string digit = *i;
			auto iter = std::search(
				line.begin(), line.end(), 
				digit.begin(), digit.end()
			);

			int pos = (int)std::distance(line.begin(), iter);
			if (pos < earliest.second)
				earliest = { digitToChar.at(digit), pos };
		}
		return earliest;
	}
	static digitNpos GetLastWordyDigit(const std::string& line) {
		digitNpos latest = { 0, 0 };
		for (auto i = std::begin(digitNames);
			i != std::end(digitNames); i++)
		{
			std::string digit = *i;
			auto iter = std::search(
				line.rbegin(), line.rend(),
				digit.rbegin(), digit.rend()
			);

			int pos = (int)std::distance(iter, line.rend()) - 1;
			if (pos > latest.second)
				latest = { digitToChar.at(digit), pos };
		}
		return latest;
	}
private:
	static const std::string digitNames[9];
	static const std::unordered_map<std::string, char> digitToChar;
};

const std::string Day1Prob2::digitNames[] = {
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};
const std::unordered_map<std::string, char> Day1Prob2::digitToChar = {
	{"one", '1'}, {"two", '2'}, {"three", '3'}, 
	{"four", '4'}, {"five", '5'}, {"six", '6'}, 
	{"seven", '7'}, {"eight", '8'}, {"nine", '9'}
};