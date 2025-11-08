#include "./parser.h"


int main(){
    auto Tokens = Lexer("index.mhtml");
    for(const auto & [value , token] : Tokens){
        std::cout << "Value :: " << value << " Token :: " << tokenToString(token)  << "\n";
    }

    Parser p(Tokens);
    ASTNode* root = p.parseNode();

    try {
        printTree(root);
        delete root;
    } catch (...) {
        std::cerr << "Parsing failed.\n";
        return 1;
    }
    return 0;
}
