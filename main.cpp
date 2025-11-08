#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>
#include <fstream>


/*
@div .card .primary id:main {
    @h1 { Hello }
    @p { This is text. }
    @img src:x.png alt:
}

{@ , T_AT},{DIV , IDENTIFIER},{.card , CLASS},{.primary CLASS}

*/

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
        }else if(std::isalpha(currentChar)){
            std::string buffer = "";
            while(std::isalpha(nextChar) || std::isdigit(nextChar)){
                buffer += currentChar;
                file.read(&currentChar, sizeof(currentChar));
                nextChar = file.peek();
            }
            buffer += currentChar;

            Tokens.push_back({buffer , tokensEnum::IDENTIFIER});
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

struct Property {
    std::string name;
};

struct Selector {
    std::string name;
    std::string value;
};

struct ASTNode {
    std::string tag; 
    std::vector<Selector> selectors;
    std::vector<Property> properties;
    std::vector<ASTNode*> children;
    std::vector<std::string> textList;
};


class Parser{
private:
    //0,1,2,3,4,5,6,7,8
    //index

    token peek(){
        return tokens[index + 1];
    }
    token advance(){
        index++;
        return tokens[index - 1];
    }
    bool match(tokensEnum type){
        if(tokens[index].type == type){
            return true;
        }
        return false;
    };
    token expect(tokensEnum type){
        if(tokens[index].type == type){
            return advance();
        }
        std::exit(EXIT_FAILURE);
    }
    std::vector<token> tokens;
    size_t index;

public:
    Parser(const std::vector<token>& tokens) : tokens(tokens), index(0) {}
    ASTNode* parseNode(){
        expect(tokensEnum::AT);
        std::string tag = expect(tokensEnum::IDENTIFIER).value;
        ASTNode* node = new ASTNode();
        node->tag = tag;


        while (match(tokensEnum::CLASS)) {
            node->properties.push_back({advance().value});
        }

        while(match(tokensEnum::IDENTIFIER)){
            const std::string ident = advance().value;
            expect(tokensEnum::COLON);
            const token t = expect(tokensEnum::IDENTIFIER);
            node->selectors.push_back({ident , t.value});
        }

        expect(LBRACE);

        while(!match(tokensEnum::RBRACE)){
            if(match(tokensEnum::STRING)){
                node->textList.push_back(advance().value);
            }  
        }
    }
};


int main(){
    auto Tokens = Lexer("index.mhtml");
    return 0;
}
