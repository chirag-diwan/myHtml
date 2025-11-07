#include <iostream>
#include <string>
#include <vector>

//<root>
//  <div name=''>
//      <h1>THIS IS MY HTML</h1>
//      
//  </div>
//</root>
//
//
//
//ROOT DIV H1 H1CLOSE DIVCLOSE ROOTCLOSE
enum Token{
    ROOT,
    CLOSEROOT,
    DIV,
    CLOSEDIV,
    H1,
    CLOSEH1,
    P,
    CLOSEP,
    NONE
};

enum propertyType{
    NAME,
    NOP
};


class node{
private:
    Token nodeVal;
    propertyType Property;
    std::string PropertyVal;
    std::vector<node*> children;

public:
    node(){
        nodeVal = NONE;
        Property = propertyType::NOP;
        PropertyVal = "";
        children = {};
    }
};


std::string convertStringToToken(){}
std::vector<std::string> tokenList(std::string tokenString){}


int main(){


}
