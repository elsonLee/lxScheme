#include <string>

#include "Visitor.h"
#include "Expr.h"

namespace lx {

std::string
Expr::type_name (Expr* expr)
{
    std::string ret;
    switch (expr->_type)
    {
    case Type::Symbol:
        ret = "<Symbol>"; break;
    case Type::Boolean:
        ret = "<Boolean>"; break;
    case Type::Number:
        ret = "<Number>"; break;
    case Type::List:
        ret = "<List>"; break;
    case Type::Cons:
        ret = "<Cons>"; break;
    case Type::Arithmetic:
        ret = "<Arithmetic>"; break;
    case Type::Relation:
        ret = "<Relation>"; break;
    case Type::Define:
        ret = "<Define>"; break;
    case Type::Begin:
        ret = "<Begin>"; break;
    case Type::Cond:
        ret = "<Cond>"; break;
    case Type::Else:
        ret = "<Else>"; break;
    case Type::Lambda:
        ret = "<Lambda>"; break;
    default:
        break;
    };
    return ret;
}

LambdaExpr::LambdaExpr (std::vector<Expr*>& params, Expr* body) :
    List(Type::Lambda)
{
    _exprs.push_back(new List(params));
    _exprs.push_back(body);
}

//! accept

Expr*
Number::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
Symbol::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
Boolean::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
List::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
ConsExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
ArithmeticExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
RelationExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
DefineExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
BeginExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
LambdaExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
CondExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
ElseExpr::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

}
