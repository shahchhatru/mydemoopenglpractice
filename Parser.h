#ifndef PARSER_CLASS_H
#define PARSER_CLASS_H
#include<cmath>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<stack>
using namespace std;
class Parser {

	static int preced(char ch);
	static bool isOperator(char ch);
public:
	static string infixtoPostfix(string infix);
	static float evaluator(string postfix,float x=0,float y=0);
};

#endif
