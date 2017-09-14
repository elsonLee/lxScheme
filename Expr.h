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
    Let,
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

        virtual Expr* clone (void) const = 0;
        virtual Expr* accept (IVisitor& eval, Env& env) = 0;

        void dump_info (void) const;

        Type    _type;

    protected:

        Expr (Type type) : _type(type) {}
        Expr (const Expr& rhs) = default;
        virtual ~Expr () = default;
};

class Integer;
class Float;
class Number : public Expr
{
    public:

        virtual Expr* clone (void) const = 0;
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

    protected:
        Number (Type type): Expr(type) {}
        Number (const Number& rhs) : Expr(rhs) {}
        virtual ~Number () = default;
};

class Integer final : public Number
{
    public:
        Integer (int32_t num) :
            Number(Type::Integer),
            _num(num)
        {}

        Integer (const Integer& rhs) : Number(rhs), _num(rhs._num) {}

        virtual Expr* clone (void) const override
        {
            return new Integer(*this);
        }
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

        int32_t _num;

    private:
        ~Integer () = default;

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

};

class Float final : public Number
{
    public:
        Float (float num) :
            Number(Type::Float),
            _num(num)
        {}

        Float (const Float& rhs) : Number(rhs), _num(rhs._num) {}

        virtual Expr* clone (void) const override
        {
            return new Float(*this);
        }
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

        float _num;

    private:
        ~Float () = default;

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

        Symbol (const Symbol& rhs) : Expr(rhs), _str(rhs._str) {}

        virtual Expr* clone (void) const override
        {
            return new Symbol(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

        bool operator== (const Symbol& rhs) { return _str == rhs._str; }
        bool operator!= (const Symbol& rhs) { return _str != rhs._str; }
        bool operator<  (const Symbol& rhs) { return _str <  rhs._str; }
        bool operator>  (const Symbol& rhs) { return _str >  rhs._str; }
        bool operator<= (const Symbol& rhs) { return _str <= rhs._str; }
        bool operator>= (const Symbol& rhs) { return _str >= rhs._str; }

        const std::string    _str;

    protected:
        virtual ~Symbol () = default;

};

class Boolean final : public Symbol
{
    public:
        Boolean (bool f) :
            Symbol(Type::Boolean, f? "#T" : "#F")
        {}

        Boolean (const Boolean& rhs) : Symbol(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new Boolean(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

        bool operator== (const Symbol& rhs) { return _str == rhs._str; }
        bool operator!= (const Symbol& rhs) { return _str != rhs._str; }
        bool operator<  (const Symbol& rhs) { return _str <  rhs._str; }
        bool operator>  (const Symbol& rhs) { return _str >  rhs._str; }
        bool operator<= (const Symbol& rhs) { return _str <= rhs._str; }
        bool operator>= (const Symbol& rhs) { return _str >= rhs._str; }

        static Boolean* True (void);
        static Boolean* False (void);

    private:
        ~Boolean () = default;

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

        List (const List& rhs);

        static List* Nil (void);

        virtual Expr* clone (void) const override
        {
            return new List(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env);

        std::vector<Expr*>  _exprs;

    protected:
        virtual ~List () = default;

};

class ConsExpr final : public List
{
    public:
        ConsExpr () :
            List(Type::Cons)
        {}

        ConsExpr (const ConsExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new ConsExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~ConsExpr () = default;

};

class ListOpExpr final : public List
{
    public:
        ListOpExpr (const std::string& str) :
            List(Type::ListOp),
            _str(str)
        {}

        ListOpExpr (const ListOpExpr& rhs) : List(rhs), _str(rhs._str) {}

        virtual Expr* clone (void) const override
        {
            return new ListOpExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

        std::string _str;

    private:
        ~ListOpExpr () = default;

};

class ArithmeticExpr final : public List
{
    public:
        ArithmeticExpr (const std::string& str) :
            List(Type::Arithmetic),
            _str(str)
        {}

        ArithmeticExpr (const ArithmeticExpr& rhs) : List(rhs), _str(rhs._str) {}

        virtual Expr* clone (void) const override
        {
            return new ArithmeticExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

        std::string _str;

    private:
        ~ArithmeticExpr () = default;

};

class RelationExpr final : public List
{
    public:
        RelationExpr (const std::string& str) :
            List(Type::Relation),
            _str(str)
        {}

        RelationExpr (const RelationExpr& rhs) : List(rhs), _str(rhs._str) {}

        virtual Expr* clone (void) const override
        {
            return new RelationExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

        const std::string   _str;

    private:
        ~RelationExpr () = default;

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

        DefineExpr (const DefineExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new DefineExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~DefineExpr () = default;

};

class LetExpr final : public List
{
    public:
        LetExpr () : List(Type::Let)
        {}

        LetExpr (const LetExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new LetExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~LetExpr () = default;

};

class BeginExpr final : public List
{
    public:
        BeginExpr () : List(Type::Begin)
        {}

        BeginExpr (const BeginExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new BeginExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~BeginExpr () = default;

};

class LambdaExpr final : public List
{
    public:
        LambdaExpr () : List(Type::Lambda)
        {}
        LambdaExpr (std::vector<Expr*>& params, Expr* body);

        LambdaExpr (const LambdaExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new LambdaExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~LambdaExpr () = default;

};

class IfExpr final : public List
{
    public:
        IfExpr () :
            List(Type::If)
        {}

        IfExpr (const IfExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new IfExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~IfExpr () = default;

};

class CondExpr final : public List
{
    public:
        CondExpr () : List(Type::Cond)
        {}

        CondExpr (const CondExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new CondExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~CondExpr () = default;

};

class ElseExpr final : public List
{
    public:
        ElseExpr () : List(Type::Else)
        {}

        ElseExpr (const ElseExpr& rhs) : List(rhs) {}

        virtual Expr* clone (void) const override
        {
            return new ElseExpr(*this);
        }
        Expr* accept (IVisitor& visitor, Env& env) override;

    private:
        ~ElseExpr () = default;

};

}

#endif // EXPR_H
