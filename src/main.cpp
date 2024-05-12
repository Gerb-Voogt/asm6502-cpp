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

        auto print_variant = [](const auto& var) {
            std::cout << var;
        };

        if (tok != expected) {
            std::cout << "Something went wrong! ";
            std::visit(print_variant, tok.value);
            std::cout << " is not the same as ";
            std::visit(print_variant, expected.value);
            std::cout << std::endl;
        }
    }
}

void test_reading_input_file() {
    std::string file_path = "test_files/test.asm";

    std::string input = read_input_file(file_path);
    std::string input_stripped = strip_comments(input);

    std::vector<std::string> strings = split_string(input);

    for (auto itr: strings) {
    }
}

void test_lexing_input_file() {
    std::string file_path = "test_files/test.asm";
    std::string input = strip_comments(read_input_file(file_path));

    Lexer l = Lexer(input);
    Token tok;
    while (tok.kind != TokenKind::eof) {
        tok = l.next_token();
        tok.debug();
    }

}

int main() {
    // test_lexer_simple();
    // test_reading_input_file();
    test_lexing_input_file();
}
