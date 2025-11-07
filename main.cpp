#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>


template<typename T>
std::string convertToToken(const char* filepath){
    std::vector<std::pair<std::string, T>> tokens;
    std::ifstream file(filepath);
    if(file.fail()){
        std::cerr << "Failed to open file" << filepath;
    }
    std::string code;
    std::string line;
    while(std::getline(file , line)){
        int i = 0 ;
        while(i < line.size()){
            if(std::isalpha(line[i]) || line[i] == '_'){
                std::string buffer;
                while(i < line.size() && (std::isalpha(line[i]) || std::isdigit(line[i]) || line[i] == '_')){
                    buffer+= line[i];
                    i++;
                }
                tokens.push_back({"IDENTIFIER" , buffer});
            }
        }
    }
}

/*
        std::istringstream iss(line);
        std::string segment;
        while(std::getline(iss , segment , ' ')){
            std::cout << segment << "\n";
        }
    }

  */


node* convertToAST(){


}


int main(){
    std::ifstream file("index.mhtml");
    if(file.fail()){
        std::cerr << "Failed to open file" << "index.mhtml";
    }
    std::string code;
    std::string line;
    while(std::getline(file , line)){
        for(int i = 0 ; i < line.size() ; i++){
            if(line[i] == '/')continue;
            if(line[i] == '<' || line[i] == '>'){
                code +=':';
                continue;
            }
            code +=line[i];
        }
    }
    std::cout << code;
}
