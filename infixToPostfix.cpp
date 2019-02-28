#include <bits/stdc++.h>

using namespace std;

string input;
char *ch = &input[0];

void expr();
void exprPrime();
void factor();
void factorPrime();
void term();
void skip(char c);

int main()
{
    cin >> input;
    expr();
    return 0;
}

void expr(){
    factor();
    exprPrime();
    return;
}

void exprPrime(){
    if(*ch == '+'){
        skip('+');
        factor();
        cout << '+';
        exprPrime();
    }
    else if(*ch == '-'){
        skip('-');
        factor();
        cout << '-';
        exprPrime();
    }
    return;
}

void factor(){
    term();
    factorPrime();
    return;
}

void factorPrime(){
    if(*ch == '*'){
        skip('*');
        term();
        cout << '*';
        factorPrime();
    }
    if(*ch == '/'){
        skip('/');
        term();
        cout << '/';
        factorPrime();
    }
    return;
}

void term(){
    if(isdigit(*ch)){
        cout << *ch;
        ch++;
    }
    else if(*ch == '('){
        skip('(');
        expr();
        skip(')');
    }
    return;
}


void skip(char c){
    if(c == *ch)
        ch++;

    return;
}
