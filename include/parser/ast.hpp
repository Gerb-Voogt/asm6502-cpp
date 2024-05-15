#ifndef _AST_HPP
#define _AST_HPP
#include <string>
#include <vector>

#include "lexer/tokens.hpp"

enum class Mode {
    Accumulator, 
    Immediate, // #
    Implied,
    Relative,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
    Indirect,
    IndirectX, // Indexed Indirect ($ZZ, X)
    IndirectY, // Indirect Indexed ($ZZ), Y
};

struct Instruction {
    Token opcode;
    Token operand;
    Mode mode;
};

class Program {
public:
    std::vector<Instruction> statements;
    std::vector<Token> identifiers;
    std::vector<Token> labels;
};
#endif
