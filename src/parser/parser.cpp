#include "lexer/lexer.hpp"
#include "lexer/tokens.hpp"
#include "parser/ast.hpp"
#include "parser/parser.hpp"


Parser::Parser(const Lexer& l) : lexer(l) {
    // Call this twice to set current_token and peek_token are both set
    this->next_token();
    this->next_token();
}


void Parser::next_token() {
    this->current_token = this->peek_token;
    this->peek_token = this->lexer.next_token();
}


Program Parser::parse_program() {
    Program program;

    while (current_token.kind != TokenKind::eof) {
        // Maybe extract this into a function?
        if (this->current_token.kind == TokenKind::Identifier) {
            if (this->peek_token.kind == TokenKind::Assignment) {
                // TODO: Make a seperate function for parsing assignment
                // TODO: Assignment should be a tuple of 2 tokens (an identifier and it's value)
                //      | So this function _should_ be a vector of tuples of Tokens
                //      | I think a static array will not work in this case because the length of 
                //      | the vector is not known at compile time.
                program.identifiers.push_back(this->current_token);
            } else if (this->peek_token.kind == TokenKind::Colon) {
                program.labels.push_back(this->current_token);
            }
        }
        if (this->current_token.is_opcode()) {
            Instruction ins = this->parse_instruction(program.identifiers, program.labels);
        } else if (this->current_token.kind == TokenKind::Identifier) {
            Instruction ins = this->parse_instruction(program.identifiers, program.labels);
        }

    }
    return Program(); // Placeholder
}

Instruction Parser::parse_instruction(std::vector<Token> identifiers, std::vector<Token> labels) {
    // TODO finish this implementation
    Instruction ins;
    Mode mode;

    ins.opcode = this->current_token;
    ins.mode = this->parse_addressing_mode(identifiers, labels);

    return ins;
}


Mode Parser::parse_addressing_mode(std::vector<Token> identifiers, std::vector<Token> labels) {
    // TODO finish this implementation
    Mode mode;
    if (this->peek_token.kind == TokenKind::Pound) {
        mode = Mode::Immediate;
    } else if (this->peek_token.kind == TokenKind::OpenParan) {
        mode = this->parse_indirect_addressing();
    } else if (this->peek_token.kind == TokenKind::Identifier) {
        // Find the peek token in the list of labels or identifiers
        // If it is in neither, throw an exception
    }

    return mode;
}
