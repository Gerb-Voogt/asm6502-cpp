#include <cmath>
#include <string>
#include <iostream>

#include "lexer/tokens.hpp"
#include "lexer/lexer.hpp"


void test_lexer_simple() {
    std::string input = "+-();abc100$2A\n\t\tfunction():$FFFF";
    // std::string input = "+-();abc100$2A";
    Lexer l = Lexer(input);

    std::vector<Token> expected_token = {
        Token(TokenKind::Plus, '+'),
        Token(TokenKind::Dash, '-'),
        Token(TokenKind::OpenParan, '('),
        Token(TokenKind::CloseParan, ')'),
        Token(TokenKind::Semicolon, ';'),
        Token(TokenKind::Identifier, "abc"),
        Token(TokenKind::DecimalNumber, "100"),
        Token(TokenKind::HexNumber, "2A"),
        Token(TokenKind::Identifier, "function"),
        Token(TokenKind::OpenParan, '('),
        Token(TokenKind::CloseParan, ')'),
        Token(TokenKind::Colon, ':'),
        Token(TokenKind::HexNumber, "FFFF"),
    };

    for (auto &expected : expected_token) {
        Token tok = l.next_token();
        tok.debug();

        if (tok != expected) {
            std::cout << "Something went wrong! " <<
                tok.get_value() << " is not the same as " << expected.get_value() << std::endl;
        }
    }
}

int main() {
    std::vector<Token> tokens = {
        Token(TokenKind::BinaryNumber, "0b0100101"),
        Token(TokenKind::HexNumber, "0x00FF"),
        Token(TokenKind::DecimalNumber, "20"),
        Token(TokenKind::Colon, ':'),
    };

    for (auto tok: tokens) {
        tok.debug();
    }

    test_lexer_simple();
}
