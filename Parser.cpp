#include <string>
#include <vector>

#include "Expr.h"
#include "Parser.h"

namespace lx {

//! run

std::vector<std::string>
Tokenizer::run (const std::string& str)
{
    std::vector<std::string> tokens;
    int size = str.size();
    int i = 0;
    while (i < size) {
        while (str[i] == ' ') {
            i += 1;
        }
        if (str[i] == '(' || str[i] == ')') {
            tokens.push_back(std::string(1, str[i]));
            i += 1;
        } else {
            int m = i;
            while (i < size &&
                   str[i] != ' ' &&
                   str[i] != '(' &&
                   str[i] != ')') {
                i += 1;
            }
            if (m < i) {
                tokens.push_back(str.substr(m, i - m));
            }
        }
    }
    return tokens;
}

Expr*
Parser::run (std::vector<std::string>::const_iterator& iter)
{
    const std::string token(*iter);
    iter = std::next(iter, 1);

    if (token == "(") {
        List* expr = nullptr;
        if (*iter == "+" ||
            *iter == "-" ||
            *iter == "*" ||
            *iter == "/")
        {
            expr = new ArithmeticExpr(*iter);
            iter = std::next(iter, 1);
        }
        else if (*iter == "="  ||
                 *iter == "<"  ||
                 *iter == "<=" ||
                 *iter == ">"  ||
                 *iter == ">=")
        {
            expr = new RelationExpr(*iter);
            iter = std::next(iter, 1);
        }
        else if (*iter == "define")
        {
            expr = new DefineExpr();
            iter = std::next(iter, 1);
        }
        else if (*iter == "lambda")
        {
            expr = new LambdaExpr();
            iter = std::next(iter, 1);
        }
        else if (*iter == "if")
        {
            expr = new IfExpr();
            iter = std::next(iter, 1);
        }
        else if (*iter == "cond")
        {
            expr = new CondExpr();
            iter = std::next(iter, 1);
        }
        else if (*iter == "cons")
        {
            expr = new ConsExpr();
            iter = std::next(iter, 1);
        }
        else if (*iter == "car" ||
                 *iter == "cdr")
        {
            expr = new ListOpExpr(*iter);
            iter = std::next(iter, 1);
        }
        else if (*iter == "begin")
        {
            expr = new BeginExpr();
            iter = std::next(iter, 1);
        }
        else
        {
            expr = new List();
        }
        while (*iter != ")") {
            expr->_exprs.push_back(std::move(run(iter)));
        }
        iter = std::next(iter, 1);
        return expr;
    } else {
        if (is_integer(token)) {
            return new Integer(std::stoi(token));
        } else if (is_float(token)) {
            return new Float(std::stof(token));
        } else {
            if (token == "else")
            {
                return new ElseExpr();
            }
            else if (token == "#T" ||
                     token == "#t" ||
                     token == "true")
            {
                return new Boolean(true);
            }
            else if (token == "#F" ||
                     token == "#f" ||
                     token == "false")
            {
                return new Boolean(false);
            }
            else if (token == "nil")
            {
                return List::Nil();
            }
            else
            {
                return new Symbol(token);
            }
        }
    }
}

Expr*
Parser::run (const std::vector<std::string>& tokens)   // FIXME
{
    auto&& iter = tokens.begin();
    return run(iter);
}

}
