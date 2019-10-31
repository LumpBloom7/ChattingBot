#pragma once
#include <iostream>
#include <locale>
#include <codecvt>
#include <string>
#include <spellcheck.h>
#include <wrl/client.h>

namespace chatBot::utilities {
	class SpellChecker {
	public:
		SpellChecker();
		std::string checkSpelling(std::string& string);

	private:
		Microsoft::WRL::ComPtr<ISpellChecker> checker;
		Microsoft::WRL::ComPtr<IEnumSpellingError> errors;
	};

}
