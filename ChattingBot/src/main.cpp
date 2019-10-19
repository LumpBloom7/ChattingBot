#include <iostream>
#include <limits>
#include <string>

int main() {
	std::string input;
	while (input != "quit") {
		std::getline(std::cin, input);
		std::cout << input << std::endl;
	}
	return 0;
}
