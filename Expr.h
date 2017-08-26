#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>

#include "AutoReleasePool.h"

namespace lx {

enum class Type
{
    Symbol,
    Boolean,
    Number,
    List,
    Cons,
    Arithmetic,
    Relation,
    Define,
    Begin,
    Cond,
    Else,
    Lambda,
};

class IVisitor;
class Env;

class Expr : public AutoReleaseObj
{
    public:
        static std::string type_name (Expr* expr);

    public:

        virtual ~Expr () = default;
        virtual Expr* accept (IVisitor& eval, Env& env) = 0;

        Type    _type;

    protected:

        Expr (Type type) : _type(type)
        {}
};

class Number final : public Expr
{
    public:
        Number (int32_t num) :
            Expr(Type::Number),
            _num(num)
        {}

        ~Number () = default;

        bool operator== (const Number& rhs) { return _num == rhs._num; }
        bool operator!= (const Number& rhs) { return _num != rhs._num; }
        bool operator<  (const Number& rhs) { return _num <  rhs._num; }
        bool operator>  (const Number& rhs) { return _num >  rhs._num; }
        bool operator<= (const Number& rhs) { return _num <= rhs._num; }
        bool operator>= (const Number& rhs) { return _num >= rhs._num; }

        Expr* accept (IVisitor& visitor, Env& env) override;

        int32_t _num;
};

class Symbol : public Expr
{
    public:
        Symbol (const std::string& str) :
            Expr(Type::Symbol), _str(str)
        {}

        Symbol (Type type, const std::string& str) :
            Expr(type), _str(str)
        {}

        virtual ~Symbol () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        bool operator== (const Symbol& rhs) { return _str == rhs._str; }
        bool operator!= (const Symbol& rhs) { return _str != rhs._str; }
        bool operator<  (const Symbol& rhs) { return _str <  rhs._str; }
        bool operator>  (const Symbol& rhs) { return _str >  rhs._str; }
        bool operator<= (const Symbol& rhs) { return _str <= rhs._str; }
        bool operator>= (const Symbol& rhs) { return _str >= rhs._str; }

        const std::string    _str;
};

class Boolean final : public Symbol
{
    public:
        Boolean (bool f) :
            Symbol(Type::Boolean, f? "#T" : "#F")
        {}

        ~Boolean () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        bool operator== (const Symbol& rhs) { return _str == rhs._str; }
        bool operator!= (const Symbol& rhs) { return _str != rhs._str; }
        bool operator<  (const Symbol& rhs) { return _str <  rhs._str; }
        bool operator>  (const Symbol& rhs) { return _str >  rhs._str; }
        bool operator<= (const Symbol& rhs) { return _str <= rhs._str; }
        bool operator>= (const Symbol& rhs) { return _str >= rhs._str; }
};

class List : public Expr
{
    public:
        List () : Expr(Type::List)
        {}

        List (std::vector<Expr*>& exprs) :
            Expr(Type::List), _exprs(exprs)
        {}

        List (Type type) : Expr(type)
        {}

        virtual ~List () = default;

        Expr* accept (IVisitor& visitor, Env& env);

        std::vector<Expr*>  _exprs;
};

class ConsExpr final : public List
{
    public:
        ConsExpr () :
            List(Type::Cons)
        {}

        ~ConsExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;
};

class ArithmeticExpr final : public List
{
    public:
        ArithmeticExpr (const std::string& str) :
            List(Type::Arithmetic),
            _str(str)
        {}

        ~ArithmeticExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        std::string _str;
};

class RelationExpr final : public List
{
    public:
        RelationExpr (const std::string& str) :
            List(Type::Relation),
            _str(str)
        {}

        ~RelationExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        const std::string   _str;
};

class DefineExpr final : public List
{
    public:
        DefineExpr () : List(Type::Define)
        {}

        DefineExpr (const std::string& var, Expr* val) :
            List(Type::Define)
        {
            _exprs.push_back(new Symbol(var));
            _exprs.push_back(val);
        }

        ~DefineExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;
};

class BeginExpr final : public List
{
    public:
        BeginExpr () : List(Type::Begin)
        {}

        ~BeginExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;
};

class LambdaExpr final : public List
{
    public:
        LambdaExpr () : List(Type::Lambda)
        {}
        LambdaExpr (std::vector<Expr*>& params, Expr* body);

        ~LambdaExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;
};

class CondExpr final : public List
{
    public:
        CondExpr () : List(Type::Cond)
        {}

        ~CondExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;
};

class ElseExpr final : public List
{
    public:
        ElseExpr () : List(Type::Else)
        {}

        ~ElseExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;
};

}

#endif // EXPR_H
