#include <cassert>
#include <string>
#include <unordered_map>

#include "Visitor.h"
#include "Env.h"

class Expr;

namespace lx {

//! Frame

void
Frame::add_symbol (const std::string& var, Expr* val)
{
    printf("Add Sym: %s\n", var.c_str());
    assert(_variables.find(var) == _variables.end());
    _variables.insert(std::make_pair(var, val));
}

bool
Frame::set_symbol (const std::string& var, Expr* val)
{
    printf("Set Sym: %s\n", var.c_str());
    const auto& iter = _variables.find(var);
    if (iter == _variables.end()) {
        return false;
    } else {
        iter->second = val;
        return true;
    }
}

Expr*
Frame::query_symbol (const std::string& var) const
{
    const auto& iter = _variables.find(var);
    if (iter == _variables.end()) {
        return nullptr;
    } else {
        printf("Query Sym: %s\n", var.c_str());
        return iter->second;
    }
}

//! Env

void
Env::extend_symbols (std::vector<std::string>& params,
                     std::vector<Expr*>& args)
{
    uint32_t argsSize = args.size();
    for (uint32_t i = 0; i < argsSize; i++) {
        define_symbol(params[i], args[i]);
    }
}

Expr*
Env::query_symbol (const std::string& var) const
{
    Expr* ret = _frame.query_symbol(var);

    if (!ret && _upperEnv) {
        ret = _upperEnv->query_symbol(var);
    }

    if (!ret) {
        printf("[Warning] Cannot find symbol %s\n", var.c_str());
    }

    return ret;
}

bool
Env::set_symbol (const std::string& var, Expr* val)
{
    // FIXME
    Eval eval;
    val = eval.call(val, *this);

    if (_frame.set_symbol(var, val)) {
        return true;
    } else if (_upperEnv) {
        return _upperEnv->set_symbol(var, val);
    } else {
        return false;
    }
}

void
Env::define_symbol (const std::string& var, Expr* val)
{
    // FIXME
    Eval eval;
    val = eval.call(val, *this);

    if (_frame.query_symbol(var)) {
        _frame.set_symbol(var, val);
    } else {
        _frame.add_symbol(var, val);
    }
}

}
