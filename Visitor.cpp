#include <cstdio>
#include <algorithm>

#include "Env.h"
#include "Expr.h"
#include "Visitor.h"

namespace lx {

//! call

Expr*
Debugger::call (Expr* expr)
{
    Env env(nullptr);
    Expr* ret = expr->accept(*this, env);
    printf("\n");
    return ret;
}

Expr*
Eval::call (Expr* expr, Env& env)
{
    return expr->accept(*this, env);
}

//! run

Expr*
Debugger::run (Integer* number, Env& env)
{
    printf("%d%s", number->_num, Expr::type_name(number).c_str());
    return number;
}

Expr*
Debugger::run (Float* number, Env& env)
{
    printf("%f%s", number->_num, Expr::type_name(number).c_str());
    return number;
}

Expr*
Debugger::run (Symbol* sym, Env& env)
{
    printf("%s%s", sym->_str.c_str(), Expr::type_name(sym).c_str());
    return sym;
}

Expr*
Debugger::run (Boolean* sym, Env& env)
{
    return run(static_cast<Symbol*>(sym), env);
}

Expr*
Debugger::run (List* list, Env& env)
{
    printf("{");
    for (auto& e : list->_exprs) {
        e->accept(*this, env);
    }
    printf("\n}");
    return list;
}

Expr*
Debugger::run_relation_proc (RelationExpr* expr, Env& env)
{
    printf("(%s){", expr->_str.c_str());
    for (auto& e : expr->_exprs) {
        e->accept(*this, env);
    }
    printf("\n}");
    return expr;
}

Expr*
Debugger::run_arithmetic_proc (ArithmeticExpr* expr, Env& env)
{
    printf("(%s){", expr->_str.c_str());
    for (auto& e : expr->_exprs) {
        e->accept(*this, env);
    }
    printf("\n}");
    return expr;
}

Expr*
Debugger::run_specific_proc (List* expr, Env& env)
{
    printf("%s{", Expr::type_name(expr).c_str());
    for (auto& e : expr->_exprs) {
        e->accept(*this, env);
    }
    printf("\n}");
    return expr;
}

Expr*
Debugger::run (ConsExpr* expr, Env& env)
{
    return run_specific_proc(expr, env);
}

Expr*
Debugger::run (ArithmeticExpr* expr, Env& env)
{
    return run_arithmetic_proc(expr, env);
}

Expr*
Debugger::run (RelationExpr* relationExpr, Env& env)
{
    return run_relation_proc(relationExpr, env);
}

Expr*
Debugger::run (DefineExpr* defineExpr, Env& env)
{
    return run_specific_proc(defineExpr, env);
}

Expr*
Debugger::run (BeginExpr* beginExpr, Env& env)
{
    return run_specific_proc(beginExpr, env);
}

Expr*
Debugger::run (LambdaExpr* lambdaExpr, Env& env)
{
    return run_specific_proc(lambdaExpr, env);
}

Expr*
Debugger::run (CondExpr* condExpr, Env& env)
{
    return run_specific_proc(condExpr, env);
}

Expr*
Debugger::run (ElseExpr* elseExpr, Env& env)
{
    return run_specific_proc(elseExpr, env);
}


Expr*
Eval::run (Integer* number, Env& env)
{
    return number;
}

Expr*
Eval::run (Float* number, Env& env)
{
    return number;
}

Expr*
Eval::run (Symbol* sym, Env& env)
{
    Expr* ret = env.query_symbol(sym->_str);
    return ret;
}

Expr*
Eval::run (Boolean* sym, Env& env)
{
    return sym;
}

Expr*
Eval::run (List* list, Env& env)
{
    auto& exprs = list->_exprs;
    if (exprs.empty()) {
        return list;    // empty list
    } else {
        Expr* expr = exprs[0];
        if (expr->_type == Type::Symbol)
        {
            expr = env.query_symbol(dynamic_cast<Symbol*>(expr)->_str);
        }

        if (expr->_type == Type::Lambda)
        {
            std::vector<Expr*> args(exprs.begin() + 1, exprs.end());
            assert(expr->_type == Type::Lambda);
            auto&& lambdaExpr = dynamic_cast<LambdaExpr*>(expr);
            return run_proc(lambdaExpr, args, env);
        }
        else
        {
            auto&& map_func = [&](Expr* e)->Expr* { return call(e, env); };
            std::transform(exprs.begin(), exprs.end(), exprs.begin(), map_func);
            return list;
        }
    }
}

Expr*
Eval::run (ConsExpr* consExpr, Env& env)
{
    auto& consExprs = consExpr->_exprs;
    assert(consExprs.size() == 2);

    auto&& list = new List();
    list->_exprs.push_back(call(consExprs[0], env));
    list->_exprs.push_back(call(consExprs[1], env));
    return list;
}

Expr*
Eval::run_proc (LambdaExpr* lambdaExpr, std::vector<Expr*>& args, Env& env)
{
    auto& lambdaExprs = lambdaExpr->_exprs;
    assert(lambdaExprs.size() == 2);
    Expr* paramsExpr = lambdaExprs[0];
    assert(paramsExpr->_type == Type::List);

    std::vector<Expr*> paramsExprs = dynamic_cast<List*>(paramsExpr)->_exprs;
    std::vector<std::string> params;
    for (auto& paramExpr : paramsExprs) {
        assert(paramExpr->_type == Type::Symbol);
        params.push_back(dynamic_cast<Symbol*>(paramExpr)->_str);
    }
    Expr* bodyExpr = lambdaExprs[1];

    //assert(params.size() == args.size());

    Env lambdaEnv(env);
    lambdaEnv.extend_symbols(params, args);
    return call(bodyExpr, lambdaEnv);
}

Expr*
Eval::run (ArithmeticExpr* expr, Env& env)
{
    std::vector<Expr*>& exprs = expr->_exprs;
    int32_t size = exprs.size();
    if (size < 2) {
        fprintf(stderr, "%d: %s operands less than 2\n", __LINE__, Expr::type_name(expr).c_str());
        exit(-1);
    }

    Number* init = dynamic_cast<Number*>(call(exprs[0], env));
    Number* ret = init;

    for (auto i = 1; i < size; i++) {
        Number* operands = dynamic_cast<Number*>(call(exprs[i], env));
        if (expr->_str == "+") {
            ret = &(*ret + *operands);
        }
        else if (expr->_str == "-") {
            ret = &(*ret - *operands);
        }
        else if (expr->_str == "*") {
            ret = &(*ret * *operands);
        }
        else if (expr->_str == "/") {
            ret = &(*ret / *operands);
        }
        else {
            assert(0);
        }
    }
    return ret;
}

Expr*
Eval::run (RelationExpr* relationExpr, Env& env)
{
    std::vector<Expr*>& exprs = relationExpr->_exprs;
    assert(exprs.size() == 2);

    Expr* x = call(exprs[0], env);
    Expr* y = call(exprs[1], env);

    if (x->_type == y->_type && x->_type == Type::Integer) {
        Integer* numX = dynamic_cast<Integer*>(x);
        Integer* numY = dynamic_cast<Integer*>(y);
        if (relationExpr->_str == "=") {
            return (*numX == *numY)? new Boolean(true) : new Boolean(false);
        } else if (relationExpr->_str == "<") {
            return (*numX <  *numY)? new Boolean(true) : new Boolean(false);
        } else if (relationExpr->_str == "<=") {
            return (*numX <= *numY)? new Boolean(true) : new Boolean(false);
        } else if (relationExpr->_str == ">") {
            return (*numX >  *numY)? new Boolean(true) : new Boolean(false);
        } else if (relationExpr->_str == ">=") {
            return (*numX >= *numY)? new Boolean(true) : new Boolean(false);
        } else {
            printf("no such relation expr: %s\n", relationExpr->_str.c_str());
            return nullptr;
        }
    } else {
        printf("relation with wrong operands!\n");
        return nullptr;
    }
}

Expr*
Eval::run (DefineExpr* defineExpr, Env& env)
{
    std::vector<Expr*>& exprs = defineExpr->_exprs;
    assert(exprs.size() == 2);

    Expr* var = exprs[0];
    Expr* val = exprs[1];

    Expr* ret = nullptr;

    // (define <var> <val>)
    if (var->_type == Type::Symbol) {
        std::string var_name = dynamic_cast<Symbol*>(var)->_str;
        env.define_symbol(var_name, val);
        ret = val;
    }
    // (define (<var> <param1>...<paramN>) <body>)
    // (define <var> (lambda (<param1>...<paramN>) <body>)
    else if (var->_type == Type::List)
    {
        std::vector<Expr*> varList = dynamic_cast<List*>(var)->_exprs;
        if (varList[0]->_type == Type::Symbol)
        {
            std::string varName = dynamic_cast<Symbol*>(varList[0])->_str;
            std::vector<Expr*> params(varList.begin() + 1, varList.end());
            Expr* body = val;
            Expr* lambdaExpr = new LambdaExpr(params, body);
            env.define_symbol(varName, lambdaExpr);
            return new DefineExpr(varName, lambdaExpr);
        }
    } else {
        assert(0);
    }
    return ret;
}

Expr*
Eval::run (BeginExpr* beginExpr, Env& env)
{
    Expr* ret = nullptr;
    for (auto& expr : beginExpr->_exprs)
    {
        ret = call(expr, env);
    }
    return ret;
}

Expr*
Eval::run (LambdaExpr* lambdaExpr, Env& env)
{
    return lambdaExpr;
}

Expr*
Eval::run (CondExpr* condExpr, Env& env)
{
    for (auto& expr : condExpr->_exprs)
    {
        printf("cond type: %s\n", Expr::type_name(expr).c_str());
        assert(expr->_type == Type::List);
        List* exprList = dynamic_cast<List*>(expr);
        assert(exprList->_exprs.size() == 2);
        Expr* predicate = call(exprList->_exprs[0], env);
        if (*dynamic_cast<Boolean*>(predicate) == Boolean(true)) {
            return call(exprList->_exprs[1], env);
        }
    }
    printf("no cond predicate is met!\n");
    return nullptr;
}

Expr*
Eval::run (ElseExpr* condExpr, Env& env)
{
    return new Boolean(true);
}

}
