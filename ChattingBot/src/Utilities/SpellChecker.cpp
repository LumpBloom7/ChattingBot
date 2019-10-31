#include "Utilities/SpellChecker.h"

namespace chatBot::utilities {
	SpellChecker::SpellChecker() {
		HRESULT HR;
		HR = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		if (S_OK != HR) throw std::exception("ERROR: Failed to initialize spell checking COM Lib");

		Microsoft::WRL::ComPtr<ISpellCheckerFactory> factory;

		HR = CoCreateInstance(__uuidof(SpellCheckerFactory),
			nullptr,
			CLSCTX_INPROC_SERVER,
			__uuidof(factory),
			reinterpret_cast<void**>(factory.GetAddressOf()));

		BOOL supported;

		HR = factory->IsSupported(L"en-US", &supported);

		if (!supported) { throw std::exception("ERROR: en-US is not supported by spell checking API"); }

		HR = factory->CreateSpellChecker(L"en-US", checker.GetAddressOf());

	}

	void SpellChecker::checkSpelling(std::wstring& string) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		HRESULT HR = checker->Check(string.c_str(), errors.GetAddressOf());

		for (;;)
		{
			Microsoft::WRL::ComPtr<ISpellingError> error;

			if (S_OK != errors->Next(error.GetAddressOf()))
			{
				break;
			}

			// Respond to each error here!
			ULONG startIndex;
			HR = error->get_StartIndex(&startIndex);

			ULONG length;
			HR = error->get_Length(&length);

			std::wstring word(string.c_str() + startIndex,
				string.c_str() + startIndex + length);

			CORRECTIVE_ACTION action;
			HR = error->get_CorrectiveAction(&action);

			if (action == CORRECTIVE_ACTION_DELETE) {
				if (startIndex != 0) --startIndex, ++length;
				string.erase(string.begin() + startIndex, string.begin() + startIndex + length);
				HR = checker->Check(string.c_str(), errors.GetAddressOf());

				std::cout << "[SPELLCHECKER] Deleting \'" << converter.to_bytes(word) << "\' from input" << std::endl;
			}
			else if (action == CORRECTIVE_ACTION_REPLACE) {
				wchar_t* replacement;
				HR = error->get_Replacement(&replacement);

				string.replace(string.begin() + startIndex, string.begin() + startIndex + length, replacement);
				std::cout << "[SPELLCHECKER] Replacing \'" << converter.to_bytes(word) << "\' from input with \'" << converter.to_bytes(replacement) << "\'" << std::endl;
				CoTaskMemFree(replacement);
				HR = checker->Check(string.c_str(), errors.GetAddressOf());
			}
			else if (action == CORRECTIVE_ACTION_GET_SUGGESTIONS) {
				Microsoft::WRL::ComPtr<IEnumString> suggestions;

				HR = checker->Suggest(word.c_str(), suggestions.GetAddressOf());
				for (;;)
				{
					wchar_t* suggestion;

					if (S_OK != suggestions->Next(1, &suggestion, nullptr))
					{
						break;
					}
					string.replace(string.begin() + startIndex, string.begin() + startIndex + length, suggestion);
					std::cout << "[SPELLCHECKER] Replacing \'" << converter.to_bytes(word) << "\' with likely replacement " "\'" << converter.to_bytes(suggestion) <<"\'"<< std::endl;
					// Add the suggestion to a list for presentation

					CoTaskMemFree(suggestion);
					HR = checker->Check(string.c_str(), errors.GetAddressOf());
					break;
				}
			}
		}
	}
}