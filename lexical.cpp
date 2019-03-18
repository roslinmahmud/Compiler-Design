#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_set>
using namespace std;


ifstream inFile("input.txt");
ofstream outFile("output.txt");

regex number("((\\+|-)?[[:digit:]]+)(\\.([[:digit:]]+)?)?;?");
regex idetifier("([_[:alpha:]])+([[:alnum:]]*_*)*;?");
regex operat("=|==|<=|>=|>|<");
regex aoperat("\\*|\\/|\\+|-");
regex bracket("\\(|\\)");

unordered_set<string> keyword = {"auto","break","case","char","const","continue",
"default","do","double","else","enum","extern","float","for","goto","if","int",
"long","register","return","short","signed","sizeof","static","struct","switch",
"typedef","union","unsigned","void","volatile","while"};

struct sTable {
	string s = "invalid_lexeme";
	pair <string, string> p;
	bool isId = false;
};
vector <sTable> table;
void scan(){
    string s, lexeme;
    int line = 1;
    while(getline(inFile, s)){
        stringstream w(s);
        while(w >> lexeme){
            sTable st;
            if(lexeme == "\n")
                break;
            if(regex_match(lexeme, number)){
                outFile << "number: " << lexeme << '\n';
                st.s = lexeme;
            }
            else if(regex_match(lexeme, idetifier)){
                if(keyword.find(lexeme) != keyword.end()){
                    outFile << "keyword: " << lexeme << '\n';
                    st.s = lexeme;
                }
                else{
                    outFile << "identifier: " << lexeme << '\n';
                    st.p = {"id", lexeme};
                    st.isId = true;
                }
            }
            else if(regex_match(lexeme, operat)){
                outFile << "operator: " << lexeme << '\n';
                st.s = lexeme;
            }
            else if(regex_match(lexeme, aoperat)){
                outFile << "arithmetic operator: " << lexeme << '\n';
                st.s = lexeme;
            }
            else if(regex_match(lexeme, bracket)){
                outFile << "bracket: " << lexeme << '\n';
                st.s = lexeme;
            }
            else{
                outFile << "invalid lexeme at line " << line << " : " << lexeme << '\n';
            }
            table.push_back(st);
        }
        line++;
    }
}

void showToken(){
    for(int i=0;i<table.size();i++){
        if(table[i].isId == true){
            outFile << "<" << table[i].p.first << "," << table[i].p.second << ">" << " ";
        }
        else{
            outFile << "<" << table[i].s << ">" << " ";
        }
    }
    cout << '\n';
}

int main(){

    scan();

    showToken();

    return 0;
}
