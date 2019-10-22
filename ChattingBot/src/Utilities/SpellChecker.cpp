#include "Utilities/SpellChecker.h"

namespace chatBot::utilities {
	SpellChecker::SpellChecker(const std::filesystem::path& dictionaryPath) {
		std::ifstream input(dictionaryPath);
		while (!input.eof()) {
			std::string string;
			input >> string;
			dictionary.emplace(string, string);
		}
	}
	void SpellChecker::addWord(const std::string& string) {
		dictionary.emplace(string, string);
	}
	void SpellChecker::removeWord(const std::string& string) {
		dictionary.erase(string);
	}

	std::vector<std::string> SpellChecker::checkSpelling(std::string& string) {
		std::transform(string.begin(), string.end(), string.begin(),
			[](unsigned char c) { return std::tolower(c); });

		std::vector<std::string> possibilities;

		if (dictionary.find(string) == dictionary.end()) {
			for (int i = 0; i < string.length(); ++i) {
				std::string tmp = string;
				for (char newChar = 'a'; newChar <= 'z'; ++newChar) {
					tmp[i] = newChar;
					auto it = dictionary.find(tmp);
					if (it != dictionary.end())
						possibilities.emplace_back(it->second);
				}
			}
		}
		return possibilities;
	}


}