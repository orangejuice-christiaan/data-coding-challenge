#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <sstream>

template <int size>
void processData(std::string_view line, void (*processFn)(std::array<std::string, size>&))
{
    std::stringstream test((std::string)line);
    std::string segment;
    std::array<std::string, size> lineData {};

    int i = 0;

    while (std::getline(test, segment, ','))
    {
        lineData[i] = segment;
        ++i;
    }

    processFn(lineData);
}

template <int size>
void getLongestName(std::array<std::string, size>& data)
{
    auto firstName = data[2];
    auto lastName = data[3];

    std::cout << firstName << " " << lastName << "\n";
}

int main()
{
    std::ifstream inf{ "C:/Git/data-coding-challenge/App/Source/resources/input-small.csv" };

    if (!inf)
    {
        std::cerr << "Could not find/open file.\n";
        return 1;
    }

    int i{ 0 };

    std::string strInput{};
    while (std::getline(inf, strInput)) {
        if (i != 0)
            processData<12>(strInput, getLongestName); // todo dynamically get nColumns
        ++i;
    }

	return 0;
}