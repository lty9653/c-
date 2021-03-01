//计算器

#include <cmath>                        //for pow()
#include <iostream>                     //for standard streams
#include <stack>                        //for stack<T> containers
#include <algorithm>                    //for remove()
#include <stdexcept>                    //for suntime_error exception
#include <string>

using std::string;
using namespace std;

//优先级比较
inline size_t precedence(const char op)
{
    if(op=='+' || op=='-')
        return 1;
    if(op=='*' || op=='/')
        return 2;
    if(op == '^')
        return 3;
    //抛出异常，可以在catch中的what()函数捕捉
    throw runtime_error {string{"invalid operator: "} + op};
}

//执行
double execute(stack<char>& ops, stack<double>& operands)
{
    double result {};
    double rhs {operands.top()};
    operands.pop();
    double lhs {operands.top()};
    operands.pop();

    switch(ops.top())
    {
    case '+':
        result = lhs + rhs;
        break;
    case '-':
        result = lhs - rhs;
        break;
    case '*':
        result = lhs * rhs;
        break;
    case '/':
        result = lhs / rhs;
        break;
    case '^':
        result = pow(lhs,rhs);
    default:
        throw runtime_error {string{"invalid operator: "} + ops.top()};
    }
    ops.pop();
    operands.push(result);
    return result;
}

int main()
{
    stack<double> operands;                     //操作数栈
    stack<char> operators;                    //运算符栈
    string exp;
    cout << "An arithmetic expression van include +,-,*,/,^" << endl;

    try
    {
        while(true)
        {
            cout << "Enter an arithmetic expression and press Enter"
                 << "- enter an empty line to end"
                 << endl;

            //以cin的方式读入exp中，遇到'\n'结束
            getline(cin, exp, '\n');
            if(exp.empty()) break;

            //remove spaces
            //remove不能移除元素，只能通过移动的方式覆盖要移除的元素
            //通过erase()可以移除元素，传入两个迭代器，第一个是移动之后的元素的后面位置
            //第二个是原始状态的结束迭代器，两个之间的内容和会被删除。
            exp.erase(remove(begin(exp), end(exp), ' '), end(exp));
            size_t index {};                    //字符串下标


            //每一个表达式必须以数字开头
            //stod函数获取操作数，将第一个字符串参数中的字符序列转换为double值
            //第二个参数是一个整型指针，保存字符串中非字符部分第一个字符的索引
            //stod()返回float, Stod()返回long double
            operands.push(stod(exp, &index));

            while(true){
                operators.push(exp[index++]);
                size_t i {};

                //stod的第一个参数是从index开始的exp字符串，是被压入operators栈后的字符
                //第一个非数字索引保存在i中，i是相对于index而言的，所以index+i指向下一个操作符
                operands.push(stod(exp.substr(index), &i));
                index += i;
                if(index == exp.length()){
                    while(!operators.empty()){
                        execute(operators, operands);
                    }
                    break;
                }

                while(!operators.empty() && precedence(exp[index]) <= precedence(operators.top())){
                    execute(operators, operands);
                }
            }
            cout << "result = " << operands.top() <<endl;
        }
    }
    catch(const exception& e){
        cerr << e.what() << endl;
    }
    cout << "Calculate ending..." << endl;
}
