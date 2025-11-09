#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "./compiler.h"

std::string tokenToString(short int i){
    switch (i) {
        case 1:
            return ("AT");
            break;
        case 2:
            return ("IDENTIFIER");
            break;
        case 3:
            return ("TEXT");
            break;
        case 4:
            return ("CLASS");
            break;
        case 5:
            return ("COLON");
            break;
        case 6:
            return ("LBRACE");
            break;
        case 7:
            return ("RBRACE");
            break;
        case 8:
            return ("STRING");
            break;
    }
    return "";
}

std::vector<token> Lexer(const char* filepath){
    std::ifstream file(filepath);
    if(file.fail()){
        std::cerr << "Error Opening File :: " << filepath;
    }
    std::vector<token> Tokens;
    while(file.peek() != EOF){
        char prevChar;
        char currentChar;
        char nextChar = file.peek();
        file.read(&currentChar , sizeof(currentChar));
        if(currentChar == ' ')continue;
        if(currentChar == '@'){
            Tokens.push_back({"@" , tokensEnum::AT});
        }else if (currentChar == '{'){
            Tokens.push_back({"{" , tokensEnum::LBRACE});
        }else if (currentChar == '}'){
            Tokens.push_back({"}" , tokensEnum::RBRACE});
        }else if(currentChar == '.'){
            std::string buffer = "";
            while(nextChar != ' '){
                buffer += currentChar;
                file.read(&currentChar, sizeof(currentChar));
                nextChar = file.peek();
            }
            buffer += currentChar;
            Tokens.push_back({buffer , tokensEnum::CLASS});
        }else if(currentChar == ':'){
            Tokens.push_back({":" , tokensEnum::COLON});
        }else if (std::isalpha(currentChar) || currentChar == '_') {
            std::string buffer;
            buffer += currentChar;

            while (file.peek() != EOF) {
                char next = file.peek();
                if (std::isalnum(next) || next == '_' || next == '-') {
                    buffer += file.get();
                } else {
                    break; 
                }
            }
            Tokens.push_back({buffer, tokensEnum::IDENTIFIER});
        }else if(currentChar == '"'){
            std::string buffer;

            while(file.peek() != EOF){
                file.read(&currentChar, 1);
                if(currentChar == '"') {
                    break;
                }
                buffer += currentChar;
            }

            Tokens.push_back({buffer, tokensEnum::STRING});
        }
    }
    return Tokens;
}

token Parser::peek(){
    if(index + 1 >= tokens.size())return token{"" , (tokensEnum)0};
    return tokens[index + 1];
}
token Parser::advance(){
    index++;
    return tokens[index - 1];
}
bool Parser::match(tokensEnum type) {
    return index < tokens.size() && tokens[index].type == type;
}

token Parser::expect(tokensEnum type){
    if (index >= tokens.size()) {
        std::cerr << "Expected " << tokenToString(type) << " but got EOF\n";
        std::exit(EXIT_FAILURE);
    }
    if (tokens[index].type != type) {
        std::cerr << "Expected " << tokenToString(type)
            << " but got " << tokenToString(tokens[index].type)
            << " ('" << tokens[index].value << "') at index " << index << "\n";
        std::exit(EXIT_FAILURE);
    }
    return advance();
}

Parser::Parser(const std::vector<token>& t) : tokens(t), index(0) {}
ASTNode* Parser::parseNode() {
    expect(tokensEnum::AT);
    std::string tag = expect(tokensEnum::IDENTIFIER).value;
    ASTNode* node = new ASTNode();
    node->tag = tag;

    while (true) {
        if (match(tokensEnum::CLASS)) {
            const std::string cl = advance().value;
            node->classes.push_back({cl.substr(1 , cl.size())});
        }
        else if (match(tokensEnum::IDENTIFIER) && peek().type == tokensEnum::COLON) {
            std::string key = advance().value;
            expect(tokensEnum::COLON);
            std::string value = "";
            if (match(tokensEnum::IDENTIFIER) || match(tokensEnum::STRING)) {
                value = advance().value;
            }
            node->attributes.push_back({key, value});
        }
        else {
            break;  
        }
    }

    expect(tokensEnum::LBRACE);  

    while (!match(tokensEnum::RBRACE)) {
        if (match(tokensEnum::STRING)) {
            node->textList.push_back(advance().value);
        }
        else if (match(tokensEnum::AT)) {
            node->children.push_back(parseNode());
        }
        else {
            std::cerr << "INVALID TOKEN IN BODY: '" << tokens[index].value << "' at " << index << "\n";
            std::exit(EXIT_FAILURE);
        }
    }
    expect(tokensEnum::RBRACE);
    return node;
}

void printTree(ASTNode* node, const std::string& prefix, bool isLast) {
    if (!node) return;

    std::cout << prefix;
    std::cout << (isLast ? "└── " : "├── ");
    std::cout << '@' << node->tag;

    for (const auto& cls : node->classes) {
        std::cout << " " << cls.className;
    }

    for (const auto& attr : node->attributes)
    std::cout << " " << attr.name << ":\"" << attr.value << "\"";

    std::cout << "\n";

    for (size_t i = 0; i < node->textList.size(); ++i) {
        std::string textPrefix = prefix + (isLast ? "    " : "│   ");
        std::cout << textPrefix;
        std::cout << (i == node->textList.size() - 1 && node->children.empty() ? "└── " : "├── ");
        std::cout << "\"" << node->textList[i] << "\"\n";
    }

    for (size_t i = 0; i < node->children.size(); ++i) {
        bool lastChild = (i == node->children.size() - 1);
        std::string childPrefix = prefix + (isLast ? "    " : "│   ");
        printTree(node->children[i], childPrefix, lastChild);
    }
}

std::string appendQuote(std::string a){
    std::string buffer = "'";
    buffer += a;
    buffer += "'";
    return buffer;
}

void writeHtml(std::string parentHtml){
 
    std::ofstream file("index.html");
    std::string htmlHeader = "";
    htmlHeader += "<!DOCTYPE html>\n";
    htmlHeader += "<html lang='en'>\n";
    htmlHeader += "<head>\n";
    htmlHeader += "    <meta charset='UTF-8'>\n";
    htmlHeader += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    htmlHeader += "    <title>My Awesome App</title>\n";
    htmlHeader += "    <link rel='stylesheet' href='style.css'>\n";
    htmlHeader += "</head>\n";
    htmlHeader += "<body>\n";
    htmlHeader += parentHtml;
    file.write(htmlHeader.c_str() , htmlHeader.size());
}

std::string convertToHtml(ASTNode* root , std::string& parentHtml , std::string indent){
    parentHtml.append(indent);
    parentHtml.append("<");
    parentHtml.append(root->tag + " ");
    for(const auto& c:root->classes){
        parentHtml.append(" class="+ appendQuote(c.className));
    }
    for(const auto& a : root->attributes){
        parentHtml.append(" " + a.name + '=' + appendQuote(a.value));
    }
    parentHtml += ">\n";
    for(const auto & t : root->textList){
        parentHtml.append(indent + "    ");
        parentHtml.append(t);
        parentHtml += "\n";
    }
    for(const auto& c : root->children){
        convertToHtml(c , parentHtml ,indent + "    ");
    }
    parentHtml.append(indent);
    parentHtml.append("</" + root->tag + ">\n");
    return parentHtml;
}


