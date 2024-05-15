#include <exception>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>

#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"


Lexer::Lexer(std::string input) {
    // Exception if empty input passed
    if (input.empty()) {
        throw std::exception();
    }
    this->input = strip_comments(input);
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

std::vector<std::string> split_string(const std::string input) {
    std::vector<std::string> string;
    const char delimiter = '\n';
    std::stringstream ss = std::stringstream(input);

    for (std::string line; std::getline(ss, line, delimiter);) {
        string.push_back(line);
    }
    return string;
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


std::string read_input_file(std::string file_path) {
    std::ifstream read_file;
    read_file.open("../" + file_path);

    if (!(read_file.is_open())) {
        throw std::exception();
    }

    std::string line;
    std::string file_content;
    while (getline(read_file, line)) {
        file_content += line + '\n';
    }

    read_file.close();

    return file_content;
}

std::string strip_comments(const std::string input) {
    std::vector<std::string> strings = split_string(input);
    std::string output = "";

    for (auto itr: strings) {
        size_t pos = itr.find(";");
        if (pos == itr.npos) {
            // Not found, add the entire string
            output += itr + "\n";
        } else {
            output += itr.substr(0, pos) + "\n";
        }
    }
    return output;
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
        // Get the value
        token.value = this->read_literal();

        // Check if it's a keyword, otherwise it's an identifier
        if (token.is_opcode()) {
            token.set_keyword_kind(token.value);
        } else {
            token.kind = TokenKind::Identifier;
        }
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
        case '#': {
            token.kind = TokenKind::Pound;
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
