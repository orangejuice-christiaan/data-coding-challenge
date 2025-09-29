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
	std::ifstream file { "C:/Git/data-coding-challenge/App/Source/resources/input-tiny.csv" };

	if (!file)
	{
		std::cerr << "Could not find/open file.\n";
		return 1;
	}

	int i { 0 };

	Timer t;

	std::string longestName{ "TODO" };

	const size_t BUFFER_SIZE = 64 * 1024; // 64 KB
	std::vector<char> buffer(BUFFER_SIZE);

	while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
		size_t count = file.gcount();
		size_t lineCount = 0;
		size_t fieldCount = 0;
		for (size_t i = 0; i < count; ++i) {
			char ch = buffer[i];

			// process ch
		}
	}

	std::cout << longestName << "\n";
	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

	return 0;
}

/*processData(strInput, [&longestName](auto& fields)
	{
		getLongestName(fields, longestName);
	}, fieldsBuffer);*/