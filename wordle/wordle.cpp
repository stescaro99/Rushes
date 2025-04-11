#include "wordle.hpp"

Wordle::Wordle(int &n) : attempts(0)
{
    std::ifstream file("words.txt");
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    std::string word;
    while (file >> word)
        words.push_back(to_lower(word));
    file.close();
    n = words.size();
    if (n == 0)
    {
        std::cerr << "No words found in file." << std::endl;
        return;
    }
    print_header();
    for (short i = 0; i < 6; ++i)
    {
        guesses[i] = "_ _ _ _ _";
    }
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        alphabet[c] = 0;
    }
}

Wordle::~Wordle()
{
}