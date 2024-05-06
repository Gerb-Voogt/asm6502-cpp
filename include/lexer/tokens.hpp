#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

enum TokenKind {
    EOFT, // EOFT for EOF Token
    DecimalNumber,
    HexNumber,
    BinaryNumber,
    Identifier,
    Label,
    Assignment,
    Semicolon, 
    Colon,
    Comma,
    Dollar, // Denotes Hex numbers
    Percent, // Denotes Binary numbers

    // Operations
    Plus,
    Dash,
    Star,

    // Grouping Tokens
    OpenParan, CloseParan,

    // These are reserved because X and Y are the index registers
    X, Y,
    // Reserved Keywords (Opcodes, X and Y)
    ADC, AND, ASL, BCC, BCS, BEQ, BIT,
    BMI, BNE, BPL, BRK, BVC, BVS, CLC,
    CLD, CLI, CLV, CMP, CPX, CPY, DEC,
    DEX, DEY, EOR, INC, INX, INY, JMP,
    JSR, LDA, LDX, LDY, LSR, NOP, ORA,
    PHA, PHP, PLA, PLP, ROL, ROR, RTI,
    RTS, SBC, SEC, SED, SEI, STA, STX,
    STY, TAX, TAY, TSX, TXA, TXS, TYA,
};

struct Token {
    TokenKind kind;
    std::string value;
};

std::string debug(TokenKind kind); {
    std::string token_string;
    switch (kind) {
        case TokenKind::EOFT: { token_string = "EOF"; }
        case TokenKind::X: { token_string = "X"; }
    
    }
    return token_string;
}
#endif
