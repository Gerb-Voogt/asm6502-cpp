#include <string>
#include <cstdarg>
#include <iostream>
#include <variant>
#include <vector>

#include "lexer/tokens.hpp"

Token::Token() {
}


Token::Token(const TokenKind kind, const std::variant<std::string, char> value) {
    this->kind = kind;
    this->value = value;
}

std::string Token::get_value() const {
    std::string str;

    // Check if it's a string, if it is, return it
    // if it's not, convert the char to a string and return that
    if (std::holds_alternative<std::string>(this->value)) {
        str = std::get<std::string>(this->value);
    } else if (std::holds_alternative<char>(this->value)) {
        str = std::string(1, std::get<char>(this->value));
    }
    return str;
}

TokenKind Token::get_kind() const {
    return this->kind;
}


bool Token::operator==(Token rhs) {
    if (this->kind == rhs.get_kind() && this->get_value() == rhs.get_value()) {
        return true;
    } else {
        return false;
    }
}

bool Token::operator!=(Token rhs) {
    if (*this == rhs) {
        return false;
    } else {
        return true;
    }
}

bool Token::is_one_of_many(std::vector<TokenKind> token_kinds) const {
    for (auto itr: token_kinds) {
        if (itr == this->kind) {
            return true;
        }
    }
    return false;
}

void Token::debug() const {
    std::string str = token_string(this->kind);

    auto print_variant = [](const auto& var) {
        std::cout << var;
    };

    if (this->is_one_of_many({TokenKind::DecimalNumber, TokenKind::HexNumber, TokenKind::BinaryNumber, TokenKind::Identifier})) {
        // Print the variant
        std::cout << "[" << str << ", ";
        std::visit(print_variant, this->value);
        std::cout << "]" << std::endl;
    }  else {
        std::cout << "[" << str << "]" << std::endl;
    }
}


std::string token_string(TokenKind kind) {
    std::string token_string;
    switch (kind) {
        case TokenKind::eof: token_string = "EOF"; break;
        case TokenKind::DecimalNumber: token_string = "DECIMAL"; break;
        case TokenKind::HexNumber: token_string = "HEXADECIMAL"; break;
        case TokenKind::BinaryNumber: token_string = "BINARY"; break;
        case TokenKind::Identifier: token_string = "IDENTIFIER"; break;
        case TokenKind::Assignment: token_string = "ASSIGNMENT"; break;
        case TokenKind::Semicolon: token_string = "SEMICOLON"; break;
        case TokenKind::Colon: token_string = "COLON"; break;
        case TokenKind::Comma: token_string = "COMMA"; break;
        case TokenKind::Illegal: token_string = "ILLEGAL"; break;
        case TokenKind::Dollar: token_string = "DOLLAR"; break;
        case TokenKind::Percent: token_string = "PERCENT"; break;
        case TokenKind::Plus: token_string = "PLUS"; break;
        case TokenKind::Dash: token_string = "DASH"; break;
        case TokenKind::Star: token_string = "STAR"; break;
        case TokenKind::OpenParan: token_string = "OPEN_PARAN"; break;
        case TokenKind::CloseParan: token_string = "CLOSE_PARAN"; break;
        case TokenKind::X: token_string = "X"; break;
        case TokenKind::Y: token_string = "Y"; break;
        case TokenKind::ADC: token_string = "ADC"; break;
        case TokenKind::AND: token_string = "AND"; break;
        case TokenKind::ASL: token_string = "ASL"; break;
        case TokenKind::BCC: token_string = "BCC"; break;
        case TokenKind::BCS: token_string = "BCS"; break;
        case TokenKind::BEQ: token_string = "BEQ"; break;
        case TokenKind::BIT: token_string = "BIT"; break;
        case TokenKind::BMI: token_string = "BMI"; break;
        case TokenKind::BNE: token_string = "BNE"; break;
        case TokenKind::BPL: token_string = "BPL"; break;
        case TokenKind::BRK: token_string = "BRK"; break;
        case TokenKind::BVC: token_string = "BVC"; break;
        case TokenKind::BVS: token_string = "BVS"; break;
        case TokenKind::CLC: token_string = "CLC"; break;
        case TokenKind::CLD: token_string = "CLD"; break;
        case TokenKind::CLI: token_string = "CLI"; break;
        case TokenKind::CLV: token_string = "CLV"; break;
        case TokenKind::CMP: token_string = "CMP"; break;
        case TokenKind::CPX: token_string = "CPX"; break;
        case TokenKind::CPY: token_string = "CPY"; break;
        case TokenKind::DEC: token_string = "DEC"; break;
        case TokenKind::DEX: token_string = "DEX"; break;
        case TokenKind::DEY: token_string = "DEY"; break;
        case TokenKind::EOR: token_string = "EOR"; break;
        case TokenKind::INC: token_string = "INC"; break;
        case TokenKind::INX: token_string = "INX"; break;
        case TokenKind::INY: token_string = "INY"; break;
        case TokenKind::JMP: token_string = "JMP"; break;
        case TokenKind::JSR: token_string = "JSR"; break;
        case TokenKind::LDA: token_string = "LDA"; break;
        case TokenKind::LDX: token_string = "LDX"; break;
        case TokenKind::LDY: token_string = "LDY"; break;
        case TokenKind::LSR: token_string = "LSR"; break;
        case TokenKind::NOP: token_string = "NOP"; break;
        case TokenKind::ORA: token_string = "ORA"; break;
        case TokenKind::PHA: token_string = "PHA"; break;
        case TokenKind::PHP: token_string = "PHP"; break;
        case TokenKind::PLA: token_string = "PLA"; break;
        case TokenKind::PLP: token_string = "PLP"; break;
        case TokenKind::ROL: token_string = "ROL"; break;
        case TokenKind::ROR: token_string = "ROR"; break;
        case TokenKind::RTI: token_string = "RTI"; break;
        case TokenKind::RTS: token_string = "RTS"; break;
        case TokenKind::SBC: token_string = "SBC"; break;
        case TokenKind::SEC: token_string = "SEC"; break;
        case TokenKind::SED: token_string = "SED"; break;
        case TokenKind::SEI: token_string = "SEI"; break;
        case TokenKind::STA: token_string = "STA"; break;
        case TokenKind::STX: token_string = "STX"; break;
        case TokenKind::STY: token_string = "STY"; break;
        case TokenKind::TAX: token_string = "TAX"; break;
        case TokenKind::TAY: token_string = "TAY"; break;
        case TokenKind::TSX: token_string = "TSX"; break;
        case TokenKind::TXA: token_string = "TXA"; break;
        case TokenKind::TXS: token_string = "TXS"; break;
        case TokenKind::TYA: token_string = "TYA"; break;
    }
    return token_string;
}

