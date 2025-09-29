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
		longestFirst.assign(firstName, firstLen);
		longestLast.assign(lastName, lastLen);
		bestLen = totalLen;
	}
	firstLen = lastLen = 0;
	field = 0;
}

int main()
{
	std::ifstream file { "D:/Github/data-coding-challenge/App/Source/resources/input-small.csv" };

	if (!file)
	{
		std::cerr << "Could not find/open file.\n";
		return 1;
	}

	Timer t;

	const size_t BUFFER_SIZE = 64 * 1024; // 64 KB
	std::vector<char> buffer(BUFFER_SIZE);

	char firstName[512];
	char lastName[512];
	int firstLen = 0, lastLen = 0;

	std::string longestFirst;
	std::string longestLast;
	int bestLen = 0;

	bool inQuotes = false;
	int field = 0;
	bool headerSkipped = false;

	while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0)
	{
		const char* ptr = buffer.data();
		const char* end = ptr + file.gcount();

		while (ptr != end)
		{
			char ch = *ptr++;

			if (!headerSkipped)
			{
				if (ch == '\n') { headerSkipped = true; field = 0; }
				continue;
			}

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

	std::cout << longestFirst << " " << longestLast << "\n";
	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";

	return 0;
}
