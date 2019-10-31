#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <locale>
#include <codecvt>
#include <string>
#include "Utilities/SpellChecker.h"

int main() {
	chatBot::utilities::SpellChecker spellCheck = chatBot::utilities::SpellChecker();
	std::string input;
	auto text = L"Can I I heav some?";
	while (input != "quit") {
		std::getline(std::cin, input); // Input sentence ending with a line-break.
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(input);
		input.erase(std::remove_if(input.begin(), input.end(), ispunct), input.end());
		std::stringstream ss(input);
		std::string tmp;
		std::vector<std::pair<std::string, std::vector<std::string>>> errorList;

		std::cout << "Interpreted input: " << input << std::endl; // Echo the input for test purposes.
		spellCheck.checkSpelling(wide);
		/*if (!errorList.empty()) {
			std::cout << "Errors found: " << std::endl;
			for (auto& i : errorList) {
				std::cout << "\t" << i.first << std::endl;
				std::cout << "\tPossible corrections: " << std::endl;
				for (auto& errors : i.second) {
					std::cout << "\t\t" << errors << std::endl;
				}
			}
		}*/
		std::string narrow = converter.to_bytes(wide);
		std::cout << "Corrected input: " << narrow << std::endl; // Echo the input for test purposes.
	}
	return 0;
}
