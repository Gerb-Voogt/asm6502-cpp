#ifndef _TOKENS_HPP
#define _TOKENS_HPP

#include <string>
#include <variant>
#include <vector>

enum class TokenKind {
    eof, 
    Assignment,
    Semicolon, 
    Colon,
    Comma,
    Illegal,

    DecimalNumber,
    Dollar, // Denotes Hex numbers
    HexNumber,
    Percent, // Denotes Binary numbers
    BinaryNumber,
    Identifier,

    // Binary Operations
    Plus, Dash, Star,

    // Unary Operation
    Pound,

    // Grouping Tokens
    OpenParan, CloseParan,

    // These are reserved because X and Y are the index registers
    X, Y,
    // Reserved Keywords (Opcodes)
    ADC, AND, ASL, BCC, BCS, BEQ, BIT,
    BMI, BNE, BPL, BRK, BVC, BVS, CLC,
    CLD, CLI, CLV, CMP, CPX, CPY, DEC,
    DEX, DEY, EOR, INC, INX, INY, JMP,
    JSR, LDA, LDX, LDY, LSR, NOP, ORA,
    PHA, PHP, PLA, PLP, ROL, ROR, RTI,
    RTS, SBC, SEC, SED, SEI, STA, STX,
    STY, TAX, TAY, TSX, TXA, TXS, TYA,
};

struct Token final {
    TokenKind kind;
    std::variant<std::string, char> value;

    // Constructors
    Token();
    Token(const TokenKind kind, std::variant<std::string, char> value);

    // Check if a token is one of many in a list
    bool is_one_of_many(std::vector<TokenKind> token_kinds) const;

    bool is_opcode() const;

    // Print information on the current token
    void debug() const;

    // Getters and setter
    TokenKind get_kind() const;

    void set_keyword_kind(std::variant<std::string, char> val);

    // Operators
    bool operator==(Token rhs);

    bool operator!=(Token rhs);
};

std::string token_string(TokenKind kind);

TokenKind keyword_kind(std::string keyword);

#endif
