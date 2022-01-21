#include"Parser.h"

 int Parser::preced(char ch) {
    if (ch == '+' || ch == '-') {
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else if (ch == '^') {
        return 3;
    }
    else {
        return 0;
    }
}

bool Parser::isOperator(char ch) {
    if (ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '^') {
        return true;
    }
    return false;
}

string Parser::infixtoPostfix(string infix) {
    stack<char> stk;

    string postfix = "";

    int ln = infix.length();
    if (ln == 1) {
        return infix;
    }
    //a*(x*x*y)

    int i = 0;
    while (i < ln) {
        char c = infix[i];
        if (isalpha(c) || isdigit(c)) {
            postfix += c;
        }
        else if (c == '(') {
            int lastn = postfix.length() - 1;
            char ch = postfix[lastn];
            if (isdigit(ch)) {
                postfix += ' ';
                stk.push('(');
            }
            else if (isalpha(ch)) {
                postfix += '(';
                string temp = "";
                i++;
                c = infix[i];
                cout << "enter " << c << endl;
                int parencount = 1;
                while (parencount > 0) {
                    cout << c << endl;

                    temp += c;
                    cout << temp << endl;
                    i++;
                    c = infix[i];
                    if (c == ')') {
                        parencount--;
                    }
                    if (c == '(') {
                        parencount++;
                    }

                }
                //cout<<c<<endl;
                //cout<<temp<<endl;
                string newtemp = infixtoPostfix(temp);
                cout << newtemp << endl;
                postfix += newtemp;
                postfix += ')';
                //cout<<postfix<<endl;
                i++;
                if (i < ln) {

                    continue;
                }
                else {
                    break;
                }

            }
            else {
                stk.push('(');

            }


        }

        else if (isOperator(c)) {
            int lastn = postfix.length() - 1;
            char ch = postfix[lastn];
            if (isalpha(ch) || isdigit(ch)) {
                postfix += ' ';
            }
            while (!stk.empty() && preced(infix[i]) <= preced(stk.top())) {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(c);
        }
        else if (c == ')') {
            while (stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else {
            i++;
            continue;
        }
        i++;
    }
    int lastn = postfix.length() - 1;
    char ch = postfix[lastn];
    if (isalpha(ch) || isdigit(ch)) {
        postfix += ' ';
    }
    while (!stk.empty()) {
        postfix += stk.top();
        stk.pop();
    }


    return postfix;
}


float Parser::evaluator(string postfix, float x, float y) {
    stack<float> stk;
    int n = postfix.length();
    string temp;
    int i = 0;
    while (i < n) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            while (ch != ' ') {
                temp += ch;
                i++;
                ch = postfix[i];
            }
            //cout<<"temp"<<temp<<endl;
            int a = stoi(temp);
            //cout<<a<<endl;
            stk.push(a);
            //cout<<stk.top()<<endl;
            temp = " ";
            continue;
        }
        else if (isOperator(ch)) {
            float a = stk.top();
            stk.pop();
            float b = stk.top();
            stk.pop();
            float res = 0;
            if (ch == '-') {
                res = b - a;
            }
            else if (ch == '*') {
                res = b * a;
            }
            else if (ch == '/') {
                res = b / a;
            }
            else if (ch == '+') {
                res = b + a;
            }
            else if (ch == '^') {
                res = pow(b, a);
            }
            stk.push(res);
        }
        else if (isalpha(ch)) {
            string word = "";
            if (ch == 'x') {
                stk.push(x);
            }
            else if (ch == 'y') {
                stk.push(y);
            }
            else {
                while (ch != '(') {
                    word += ch;
                    i++;
                    ch = postfix[i];

                }
                word += ch;
                //cout<<word<<endl;
                //cout<<ch<<endl;
                i++;
                ch = postfix[i];
                if (word == "sin(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = sin(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "cos(") {
                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    float a = cos(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "tan(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = tan(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "asin(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = asin(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "atan(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = atan(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "acos(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = acos(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "abs(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = fabs(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "ln(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = log(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "log(") {

                    string exp = "";
                    int parencount = 1;
                    while (parencount > 0) {
                        exp += ch;
                        i++;
                        ch = postfix[i];
                        if (ch == ')') {
                            parencount--;
                        }
                        if (ch == '(') {
                            parencount++;
                        }
                    }
                    //cout<<exp<<endl;
                    float a = log10(evaluator(exp, x, y));
                    stk.push(a);
                    continue;
                }
                else if (word == "e(") {

                    string expr = "";
                    while (ch != ')') {
                        expr += ch;
                        i++;
                        ch = postfix[i];
                    }
                    //cout<<expr<<endl;
                    float a = exp(evaluator(expr, x, y));
                    stk.push(a);
                    continue;
                }
            }



        }
        i++;
    }


    float a = stk.top();
    return a;
}
