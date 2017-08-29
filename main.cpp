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
#include <iostream>

#include "Parser.h"
#include "Env.h"
#include "Visitor.h"
#include "Expr.h"
#include "AutoReleasePool.h"

#define REPL

namespace lx
{

class Repl
{
    public:
        static void run (void)
        {
            std::string line;
            Eval eval;
            Debugger debugger;
            Env env(nullptr);

            float a;
            try {
                while (1)
                {
                    printf(">");
                    std::getline(std::cin, line);
                    if (line == "quit") {
                        break;
                    }
                    a = std::stof(line);
                    printf("a: %f\n", a);
                    //debugger.call(eval.call(Parser::run(Tokenizer::run(line)), env));
                }
            }
            catch (const std::exception& e)
            {
                //printf("%s\n", e.what().c_str());
                std::cout << e.what() << std::endl;
                return;
            }
        }
};

Expr*
test (Eval& eval, Env& env, const std::string& code)
{
    Debugger debugger;
    printf("[Code]: %s\n", code.c_str());
    printf("[ParserResult]:\n");
    Expr* parserResult = debugger.call(Parser::run(Tokenizer::run(code)));
    printf("[EvalResult]:\n");
    Expr* evalResult = debugger.call(eval.call(parserResult, env));
    printf("\n");
    return evalResult;
}


}

int32_t
main (int32_t argc, char* argv[])
{
    using namespace lx;

    AutoReleasePool pool;

#ifdef REPL
    Repl::run();
#else
    // testcase
    Eval eval;
    Env env(nullptr);
    test(eval, env, "(1)");

    assert(dynamic_cast<Integer*>(test(eval, env, "(+ 2 3 -4)"))->_num == 1);
    assert(dynamic_cast<Integer*>(test(eval, env, "(- 2 3 -4)"))->_num == 3);
    assert(dynamic_cast<Integer*>(test(eval, env, "(* 2 3 -4)"))->_num == -24);
    assert(dynamic_cast<Integer*>(test(eval, env, "(/ 2 3 -4)"))->_num == 0);
    assert(dynamic_cast<Float*>(test(eval, env, "(+ 2 3.0 -4)"))->_num == 1.0);
    assert(dynamic_cast<Float*>(test(eval, env, "(- 2 3.0 -4)"))->_num == 3.0);
    assert(dynamic_cast<Float*>(test(eval, env, "(* 2 3.0 -4)"))->_num == -24.0);
    assert(dynamic_cast<Integer*>(test(eval, env, "(define a 3)"))->_num == 3);
    assert(dynamic_cast<Integer*>(test(eval, env, "(* (- 1 a 2) (+ 3 4) (/ 8 2))"))->_num == -112);
    assert(dynamic_cast<Integer*>(test(eval, env, "(define a -2)"))->_num == -2);
    assert(dynamic_cast<Integer*>(test(eval, env, "(* (- 1 a 2) (+ 3 4) (/ 8 2))"))->_num == 28);
    //assert(dynamic_cast<Symbol*>(test(eval, env, "#T"))->_str == "#T");
    //assert(dynamic_cast<Symbol*>(test(eval, env, "#F"))->_str == "#F");
    //assert(dynamic_cast<Integer*>(test(eval, env, "(cond ((> 1 2) 3) (else 4))"))->_num == 4);
    assert(dynamic_cast<Integer*>(test(eval, env, "(cond ((> 1 2) 3) ((<= 37 38) (+ 5 4)) (else 4))"))->_num == 9);
    test(eval, env, "(define empty_lambda (lambda () (+ 1 3)))");
    assert(dynamic_cast<Integer*>(test(eval, env, "(empty_lambda)"))->_num == 4);
    test(eval, env, "(define (factorials n) ( cond ((= n 1) 1) (else (* n (factorials (- n 1))))))");
    assert(dynamic_cast<Integer*>(test(eval, env, "(factorials 5)"))->_num == 120);
    test(eval, env, "(define (sqr x y) \
                            (begin \
                             (define (internal_func x) (* x x x)) \
                             (+ (* x x) (* y y) (internal_func y))))");
    assert(dynamic_cast<Integer*>(test(eval, env, "(sqr 3 4)"))->_num == 89);;
    //test(eval, env, "(< 423 534)");
    //test(eval, env, "(define sqr (lambda (x y) (+ (* x x) (* y y))))");
    //test(eval, env, "(sqr 3 4)");
    //test(eval, env, "((lambda (x y) (+ (* x x) (* y y))) 3 4)");
    //test(eval, env, "(define (sqr x y) (+ (* x x) (* y y)))");
    //test(eval, env, "(sqr 3 4)");
    //test(eval, env, "(1 2 3 (+ 1 4))");
    //test(eval, env, "(cons 1 (cons 2 3))");
    test(eval, env, "(define (factorials n) ( cond ((= n 1) 1) (else (* n (factorials (- n 1))))))");
    assert(dynamic_cast<Integer*>(test(eval, env, "(factorials 5)"))->_num == 120);
    test(eval, env, "(+ 7 3)");
    test(eval, env, "(- 7 3)");
    test(eval, env, "(* 7 3)");
    test(eval, env, "(/ 7 3)");

    test(eval, env, "(+ 7.2 3)");
    test(eval, env, "(- 7.2 3)");
    test(eval, env, "(* 7.2 3)");
    test(eval, env, "(/ 7.2 3)");

    test(eval, env, "(+ 7 3.4)");
    test(eval, env, "(- 7 3.4)");
    test(eval, env, "(* 7 3.4)");
    test(eval, env, "(/ 7 3.4)");

    test(eval, env, "(+ 7.2 3.4)");
    test(eval, env, "(- 7.2 3.4)");
    test(eval, env, "(* 7.2 3.4)");
    test(eval, env, "(/ 7.2 3.4)");
#endif

    return 0;
}
