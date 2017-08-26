#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <utility>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include "Parser.h"
#include "Env.h"
#include "Visitor.h"
#include "Expr.h"
#include "AutoReleasePool.h"

namespace lx
{

Expr*
test (Eval& eval, Env& env, const std::string& code)
{
    Debugger debugger;
    printf("[Code]: %s\n", code.c_str());
    Expr* parserResult = debugger.call("ParserResult", Parser::run(Tokenizer::run(code)));
    Expr* evalResult = debugger.call("EvalResult", eval.call(parserResult, env));
    printf("\n");
    return evalResult;
}


}

int32_t
main (int32_t argc, char* argv[])
{
    using namespace lx;

    AutoReleasePool pool;

    Eval eval;

    Env env(nullptr);

    // testcase
    test(eval, env, "(1)");
    assert(dynamic_cast<Number*>(test(eval, env, "(+ 2 3 -4)"))->_num == 1);
    assert(dynamic_cast<Number*>(test(eval, env, "(- 2 3 -4)"))->_num == 3);
    assert(dynamic_cast<Number*>(test(eval, env, "(* 2 3 -4)"))->_num == -24);
    assert(dynamic_cast<Number*>(test(eval, env, "(/ 2 3 -4)"))->_num == 0);
    assert(dynamic_cast<Number*>(test(eval, env, "(define a 3)"))->_num == 3);
    assert(dynamic_cast<Number*>(test(eval, env, "(* (- 1 a 2) (+ 3 4) (/ 8 2))"))->_num == -112);
    assert(dynamic_cast<Number*>(test(eval, env, "(define a -2)"))->_num == -2);
    assert(dynamic_cast<Number*>(test(eval, env, "(* (- 1 a 2) (+ 3 4) (/ 8 2))"))->_num == 28);
    assert(dynamic_cast<Symbol*>(test(eval, env, "#T"))->_str == "#T");
    assert(dynamic_cast<Symbol*>(test(eval, env, "#F"))->_str == "#F");
    assert(dynamic_cast<Number*>(test(eval, env, "(cond ((> 1 2) 3) (else 4))"))->_num == 4);
    assert(dynamic_cast<Number*>(test(eval, env, "(cond ((> 1 2) 3) ((<= 37 38) (+ 5 4)) (else 4))"))->_num == 9);
    test(eval, env, "(define empty_lambda (lambda () (+ 1 3)))");
    assert(dynamic_cast<Number*>(test(eval, env, "(empty_lambda)"))->_num == 4);
    test(eval, env, "(define (factorials n) ( cond ((= n 1) 1) (else (* n (factorials (- n 1))))))");
    assert(dynamic_cast<Number*>(test(eval, env, "(factorials 5)"))->_num == 120);
    test(eval, env, "(define (factorials n) ( cond ((= n 1) 1) (else (* n (factorials (- n 1))))))");
    assert(dynamic_cast<Number*>(test(eval, env, "(factorials 5)"))->_num == 120);
    test(eval, env, "(define (sqr x y) \
                            (begin \
                             (define (internal_func x) (* x x x)) \
                             (+ (* x x) (* y y) (internal_func y))))");
    assert(dynamic_cast<Number*>(test(eval, env, "(sqr 3 4)"))->_num == 89);;
    //test(eval, env, "(< 423 534)");
    //test(eval, env, "(define sqr (lambda (x y) (+ (* x x) (* y y))))");
    //test(eval, env, "(sqr 3 4)");
    //test(eval, env, "((lambda (x y) (+ (* x x) (* y y))) 3 4)");
    //test(eval, env, "(define (sqr x y) (+ (* x x) (* y y)))");
    //test(eval, env, "(sqr 3 4)");
    //test(eval, env, "(1 2 3 (+ 1 4))");
    //test(eval, env, "(cons 1 (cons 2 3))");

    return 0;
}
