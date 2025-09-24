#include "Util.h"
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

void processData(const std::string& line, const std::function<void(const std::vector<std::string_view>&)>& fn, std::vector<std::string_view>& fieldsBuffer)
{
	splitCsvLine(line, fieldsBuffer);
	fn(fieldsBuffer);
}

void getLongestName(const std::vector<std::string_view>& fields, std::string& currentLongestName)
{
	const auto& firstName = fields[2];
	const auto& lastName = fields[3];
	const auto nameLength = std::ssize(firstName) + std::ssize(lastName);

	if (nameLength > std::ssize(currentLongestName))
		currentLongestName = std::format("{} {}", firstName, lastName);
}

int main()
{
	std::ifstream inf { "D:/Github/data-coding-challenge/App/Source/resources/input-small.csv" };

	if (!inf)
	{
		std::cerr << "Could not find/open file.\n";
		return 1;
	}

	int i { 0 };

	Timer t;

	std::string strInput {};
	std::string longestName {};

	std::vector<std::string_view> fieldsBuffer;
	fieldsBuffer.reserve(12);

	while (std::getline(inf, strInput))
	{
		if (i != 0)
			processData(strInput, [&longestName](auto& fields)
				{
					getLongestName(fields, longestName);
				}, fieldsBuffer);
		++i;
	}

	std::cout << longestName << "\n";
	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

	return 0;
}