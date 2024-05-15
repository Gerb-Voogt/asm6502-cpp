#ifndef _PARSER_HPP
#define _PARSER_HPP

#include "lexer/lexer.hpp"
#include "parser/ast.hpp"

class Parser {
public:
    Parser(const Lexer& l);

    void next_token();

    Program parse_program();


private:
    Lexer lexer;
    Token current_token;
    Token peek_token;

    Instruction parse_instruction(std::vector<Token> identifiers, std::vector<Token> labels);

    Mode parse_addressing_mode(std::vector<Token> identifiers, std::vector<Token> labels);

    Mode parse_indirect_addressing();
};

#endif
