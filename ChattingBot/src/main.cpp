#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Utilities/SpellChecker.h"

int main() {
	chatBot::utilities::SpellChecker spellCheck("dictionary.txt");
	std::string input;
	while (input != "quit") {
		std::getline(std::cin, input); // Input sentence ending with a line-break.
		input.erase(std::remove_if(input.begin(), input.end(), ispunct), input.end());
		std::stringstream ss(input);
		std::string tmp;
		std::vector<std::pair<std::string, std::vector<std::string>>> errorList;

		std::cout << "Interpreted input: " << input << std::endl; // Echo the input for test purposes.
		while (ss >> tmp) {
			auto errors = spellCheck.checkSpelling(tmp);
			if (!errors.empty()) errorList.emplace_back(std::make_pair(tmp, errors));
		}

		if (!errorList.empty()) {
			std::cout << "Errors found: " << std::endl;
			for (auto& i : errorList) {
				std::cout << "\t" << i.first << std::endl;
				std::cout << "\tPossible corrections: " << std::endl;
				for (auto& errors : i.second) {
					std::cout << "\t\t" << errors << std::endl;
				}
			}
		}

	}
	return 0;
}
