#include <array>
#include <exception>
#include <map>
#include <string>
#include <cstdarg>
#include <iostream>
#include <variant>
#include <vector>
#include <algorithm>

#include "lexer/tokens.hpp"

static std::map<std::string, TokenKind> KEYWORDS_MAP = {
    std::pair<std::string, TokenKind>("ADC", TokenKind::ADC),
};

Token::Token() { }


Token::Token(const TokenKind kind, const std::variant<std::string, char> value) {
    this->kind = kind;
    this->value = value;
}


bool Token::operator==(Token rhs) {
    if (this->kind == rhs.kind && this->value == rhs.value) {
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


bool Token::is_keyword() const {
    // Create an array containing the opcodes
    // use std::find to check if it is contained in the array or not
    std::array<std::string, 56> keywords = {
        "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE",
        "BPL", "BRK", "BVC", "BVS", "CLC", "CLD", "CLI", "CLV", "CMP",
        "CPX", "CPY", "DEC", "DEX", "DEY", "EOR", "INC", "INX", "INY",
        "JMP", "JSR", "LDA", "LDX", "LDY", "LSR", "NOP", "ORA", "PHA",
        "PHP", "PLA", "PLP", "ROL", "ROR", "RTI", "RTS", "SBC", "SEC",
        "SED", "SEI", "STA", "STX", "STY", "TAX", "TAY", "TSX", "TXA",
        "TXS", "TYA",
    };

    auto itr = std::find(keywords.begin(), keywords.end(), std::get<std::string>(this->value));
    if (itr != keywords.end()) {
        return true;
    } else {
        return false;
    }
}


void Token::set_keyword_kind(std::variant<std::string, char> val) {
    if (this->is_keyword()) {
        this->kind = keyword_kind(std::get<std::string>(this->value));
    } 
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
        case TokenKind::Pound: token_string = "POUND"; break;
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

TokenKind keyword_kind(std::string keyword) {
    std::map<std::string, TokenKind> keywords_map = {
        std::pair<std::string, TokenKind>("ADC", TokenKind::ADC),
        std::pair<std::string, TokenKind>("AND", TokenKind::AND),
        std::pair<std::string, TokenKind>("ASL", TokenKind::ASL),
        std::pair<std::string, TokenKind>("BCC", TokenKind::BCC),
        std::pair<std::string, TokenKind>("BCS", TokenKind::BCS),
        std::pair<std::string, TokenKind>("BEQ", TokenKind::BEQ),
        std::pair<std::string, TokenKind>("BIT", TokenKind::BIT),
        std::pair<std::string, TokenKind>("BMI", TokenKind::BMI),
        std::pair<std::string, TokenKind>("BNE", TokenKind::BNE),
        std::pair<std::string, TokenKind>("BPL", TokenKind::BPL),
        std::pair<std::string, TokenKind>("BRK", TokenKind::BRK),
        std::pair<std::string, TokenKind>("BVC", TokenKind::BVC),
        std::pair<std::string, TokenKind>("BVS", TokenKind::BVS),
        std::pair<std::string, TokenKind>("CLC", TokenKind::CLC),
        std::pair<std::string, TokenKind>("CLD", TokenKind::CLD),
        std::pair<std::string, TokenKind>("CLI", TokenKind::CLI),
        std::pair<std::string, TokenKind>("CLV", TokenKind::CLV),
        std::pair<std::string, TokenKind>("CMP", TokenKind::CMP),
        std::pair<std::string, TokenKind>("CPX", TokenKind::CPX),
        std::pair<std::string, TokenKind>("CPY", TokenKind::CPY),
        std::pair<std::string, TokenKind>("DEC", TokenKind::DEC),
        std::pair<std::string, TokenKind>("DEX", TokenKind::DEX),
        std::pair<std::string, TokenKind>("DEY", TokenKind::DEY),
        std::pair<std::string, TokenKind>("EOR", TokenKind::EOR),
        std::pair<std::string, TokenKind>("INC", TokenKind::INC),
        std::pair<std::string, TokenKind>("INX", TokenKind::INX),
        std::pair<std::string, TokenKind>("INY", TokenKind::INY),
        std::pair<std::string, TokenKind>("JMP", TokenKind::JMP),
        std::pair<std::string, TokenKind>("JSR", TokenKind::JSR),
        std::pair<std::string, TokenKind>("LDA", TokenKind::LDA),
        std::pair<std::string, TokenKind>("LDX", TokenKind::LDX),
        std::pair<std::string, TokenKind>("LDY", TokenKind::LDY),
        std::pair<std::string, TokenKind>("LSR", TokenKind::LSR),
        std::pair<std::string, TokenKind>("NOP", TokenKind::NOP),
        std::pair<std::string, TokenKind>("ORA", TokenKind::ORA),
        std::pair<std::string, TokenKind>("PHA", TokenKind::PHA),
        std::pair<std::string, TokenKind>("PHP", TokenKind::PHP),
        std::pair<std::string, TokenKind>("PLA", TokenKind::PLA),
        std::pair<std::string, TokenKind>("PLP", TokenKind::PLP),
        std::pair<std::string, TokenKind>("ROL", TokenKind::ROL),
        std::pair<std::string, TokenKind>("ROR", TokenKind::ROR),
        std::pair<std::string, TokenKind>("RTI", TokenKind::RTI),
        std::pair<std::string, TokenKind>("RTS", TokenKind::RTS),
        std::pair<std::string, TokenKind>("SBC", TokenKind::SBC),
        std::pair<std::string, TokenKind>("SEC", TokenKind::SEC),
        std::pair<std::string, TokenKind>("SED", TokenKind::SED),
        std::pair<std::string, TokenKind>("SEI", TokenKind::SEI),
        std::pair<std::string, TokenKind>("STA", TokenKind::STA),
        std::pair<std::string, TokenKind>("STX", TokenKind::STX),
        std::pair<std::string, TokenKind>("STY", TokenKind::STY),
        std::pair<std::string, TokenKind>("TAX", TokenKind::TAX),
        std::pair<std::string, TokenKind>("TAY", TokenKind::TAY),
        std::pair<std::string, TokenKind>("TSX", TokenKind::TSX),
        std::pair<std::string, TokenKind>("TXA", TokenKind::TXA),
        std::pair<std::string, TokenKind>("TXS", TokenKind::TXS),
        std::pair<std::string, TokenKind>("TYA", TokenKind::TYA),
    };

    TokenKind kind;
    if (keywords_map.find(keyword) != keywords_map.end()) {
        kind = keywords_map[keyword];
    }
    return kind;
}

