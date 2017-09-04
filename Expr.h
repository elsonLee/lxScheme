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
    Integer,
    Float,
    List,
    Cons,
    ListOp,
    Arithmetic,
    Relation,
    Define,
    Begin,
    If,
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

        void dump_info (void) const;

        Type    _type;

    protected:

        Expr (Type type) : _type(type)
        {}
};

class Integer;
class Float;
class Number : public Expr
{
    public:
        Number (Type type): Expr(type) {}
        virtual ~Number () = default;

        virtual Expr* accept (IVisitor& visitor, Env& env) = 0;

        virtual bool operator== (const Number& rhs) const = 0;
        virtual bool operator!= (const Number& rhs) const = 0;
        virtual bool operator<  (const Number& rhs) const = 0;
        virtual bool operator>  (const Number& rhs) const = 0;
        virtual bool operator<= (const Number& rhs) const = 0;
        virtual bool operator>= (const Number& rhs) const = 0;
        virtual bool operator== (const Integer& rhs) const = 0;
        virtual bool operator!= (const Integer& rhs) const = 0;
        virtual bool operator<  (const Integer& rhs) const = 0;
        virtual bool operator>  (const Integer& rhs) const = 0;
        virtual bool operator<= (const Integer& rhs) const = 0;
        virtual bool operator>= (const Integer& rhs) const = 0;
        virtual bool operator== (const Float& rhs) const = 0;
        virtual bool operator!= (const Float& rhs) const = 0;
        virtual bool operator<  (const Float& rhs) const = 0;
        virtual bool operator>  (const Float& rhs) const = 0;
        virtual bool operator<= (const Float& rhs) const = 0;
        virtual bool operator>= (const Float& rhs) const = 0;

        virtual Number& operator- () = 0;

        virtual Number& operator+ (Number& rhs) = 0;
        virtual Number& operator- (Number& rhs) = 0;
        virtual Number& operator* (Number& rhs) = 0;
        virtual Number& operator/ (Number& rhs) = 0;

        virtual Number& beAdd (Integer& rhs) = 0;
        virtual Number& beSub (Integer& rhs) = 0;
        virtual Number& beMul (Integer& rhs) = 0;
        virtual Number& beDiv (Integer& rhs) = 0;

        virtual Number& beAdd (Float& rhs) = 0;
        virtual Number& beSub (Float& rhs) = 0;
        virtual Number& beMul (Float& rhs) = 0;
        virtual Number& beDiv (Float& rhs) = 0;
};

class Integer final : public Number
{
    public:
        Integer (int32_t num) :
            Number(Type::Integer),
            _num(num)
        {}

        ~Integer () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        bool operator== (const Number& rhs) const override { return rhs == *this; }
        bool operator!= (const Number& rhs) const override { return rhs != *this; }
        bool operator<  (const Number& rhs) const override { return rhs >= *this; }
        bool operator>  (const Number& rhs) const override { return rhs <= *this; }
        bool operator<= (const Number& rhs) const override { return rhs >  *this; }
        bool operator>= (const Number& rhs) const override { return rhs <  *this; }

        bool operator== (const Integer& rhs) const;
        bool operator!= (const Integer& rhs) const;
        bool operator<  (const Integer& rhs) const;
        bool operator>  (const Integer& rhs) const;
        bool operator<= (const Integer& rhs) const;
        bool operator>= (const Integer& rhs) const;
        bool operator== (const Float& rhs) const;
        bool operator!= (const Float& rhs) const;
        bool operator<  (const Float& rhs) const;
        bool operator>  (const Float& rhs) const;
        bool operator<= (const Float& rhs) const;
        bool operator>= (const Float& rhs) const;

        Number& operator- () { _num = -_num; return *this; }

        Number& operator+ (Number& rhs) override;
        Number& operator- (Number& rhs) override;
        Number& operator* (Number& rhs) override;
        Number& operator/ (Number& rhs) override;

        Number& beAdd (Integer& rhs) override;
        Number& beSub (Integer& rhs) override;
        Number& beMul (Integer& rhs) override;
        Number& beDiv (Integer& rhs) override;

        Number& beAdd (Float& rhs) override;
        Number& beSub (Float& rhs) override;
        Number& beMul (Float& rhs) override;
        Number& beDiv (Float& rhs) override;

        int32_t _num;
};

class Float final : public Number
{
    public:
        Float (float num) :
            Number(Type::Float),
            _num(num)
        {}

        ~Float () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        bool operator== (const Number& rhs) const override { return rhs == *this; }
        bool operator!= (const Number& rhs) const override { return rhs != *this; }
        bool operator<  (const Number& rhs) const override { return rhs >= *this; }
        bool operator>  (const Number& rhs) const override { return rhs <= *this; }
        bool operator<= (const Number& rhs) const override { return rhs >  *this; }
        bool operator>= (const Number& rhs) const override { return rhs <  *this; }

        bool operator== (const Integer& rhs) const;
        bool operator!= (const Integer& rhs) const;
        bool operator<  (const Integer& rhs) const;
        bool operator>  (const Integer& rhs) const;
        bool operator<= (const Integer& rhs) const;
        bool operator>= (const Integer& rhs) const;
        bool operator== (const Float& rhs) const;
        bool operator!= (const Float& rhs) const;
        bool operator<  (const Float& rhs) const;
        bool operator>  (const Float& rhs) const;
        bool operator<= (const Float& rhs) const;
        bool operator>= (const Float& rhs) const;

        Number& operator- () { _num = -_num; return *this; }

        Number& operator+ (Number& rhs) override;
        Number& operator- (Number& rhs) override;
        Number& operator* (Number& rhs) override;
        Number& operator/ (Number& rhs) override;

        Number& beAdd (Integer& rhs) override;
        Number& beSub (Integer& rhs) override;
        Number& beMul (Integer& rhs) override;
        Number& beDiv (Integer& rhs) override;

        Number& beAdd (Float& rhs) override;
        Number& beSub (Float& rhs) override;
        Number& beMul (Float& rhs) override;
        Number& beDiv (Float& rhs) override;

        float _num;
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

        static Boolean* True (void);
        static Boolean* False (void);
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

        static List* Nil (void);

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

class ListOpExpr final : public List
{
    public:
        ListOpExpr (const std::string& str) :
            List(Type::ListOp),
            _str(str)
        {}

        ~ListOpExpr () = default;

        Expr* accept (IVisitor& visitor, Env& env) override;

        std::string _str;
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

class IfExpr final : public List
{
    public:
        IfExpr () :
            List(Type::If)
        {}

        ~IfExpr () = default;

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
