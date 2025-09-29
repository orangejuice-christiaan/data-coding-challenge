#include "Util.h"
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

int main()
{
	std::ifstream file { "C:/Git/data-coding-challenge/App/Source/resources/input-large.csv" };

	if (!file)
	{
		std::cerr << "Could not find/open file.\n";
		return 1;
	}

	Timer t;

	std::string longestFirstName;
	std::string longestLastName;

	const size_t BUFFER_SIZE = 64 * 1024; // 64 KB
	std::vector<char> buffer(BUFFER_SIZE);

	size_t lineCount = 0;
	size_t fieldCount = 0;
	bool inQuotes = false;

	std::vector<char> firstNameBuffer;
	firstNameBuffer.reserve(256);

	std::vector<char> secondNameBuffer;
	secondNameBuffer.reserve(256);

	while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
		size_t count = file.gcount();
		for (size_t i = 0; i < count; ++i) {
			char ch = buffer[i];

			if (lineCount == 0 && ch == '\n') {
				++lineCount;
				fieldCount = 0;
				continue;
			}
			if (lineCount == 0) continue;

			if (ch == '"') {
				inQuotes = !inQuotes;
			}
			else if (ch == ',' && !inQuotes) {
				++fieldCount;
			}
			else if (ch == '\n' && !inQuotes) {
				if (std::ssize(firstNameBuffer) + std::ssize(secondNameBuffer) > std::ssize(longestFirstName) + std::ssize(longestLastName)) {
					longestFirstName.assign(firstNameBuffer.data(), firstNameBuffer.size());
					longestLastName.assign(secondNameBuffer.data(), secondNameBuffer.size());
				}

				firstNameBuffer.clear();
				secondNameBuffer.clear();

				fieldCount = 0;
			}
			else {
				if (fieldCount == 2) {
					firstNameBuffer.push_back(ch);
				}

				if (fieldCount == 3) {
					secondNameBuffer.push_back(ch);
				}
			}
		}
	}

	std::cout << longestFirstName << " " << longestLastName << "\n";
	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

	return 0;
}
