#pragma once

#include <string>
#include <fstream>
#include <cctype>
#include <iterator>

int Day1Prob1() {
	std::ifstream input("Input.txt");

	int sum = 0;
	std::string line;
	while (std::getline(input, line)) {

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