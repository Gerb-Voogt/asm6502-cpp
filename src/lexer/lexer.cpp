#include <exception>
#include <cctype>

#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"


Lexer::Lexer(std::string input) {
    // Exception if empty input passed
    if (input.empty()) {
        throw std::exception();
    }
    this->input = input;
    this->ch = input[0];
    this->position = 0;
    this->read_position = 1;
}


void Lexer::read_char() noexcept {
    if (this->position >= this->input.length()) {
        this->ch = '\0'; // eof character
    } else {
        this->ch = this->input[this->read_position];
    }


    // Update read position
    this->position = this->read_position;
    this->read_position += 1;
}


void Lexer::skip_whitespace() noexcept {
    while (this->ch == ' ' || this->ch == '\t' || this->ch == '\n' || this->ch == '\r') {
        this->read_char();
    }
}

std::string Lexer::read_hex() {
    std::string str = "";
    while (isxdigit(this->ch)) {
        str.push_back(this->ch);
        this->read_char();
    }
    return str;
}

std::string Lexer::read_dec() {
    std::string str = "";
    while (isxdigit(this->ch)) {
        str.push_back(this->ch);
        this->read_char();
    }
    return str;
}

std::string Lexer::read_bin() {
    std::string str = "";
    while (this->ch == '0' || this->ch == '1') {
        str.push_back(this->ch);
        this->read_char();
    }
    return str;
}

std::string Lexer::read_literal() {
    std::string str = "";
    while (isalpha(this->ch)) {
        str.push_back(this->ch);
        this->read_char();
    }
    return str;
}

Token Lexer::next_token() {
    Token token;

    this->skip_whitespace();

    // Special cases, early return
    //  - Numbers
    //  - Literals
    if (isdigit(this->ch)) {
        token.kind = TokenKind::DecimalNumber;
        token.value = this->read_dec();
        return token;
    } else if (isalpha(this->ch)) {
        token.kind = TokenKind::Identifier;
        token.value = this->read_literal();
        return token;
    }

    switch(this->ch) {
        case '\0': {
            token.kind = TokenKind::eof;
            token.value = '\0';
            break;
        }
        case '=': {
            token.kind = TokenKind::Assignment;
            token.value = this->ch;
            break;
        }
        case ';': {
            token.kind = TokenKind::Semicolon;
            token.value = this->ch;
            break;
        }
        case ':': {
            token.kind = TokenKind::Colon;
            token.value = this->ch;
            break;
        }
        case ',': {
            token.kind = TokenKind::Comma;
            token.value = this->ch;
            break;
        }
        case '(': {
            token.kind = TokenKind::OpenParan;
            token.value = this->ch;
            break;
        }
        case ')': {
            token.kind = TokenKind::CloseParan;
            token.value = this->ch;
            break;
        }
        case '+': {
            token.kind = TokenKind::Plus;
            token.value = this->ch;
            break;
        }
        case '-': {
            token.kind = TokenKind::Dash;
            token.value = this->ch;
            break;
        }
        case '*': {
            token.kind = TokenKind::Star;
            token.value = this->ch;
            break;
        }
        case 'X': {
            token.kind = TokenKind::X;
            token.value = this->ch;
            break;
        }
        case 'Y': {
            token.kind = TokenKind::Y;
            token.value = this->ch;
            break;
        }
        // Hex, Bin and Dec numbers
        case '$': {
            this->read_char();
            token.kind = TokenKind::HexNumber;
            token.value = this->read_hex();
            break;
        }
        case '%': {
            this->read_char();
            token.kind = TokenKind::HexNumber;
            token.value = this->read_bin();
            break;
        }
        default: {
            token.kind = TokenKind::Illegal;
            token.value = this->ch;
            break;
        }
    }

    this->read_char();

    return token;
}
