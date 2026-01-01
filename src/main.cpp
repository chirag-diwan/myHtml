#include "./Compiler/compiler.h"
#include <cstdlib>
#include <cstring>


int main(int argv , char* argc[]){
    bool isDegub = argv > 2 ? strcmp(argc[2] , "--debug") == 0 : false;
    Lexer lexer;
    lexer.LexFile(std::string(argc[1]).c_str());
    auto Tokens = lexer.getTokens();
    if(isDegub){
        for(const auto & [value , token] : Tokens){
            std::cout << "value :: " << value << "  Token :: " << token << "\n";
        }
    }
    Parser p(Tokens);
    ASTNode* root = p.parseNode();
    std::string parentHtml = "";
    std::string indent = "";
    std::string html = convertToHtml(root , parentHtml , indent);
    writeHtml(html);
    if(isDegub){
        printTree(root);
        delete root;
    }
    return 0;
}
