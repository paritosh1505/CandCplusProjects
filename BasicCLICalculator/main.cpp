#include <iostream>
#include<string>
#include "SimpleEval.h"
int main(){
    int eval,expr1,expr2,result;
    std::string replexpr;
    enum class Operator{
        ADD='+',
        SUB='-',
        MUL='*',
        DIV='/',
        Modulo='%',
        Power='^',
        Sqaure='@',
    };
    Operator openum;
    char opr;
    std::cout<<"Enter your mode of evaluation";
    std::cin>>eval;
    std::cout << "Enter First number ";
    std::cin>>expr1;
    std::cout << "Enter Operator number ";
    std::cin>>opr;
    std::cout << "Enter second number ";
    switch((opr)){
            case (static_cast<char>(Operator::ADD)):
            result= Addition(expr1,expr2);
            break;
            case (static_cast<char>(Operator::SUB)):
            result= Subtraction(expr1,expr2);
            break;
            case(static_cast<char>(Operator::MUL)):
            result=Multiply(expr1,expr2);
            break;
            case(static_cast<char>(Operator::DIV)):
            result=Divison(expr1,expr2);
            break;
            case(static_cast<char>(Operator::Modulo)):
            result=Modulos(expr1,expr2);
            break;
            case(static_cast<char>(Operator::Sqaure)):
            result=SqaureVal(expr1);
            break;
            case(static_cast<char>(Operator::Power)):
            result=PowerVal(expr1,expr2);
            break;
            default:
            std::cout<<"No valid operation check the expression";
            break;
        }
    
    return 0;
}