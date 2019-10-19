#include <iostream>
#include <limits>
#include <string>

int main() {
	std::string input;
	while (input != "quit") {
		std::getline(std::cin, input); // Input sentence ending with a line-break.
		std::cout << input << std::endl; // Echo the input for test purposes.
	}
	return 0;
}
