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
    case Type::Integer:
        ret = "<Integer>"; break;
    case Type::Float:
        ret = "<Float>"; break;
    case Type::List:
        ret = "<List>"; break;
    case Type::If:
        ret = "<If>"; break;
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
Integer::accept (IVisitor& visitor, Env& env)
{
    return visitor.run(this, env);
}

Expr*
Float::accept (IVisitor& visitor, Env& env)
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
IfExpr::accept (IVisitor& visitor, Env& env)
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

//! relational operators

bool Integer::operator== (const Integer& rhs) const { return _num == rhs._num; }
bool Integer::operator!= (const Integer& rhs) const { return _num != rhs._num; }
bool Integer::operator<  (const Integer& rhs) const { return _num <  rhs._num; }
bool Integer::operator>  (const Integer& rhs) const { return _num >  rhs._num; }
bool Integer::operator<= (const Integer& rhs) const { return _num <= rhs._num; }
bool Integer::operator>= (const Integer& rhs) const { return _num >= rhs._num; }
bool Integer::operator== (const Float& rhs) const { return _num == rhs._num; }
bool Integer::operator!= (const Float& rhs) const { return _num != rhs._num; }
bool Integer::operator<  (const Float& rhs) const { return _num <  rhs._num; }
bool Integer::operator>  (const Float& rhs) const { return _num >  rhs._num; }
bool Integer::operator<= (const Float& rhs) const { return _num <= rhs._num; }
bool Integer::operator>= (const Float& rhs) const { return _num >= rhs._num; }

bool Float::operator== (const Integer& rhs) const { return _num == rhs._num; }
bool Float::operator!= (const Integer& rhs) const { return _num != rhs._num; }
bool Float::operator<  (const Integer& rhs) const { return _num <  rhs._num; }
bool Float::operator>  (const Integer& rhs) const { return _num >  rhs._num; }
bool Float::operator<= (const Integer& rhs) const { return _num <= rhs._num; }
bool Float::operator>= (const Integer& rhs) const { return _num >= rhs._num; }
bool Float::operator== (const Float& rhs) const { return _num == rhs._num; }
bool Float::operator!= (const Float& rhs) const { return _num != rhs._num; }
bool Float::operator<  (const Float& rhs) const { return _num <  rhs._num; }
bool Float::operator>  (const Float& rhs) const { return _num >  rhs._num; }
bool Float::operator<= (const Float& rhs) const { return _num <= rhs._num; }
bool Float::operator>= (const Float& rhs) const { return _num >= rhs._num; }

//! operator
Number&
Integer::operator+ (Number& rhs)
{
    return rhs.beAdd(*this);
}

Number&
Integer::operator- (Number& rhs)
{
    return rhs.beSub(*this);
}

Number&
Integer::operator* (Number& rhs)
{
    return rhs.beMul(*this);
}

Number&
Integer::operator/ (Number& rhs)
{
    return rhs.beDiv(*this);
}

Number&
Float::operator+ (Number& rhs)
{
    return rhs.beAdd(*this);
}

Number&
Float::operator- (Number& rhs)
{
    return rhs.beSub(*this);
}

Number&
Float::operator* (Number& rhs)
{
    return rhs.beMul(*this);
}

Number&
Float::operator/ (Number& rhs)
{
    return rhs.beDiv(*this);
}

// beOp
Number&
Integer::beAdd (Integer& rhs)
{
    return *(new Integer(rhs._num + _num));
}

Number&
Integer::beAdd (Float& rhs)
{
    return *(new Float(rhs._num + _num));
}

Number&
Integer::beSub (Integer& rhs)
{
    return *(new Integer(rhs._num - _num));
}

Number&
Integer::beSub (Float& rhs)
{
    return *(new Float(rhs._num - _num));
}

Number&
Integer::beMul (Integer& rhs)
{
    return *(new Integer(rhs._num * _num));
}

Number&
Integer::beMul (Float& rhs)
{
    return *(new Float(rhs._num * _num));
}

Number&
Integer::beDiv (Integer& rhs)
{
    return *(new Integer(rhs._num / _num));
}

Number&
Integer::beDiv (Float& rhs)
{
    return *(new Float(rhs._num / _num));
}

Number&
Float::beAdd (Integer& rhs)
{
    return *(new Float(rhs._num + _num));
}

Number&
Float::beAdd (Float& rhs)
{
    return *(new Float(rhs._num + _num));
}

Number&
Float::beSub (Integer& rhs)
{
    return *(new Float(rhs._num - _num));
}

Number&
Float::beSub (Float& rhs)
{
    return *(new Float(rhs._num - _num));
}

Number&
Float::beMul (Integer& rhs)
{
    return *(new Float(rhs._num * _num));
}

Number&
Float::beMul (Float& rhs)
{
    return *(new Float(rhs._num * _num));
}

Number&
Float::beDiv (Integer& rhs)
{
    return *(new Float(rhs._num / _num));
}

Number&
Float::beDiv (Float& rhs)
{
    return *(new Float(rhs._num / _num));
}

}
