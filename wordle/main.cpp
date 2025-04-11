#include "wordle.hpp"

int main()
{
    int n = 0;
    Wordle wordle(n);
    if (n == 0)
        return 1;
    std::cout << "Total words available: " << n << std::endl << std::endl;
    wordle.print_guesses();
    wordle.play();
    return 0;
}