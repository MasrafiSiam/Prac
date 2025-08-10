#include <iostream>
#include "stacktype.cpp"

using namespace std;

bool IsOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int Precedence(char c)
{
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string InfixToPostfix(string infix)
{
    StackType<char> stc;
    string postfix;

    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] >= '0' && infix[i] <= '9')
        {
            postfix = postfix + infix[i];
        }
        else if (infix[i] == '(')
        {
            stc.Push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!stc.IsEmpty() && stc.Top() != '(')
            {
                postfix = postfix + " ";
                postfix = postfix + stc.Top();
                stc.Pop();
            }
            stc.Pop();
        }
        else if (IsOperator(infix[i]))
        {
            if (IsOperator(infix[i]) && IsOperator(infix[i + 2]))
                return postfix = "Invalid Expression";

            postfix = postfix + " ";

            if (stc.IsEmpty())
            {
                stc.Push(infix[i]);
            }
            else
            {
                if (Precedence(infix[i]) > Precedence(stc.Top()))
                {
                    stc.Push(infix[i]);
                }
                else
                {
                    while ((!stc.IsEmpty()) && (Precedence(infix[i]) <= Precedence(stc.Top())))
                    {
                        postfix = postfix + stc.Top();
                        stc.Pop();
                        postfix = postfix + " ";
                    }
                    stc.Push(infix[i]);
                }
            }
        }
    }

    while (!stc.IsEmpty())
    {
        if (stc.Top() == '(')
            return postfix = "Invalid Expression";

        postfix = postfix + " ";
        postfix = postfix + stc.Top();
        stc.Pop();
    }

    return postfix;
}

void print(string infix, string postfix)
{
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
}

void cal(string postfix)
{
    StackType<double> stk;
    string num = "";
    double result;

    for (int i = 0; i < postfix.length(); i++)
    {
        // ✅ Fixed digit detection
        if (postfix[i] >= '0' && postfix[i] <= '9')
        {
            num = num + postfix[i];
        }
        else if (postfix[i] == ' ')
        {
            if (!num.empty())
            {
                stk.Push(stoi(num));
                num = "";
            }
        }
        else if (IsOperator(postfix[i]))
        {
            // ✅ Fixed operand order
            double ope2 = stk.Top();
            stk.Pop();
            double ope1 = stk.Top();
            stk.Pop();

            switch (postfix[i])
            {
            case '+':
                result = ope1 + ope2;
                break;
            case '-':
                result = ope1 - ope2;
                break;
            case '*':
                result = ope1 * ope2;
                break;
            case '/':
                result = ope1 / ope2;
                break;
            default:
                cout << "Error" << endl;
            }
            stk.Push(result);
        }
    }

    result = stk.Top();
    cout << "Result: " << result << endl;
}

int main()
{
    string infix;
    string postfix;

    infix = "10 + 3 * 5 / (16 -4)";
    postfix = InfixToPostfix(infix);
    print(infix, postfix);
    if (postfix != "Invalid Expression")
        cal(postfix);
    cout << endl;

    infix = "(5 + 3) * 12 / 3";
    postfix = InfixToPostfix(infix);
    print(infix, postfix);
    if (postfix != "Invalid Expression")
        cal(postfix);
    cout << endl;

    infix = "3 + 4 / (2 - 3) * / 5";
    postfix = InfixToPostfix(infix);
    print(infix, postfix);
    if (postfix != "Invalid Expression")
        cal(postfix);
    cout << endl;

    infix = "7 / 5 + (4 - (2) * 3";
    postfix = InfixToPostfix(infix);
    print(infix, postfix);
    if (postfix != "Invalid Expression")
        cal(postfix);
    cout << endl;

    return 0;
}
