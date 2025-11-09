#include "./Compiler/parser.h"
#include <cstdlib>


int main(int argv , char* argc[]){
    auto Tokens = Lexer(std::string(argc[1]).c_str());
    /*for(const auto & [value , token] : Tokens){
        std::cout << "value :: " << value << "  Token :: " << token << "\n";
    }*/
    Parser p(Tokens);
    ASTNode* root = p.parseNode();
    std::string parentHtml = "";
    std::string indent = "";
    std::string html = convertToHtml(root , parentHtml , indent);
    std::cout << html;
    writeHtml(html);
    /*try {
        printTree(root);
        delete root;
    } catch (...) {
        std::cerr << "Parsing failed.\n";
        std::exit(EXIT_FAILURE);
    }*/
    return 0;
}
