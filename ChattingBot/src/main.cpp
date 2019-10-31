#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Utilities/SpellChecker.h"

int main() {
	chatBot::utilities::SpellChecker spellCheck;
	std::string input;
	while (input != "quit") {
		std::getline(std::cin, input); // Input sentence ending with a line-break.
		std::cout << "Received input: " << input << std::endl; // Echo the input for test purposes.
		input = spellCheck.checkSpelling(input);
		std::cout << "Corrected input: " << input << std::endl; // Echo the corrected input for test purposes.
	}
	return 0;
}
