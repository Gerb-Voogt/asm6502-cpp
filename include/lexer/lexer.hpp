#ifndef _LEXER_HPP
#define _LEXER_HPP

#include <string>

#include "lexer/tokens.hpp"

class Lexer {
public:
    Lexer(std::string input);

    // Repeatedly call this to yield all the tokens
    Token next_token();


private:
    std::string input;
    int position;
    int read_position;
    std::vector<Token> tokens;
    char ch;

    void skip_whitespace() noexcept;

    void read_char() noexcept;

    std::string read_hex();
    std::string read_bin();
    std::string read_literal();
    std::string read_dec();
};


#endif
