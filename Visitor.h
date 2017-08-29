#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <vector>

namespace lx {

class Env;
class Expr;
class Integer;
class Float;
class Symbol;
class Boolean;
class List;
class ConsExpr;
class ArithmeticExpr;
class RelationExpr;
class DefineExpr;
class BeginExpr;
class IfExpr;
class CondExpr;
class ElseExpr;
class LambdaExpr;

class IVisitor
{
    public:
        virtual ~IVisitor () = default;

        virtual Expr* run (Integer* number,      Env& env) = 0;
        virtual Expr* run (Float* number,        Env& env) = 0;
        virtual Expr* run (Symbol* sym,          Env& env) = 0;
        virtual Expr* run (Boolean* sym,         Env& env) = 0;
        virtual Expr* run (List* list,           Env& env) = 0;
        virtual Expr* run (ConsExpr* expr,       Env& env) = 0;
        virtual Expr* run (ArithmeticExpr* expr, Env& env) = 0;
        virtual Expr* run (RelationExpr* expr,   Env& env) = 0;
        virtual Expr* run (DefineExpr* expr,     Env& env) = 0;
        virtual Expr* run (BeginExpr* expr,      Env& env) = 0;
        virtual Expr* run (IfExpr* expr,         Env& env) = 0;
        virtual Expr* run (CondExpr* expr,       Env& env) = 0;
        virtual Expr* run (ElseExpr* expr,       Env& env) = 0;
        virtual Expr* run (LambdaExpr* expr,     Env& env) = 0;
};

class Debugger final : public IVisitor
{
    public:
        Debugger () = default;

        Expr* call (Expr* expr);

        Expr* run_relation_proc (RelationExpr* expr,     Env& env);
        Expr* run_arithmetic_proc (ArithmeticExpr* expr, Env& env);
        Expr* run_specific_proc (List* expr,             Env& env);

        Expr* run (Integer* number,      Env& env) override;
        Expr* run (Float* number,        Env& env) override;
        Expr* run (Symbol* sym,          Env& env) override;
        Expr* run (Boolean* sym,         Env& env) override;
        Expr* run (List* list,           Env& env) override;
        Expr* run (ConsExpr* expr,       Env& env) override;
        Expr* run (ArithmeticExpr* expr, Env& env) override;
        Expr* run (RelationExpr* expr,   Env& env) override;
        Expr* run (DefineExpr* expr,     Env& env) override;
        Expr* run (BeginExpr* expr,      Env& env) override;
        Expr* run (LambdaExpr* expr,     Env& env) override;
        Expr* run (IfExpr* expr,         Env& env) override;
        Expr* run (CondExpr* expr,       Env& env) override;
        Expr* run (ElseExpr* expr,       Env& env) override;
};

class Eval final : public IVisitor
{
    private:
        Expr* run_proc (LambdaExpr* lambda, std::vector<Expr*>& args, Env& env);

    public:
        Eval () = default;

        Expr* call (Expr* expr, Env& env);

        Expr* run (Integer* number,      Env& env) override;
        Expr* run (Float* number,        Env& env) override;
        Expr* run (Symbol* sym,          Env& env) override;
        Expr* run (Boolean* sym,         Env& env) override;
        Expr* run (List* list,           Env& env) override;
        Expr* run (ConsExpr* expr,       Env& env) override;
        Expr* run (ArithmeticExpr* expr, Env& env) override;
        Expr* run (RelationExpr* expr,   Env& env) override;
        Expr* run (DefineExpr* expr,     Env& env) override;
        Expr* run (BeginExpr* expr,      Env& env) override;
        Expr* run (LambdaExpr* expr,     Env& env) override;
        Expr* run (IfExpr* expr,         Env& env) override;
        Expr* run (CondExpr* expr,       Env& env) override;
        Expr* run (ElseExpr* expr,       Env& env) override;
};

}

#endif // VISITOR_H
