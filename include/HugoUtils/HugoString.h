#pragma once
#include <vector>
#include <string>
namespace HugoUtils
{
	namespace FreezeApiInvalidStrings {
        const std::vector<std::wstring>& GetCorrectStrings();
		void FixInvalidFreezeStrings(std::wstring& response);
	}
}