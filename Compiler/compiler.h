#ifndef COMPILER_H
#define COMPILER_H

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


enum tokensEnum{
    AT = 1,
    IDENTIFIER,
    TEXT,
    CLASS,
    COLON,
    LBRACE,
    RBRACE,
    STRING
};

struct token{
    std::string value;
    tokensEnum type;
};

std::string tokenToString(short int i);

std::vector<token> Lexer(const char* filepath);

struct tokenClass{
    std::string className;
};

struct IdentifyingProperty {
    std::string identifer;
    std::string identifierName;
};

struct Attribute {
    std::string name;
    std::string value;
};

struct ASTNode {
    std::string tag;
    std::vector<tokenClass> classes;
    std::vector<Attribute> attributes;        // <-- NEW
    std::vector<ASTNode*> children;
    std::vector<std::string> textList;
};


class Parser{
private:
    token peek();
    token advance();
    bool match(tokensEnum type);
    token expect(tokensEnum type);
    std::vector<token> tokens;
    size_t index;

public:
    Parser(const std::vector<token>& tokens);
    ASTNode* parseNode();
};


void printTree(ASTNode* node, const std::string& prefix = "", bool isLast = true) ;

std::string convertToHtml(ASTNode* root , std::string& parentHtml , std::string indent);

void writeHtml(std::string parentHtml);

#endif
