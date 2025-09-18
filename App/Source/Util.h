#pragma once

#include <chrono> 
#include <ratio>
#include <string_view>
#include <vector>

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<Clock> m_beg { Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};

void splitCsvLine(const std::string_view line, std::vector<std::string_view>& fieldsBuffer)
{
	fieldsBuffer.clear();
	fieldsBuffer.reserve(12);

	const char* start = line.data();
	const char* ptr = start;
	bool inQuotes = false;

	for (; ptr != line.data() + line.size(); ++ptr)
	{
		if (*ptr == '"')
		{
			inQuotes = !inQuotes;
		}
		else if (*ptr == ',' && !inQuotes)
		{
			fieldsBuffer.emplace_back(start, ptr - start);
			start = ptr + 1;
		}
	}

	fieldsBuffer.emplace_back(start, ptr - start);
}