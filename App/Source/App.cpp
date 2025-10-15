#include "Util.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void SetNewLongestName(int& firstLen, int& lastLen, int& bestLen, std::string& longestFirst, char firstName[512], std::string& longestLast, char  lastName[512], int& field)
{
	int totalLen = firstLen + lastLen;
	if (totalLen > bestLen)
	{
		longestFirst = std::string(firstName, firstLen);
		longestLast = std::string(lastName, lastLen);
		bestLen = totalLen;
	}
	firstLen = lastLen = 0;
	field = 0;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	if (argc < 2) {
		std::cerr << "Usage: App.exe <path-to-file>\n";
		return 1;
	}

	std::string filePath = argv[1];
	FILE* file = fopen(filePath.c_str(), "rb");
	if (!file) { perror("fopen"); return 1; }

	Timer t;

	const size_t BUFFER_SIZE = 1024 * 1024; // 1024 KB
	std::vector<char> buffer(BUFFER_SIZE);
	size_t bytesRead;

	char firstName[512];
	char lastName[512];
	int firstLen = 0, lastLen = 0;

	std::string longestFirst;
	std::string longestLast;
	int bestLen = 0;

	bool inQuotes = false;
	int field = 0;

	while ((bytesRead = fread(buffer.data(), 1, buffer.size(), file)) > 0)
	{
		const char* ptr = buffer.data();
		const char* end = ptr + bytesRead;

		while (ptr != end)
		{
			char ch = *ptr++;

			if (ch == '"')
			{
				inQuotes = !inQuotes;
			}
			else if (ch == ',' && !inQuotes)
			{
				++field;
			}
			else if (ch == '\n' && !inQuotes)
			{
				SetNewLongestName(firstLen, lastLen, bestLen, longestFirst, firstName, longestLast, lastName, field);
			}
			else
			{
				if (field == 2 && firstLen < 511) firstName[firstLen++] = ch;
				else if (field == 3 && lastLen < 511) lastName[lastLen++] = ch;
			}

			if (field > 3 && !inQuotes)
			{
				while (ptr != end)
				{
					char c = *ptr++;
					if (c == '"') inQuotes = !inQuotes;
					else if (c == '\n' && !inQuotes)
					{
						SetNewLongestName(firstLen, lastLen, bestLen, longestFirst, firstName, longestLast, lastName, field);
						break;
					}
				}
			}
		}
	}

	fclose(file);

	std::cout << longestFirst << " " << longestLast << "\n";
	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

	return 0;
}
