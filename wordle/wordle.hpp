#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <unistd.h>
#include <map>
#include <sys/ioctl.h>

#define Red "\033[31m"
#define Green "\033[32m"
#define Yellow "\033[33m"
#define Blue "\033[34m"
#define Magenta "\033[35m"
#define Cyan "\033[36m"
#define Reset "\033[0m"
#define WonG "\033[37m\033[42m"
#define WonR "\033[37m\033[41m"
#define WonY "\033[37m\033[43m"
#define Clear "\033c"

class Wordle
{
    private:
        std::vector<std::string> words;
        std::map<char, short> alphabet;
        std::string guesses[6];
        short attempts;
    
    public:
        Wordle(int &n);
        ~Wordle();

        void print_header() const;
        void print_guesses() const;
        void print_alphabet();
        void play();
        std::string to_lower(const std::string &str) const;
        std::string get_word() const;
        std::string get_input() const;
        bool check_word(std::string const &input) const;
        std::string parse_guess(std::string const &input, std::string const &word);
};

#endif