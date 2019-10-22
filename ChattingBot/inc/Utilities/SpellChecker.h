#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace chatBot::utilities {
	class SpellChecker {
	public:
		SpellChecker(const std::filesystem::path& dictionaryPath);
		void addWord(const std::string& string);
		void removeWord(const std::string& string);
		std::vector<std::string> checkSpelling(std::string& string);

	private:
		std::unordered_map<std::string, std::string> dictionary;
	};

}
