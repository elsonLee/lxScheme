#ifndef ENV_H
#define ENV_H

#include <string>
#include <vector>
#include <unordered_map>

namespace lx {

class Expr;
class Frame
{
    public:
        void add_symbol (const std::string& var, Expr* val);

        bool set_symbol (const std::string& var, Expr* val);

        Expr* query_symbol (const std::string& var) const;

    private:
        std::unordered_map<std::string, Expr*>   _variables;
};

class Env
{
    public:
        Env (Env* upperEnv) :
            _upperEnv(upperEnv), _frame()
        {
            printf("Add Env: %p [%p]\n", this, upperEnv);
        }

        Env (Env& upperEnv) :
            _upperEnv(&upperEnv), _frame()
        {
            printf("Add Env: %p [%p]\n", this, &upperEnv);
        }

        ~Env () {
           printf("Del Env: %p]\n", this);
        }

        void extend_symbols (std::vector<std::string>& params,
                             std::vector<Expr*>& args);

        Expr* query_symbol (const std::string& var) const;

        bool set_symbol (const std::string& var, Expr* val);

        void define_symbol (const std::string& var, Expr* val);

    public:
        Env*    _upperEnv;

    private:
        Frame   _frame;
};

}

#endif // ENV_H
