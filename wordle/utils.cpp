#include "wordle.hpp"

void Wordle::print_header() const
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    std::cout << Clear << Green;
    if (width > 116)    
    {
        std::cout << R"( .----------------. .----------------. .----------------. .----------------. .----------------. .----------------. 
| .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
| | _____  _____ | | |     ____     | | |  _______     | | |  ________    | | |   _____      | | |  _________   | |
| ||_   _||_   _|| | |   .'    `.   | | | |_   __ \    | | | |_   ___ `.  | | |  |_   _|     | | | |_   ___  |  | |
| |  | | /\ | |  | | |  /  .--.  \  | | |   | |__) |   | | |   | |   `. \ | | |    | |       | | |   | |_  \_|  | |
| |  | |/  \| |  | | |  | |    | |  | | |   |  __ /    | | |   | |    | | | | |    | |   _   | | |   |  _|  _   | |
| |  |   /\   |  | | |  \  `--'  /  | | |  _| |  \ \_  | | |  _| |___.' / | | |   _| |__/ |  | | |  _| |___/ |  | |
| |  |__/  \__|  | | |   `.____.'   | | | |____| |___| | | | |________.'  | | |  |________|  | | | |_________|  | |
| |              | | |              | | |              | | |              | | |              | | |              | |
| '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
 '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' )" << Reset << std::endl << std::endl;
    }
    else if (width > 70)
    {
        std::cout << R"(           .---.                                    ,--,               
          /. ./|                            ,---, ,--.'|               
      .--'.  ' ;    ,---.     __  ,-.     ,---.'| |  | :               
     /__./ \ : |   '   ,'\  ,' ,'/ /|     |   | : :  : '               
 .--'.  '   \' .  /   /   | '  | |' |     |   | | |  ' |       ,---.   
/___/ \ |    ' ' .   ; ,. : |  |   ,'   ,--.__| | '  | |      /     \  
;   \  \;      : '   | |: : '  :  /    /   ,'   | |  | :     /    /  | 
 \   ;  `      | '   | .; : |  | '    .   '  /  | '  : |__  .    ' / | 
  .   \    .\  ; |   :    | ;  : |    '   ; |:  | |  | '.'| '   ;   /| 
   \   \   ' \ |  \   \  /  |  , ;    |   | '/  ' ;  :    ; '   |  / | 
    :   '  |--"    `----'    ---'     |   :    :| |  ,   /  |   :    | 
     \   \ ;                           \   \  /    ---`-'    \   \  /  
      '---"                             `----'                `----'   )" << Reset << std::endl << std::endl;
    }
    else if (width > 42)
    {
        std::cout << R"(.------.------.------.------.------.------.
|W.--. |O.--. |R.--. |D.--. |L.--. |E.--. |
| :/\: | :/\: | :(): | :/\: | :/\: | (\/) |
| :\/: | :\/: | ()() | (__) | (__) | :\/: |
| '--'W| '--'O| '--'R| '--'D| '--'L| '--'E|
`------`------`------`------`------`------')" << Reset << std::endl << std::endl;
    }
    else if (width > 35)
    {
        std::cout << R"( __          __           _ _      
 \ \        / /          | | |     
  \ \  /\  / /__  _ __ __| | | ___ 
   \ \/  \/ / _ \| '__/ _` | |/ _ \
    \  /\  | (_) | | | (_| | |  __/
     \/  \/ \___/|_|  \__,_|_|\___|)" << Reset << std::endl << std::endl;
    }
    else
    {
        std::cout << "Wordle" << Reset << std::endl;
    }
}

void Wordle::print_guesses() const
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int width = w.ws_col;

    for (int i = 0; i < 6; i++)
    {
        if (width > 50)
            std::cout << "                    ";
        else if (width > 35)
            std::cout << "                ";
        else if (width > 25)
            std::cout << "        ";
        else
            std::cout << "    ";
        std::cout << guesses[i] << std::endl << std::endl;
    }
}

std::string Wordle::get_word() const
{
    std::srand(std::time(0));
    int random_index = std::rand() % words.size();
    return words[random_index];
}

bool Wordle::check_word(std::string const &input) const
{
    auto it = std::find(words.begin(), words.end(), input);
    if (it == words.end())
        return false;
    return true;
}

std::string Wordle::to_lower(const std::string &str) const
{
    std::string lower_str = str;
    
    for (size_t i = 0; i < 5; ++i)
    {
        lower_str[i] = std::tolower(lower_str[i]);
    }
    return lower_str;
}

std::string to_upper(const std::string &str)
{
    std::string upper_str = str;
    
    for (size_t i = 0; i < 5; ++i)
    {
        upper_str[i] = std::toupper(upper_str[i]);
    }
    return upper_str;
}

std::string Wordle::get_input() const
{
    std::string input;
    std::cout << "Input: ";
    while (true)
    {
        std::getline(std::cin, input);
        if (std::cin.eof() || std::cin.fail())
        {
            std::cout << "Please enter a valid 5-letter word: ";
            std::cin.clear();
            continue;
        }
        input = to_lower(input);
        if (input.length() != 5 || !check_word(input))
            std::cout << "Please enter a valid 5-letter word: ";
        else
            return input;
        input.clear();
        std::cin.clear();
    }
    return NULL;
}

std::string erase_letter(std::string str, char letter)
{
    size_t pos = str.find(letter);
    if (pos != std::string::npos)
    {
        str.erase(pos, 1);
    }
    return str;
}

std::string Wordle::parse_guess(std::string const &input, std::string const &word)
{
    std::string guess = input;
    std::string new_word = word;
    std::string res = "";
    short color[5] = {0, 0, 0, 0, 0};
    for (short i = 0; i < 5; i++)
    {
        if (guess[i] == word[i])
        {
            color[i] = 1;
            new_word = erase_letter(new_word, guess[i]);
            alphabet[std::toupper(guess[i])] = 1;
        }
    }
    for (short i = 0; i < 5; i++)
    {
        if (color[i] != 0)
            continue;
        if (new_word.find(guess[i]) != std::string::npos)
        {
            color[i] = 2;
            new_word = erase_letter(new_word, guess[i]);
            if (alphabet[std::toupper(guess[i])] == 0)
                alphabet[std::toupper(guess[i])] = 2;
        }
    }
    for (short i = 0; i < 5; i++)
    {
        if (color[i] == 1)
        {
            res += Green;
            res += std::toupper(guess[i]);
            res += Reset;
            res += " ";
        }
        else if (color[i] == 2)
        {
            res += Yellow;
            res += std::toupper(guess[i]);
            res += Reset;
            res += " ";
        }
        else
        {
            res += std::toupper(guess[i]);
            res += " ";
            if (alphabet[std::toupper(guess[i])] == 0)
                alphabet[std::toupper(guess[i])] = 3;
        }
    }
    return res;
}

void Wordle::print_alphabet()
{
    for (std::map<char, short>::iterator it = alphabet.begin(); it != alphabet.end(); ++it)
    {
        if (it->second == 0)
            std::cout << it->first << " ";
        else if (it->second == 1)
            std::cout << WonG << it->first << Reset << " ";
        else if (it->second == 2)
            std::cout << WonY << it->first << Reset << " ";
        else
            std::cout << WonR << it->first << Reset << " ";
    }
    std::cout << std::endl << std::endl;
}

void Wordle::play()
{
    std::string word = get_word();
    short attempts = 0;
    while (attempts < 6)
    {
        std::string input = get_input();
        print_header();
        std::cout << std::endl << "Input: " << input << std::endl << std::endl;
        guesses[attempts] = parse_guess(input, word);
        print_guesses();
        if (input == word)
        {
            std::cout << Green << "Congratulations you found the word " << to_upper(word) << " in " << attempts + 1 << " guesses" << Reset << std::endl;
            return;
        }
        print_alphabet();
        attempts++;
    }
    std::cout << Red << "Sorry you couldn't find the word " << to_upper(word) << " in 6 guesses" << Reset << std::endl;
}


