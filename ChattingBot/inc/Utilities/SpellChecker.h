#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <spellcheck.h>
#include <wrl/client.h>

namespace chatBot::utilities {
	class SpellChecker {
	public:
		SpellChecker();
		void checkSpelling(std::wstring& string);

	private:
		std::unordered_map<std::string, std::string> dictionary;
		Microsoft::WRL::ComPtr<ISpellChecker> checker;
		Microsoft::WRL::ComPtr<IEnumSpellingError> errors;
	};

}
