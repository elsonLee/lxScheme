#include <string>
#include <fstream>
#include <iostream>

#include "Parser.h"
#include "Env.h"
#include "Visitor.h"
#include "Expr.h"
#include "AutoReleasePool.h"

//#define REPL

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

            try {
                while (1)
                {
                    printf(">");
                    std::getline(std::cin, line);
                    if (line == "quit") {
                        break;
                    }
                    debugger.call(eval.call(Parser::run(Tokenizer::run(line)), env));
                }
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                return;
            }
        }
};

Expr*
run (Eval& eval, Env& env, const std::string& code)
{
    Debugger debugger;
    Expr* evalResult = nullptr;

    std::vector<std::string> tokens = Tokenizer::run(code);
    auto&& iter = tokens.cbegin();

    while (iter != tokens.cend())
    {
        printf("[Code]: %s\n", (*iter).c_str());
        printf("[ParserResult]:\n");
        Expr* parserResult = debugger.call(Parser::run(iter));
        //Expr* parserResult = Parser::run(iter);
        printf("[EvalResult]:\n");
        evalResult = debugger.call(eval.call(parserResult, env));
        //evalResult = eval.call(parserResult, env);
        printf("\n");
    }
    return evalResult;
}

void
add_global_symbol (Eval& eval, Env& env, const std::string& name, const std::string& code)
{
    Expr* expr = eval.call(Parser::run(Tokenizer::run(code)), env);
    env.define_symbol(name, expr);
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
    // runcase
    Eval eval;
    Env env(nullptr);
    add_global_symbol(eval, env, "+", "(+)");
    add_global_symbol(eval, env, "-", "(-)");
    add_global_symbol(eval, env, "*", "(*)");
    add_global_symbol(eval, env, "/", "(/)");

    // FIXME
    if (argc == 2) {
        std::string line;
        std::string code;
        std::string fileName(argv[1]);
        std::ifstream fileStream(fileName);
        if (fileStream) {
            while (getline(fileStream, line)) {
                code += line;
            }
        }
        fileStream.close();
        run(eval, env, code);
    }

#if 0
    assert(dynamic_cast<Integer*>(run(eval, env, "(+ 2 3 -4)"))->_num == 1);
    assert(dynamic_cast<Integer*>(run(eval, env, "(- 2 3 -4)"))->_num == 3);
    assert(dynamic_cast<Integer*>(run(eval, env, "(* 2 3 -4)"))->_num == -24);
    assert(dynamic_cast<Integer*>(run(eval, env, "(/ 2 3 -4)"))->_num == 0);
    assert(dynamic_cast<Float*>(run(eval, env, "(+ 2 3.0 -4)"))->_num == 1.0);
    assert(dynamic_cast<Float*>(run(eval, env, "(- 2 3.0 -4)"))->_num == 3.0);
    assert(dynamic_cast<Float*>(run(eval, env, "(* 2 3.0 -4)"))->_num == -24.0);
    assert(dynamic_cast<Integer*>(run(eval, env, "(define a 3)"))->_num == 3);
    assert(dynamic_cast<Integer*>(run(eval, env, "(* (- 1 a 2) (+ 3 4) (/ 8 2))"))->_num == -112);
    assert(dynamic_cast<Integer*>(run(eval, env, "(define a -2)"))->_num == -2);
    assert(dynamic_cast<Integer*>(run(eval, env, "(* (- 1 a 2) (+ 3 4) (/ 8 2))"))->_num == 28);
    //assert(dynamic_cast<Symbol*>(run(eval, env, "#T"))->_str == "#T");
    //assert(dynamic_cast<Symbol*>(run(eval, env, "#F"))->_str == "#F");
    //assert(dynamic_cast<Integer*>(run(eval, env, "(cond ((> 1 2) 3) (else 4))"))->_num == 4);
    assert(dynamic_cast<Integer*>(run(eval, env, "(cond ((> 1 2) 3) ((<= 37 38) (+ 5 4)) (else 4))"))->_num == 9);
    run(eval, env, "(define empty_lambda (lambda () (+ 1 3)))");
    assert(dynamic_cast<Integer*>(run(eval, env, "(empty_lambda)"))->_num == 4);
    run(eval, env, "(define (factorials n) ( cond ((= n 1) 1) (else (* n (factorials (- n 1))))))");
    assert(dynamic_cast<Integer*>(run(eval, env, "(factorials 5)"))->_num == 120);
    run(eval, env, "(define (sqr x y) \
                            (begin \
                             (define (internal_func x) (* x x x)) \
                             (+ (* x x) (* y y) (internal_func y))))");
    assert(dynamic_cast<Integer*>(run(eval, env, "(sqr 3 4)"))->_num == 89);;
    //run(eval, env, "(< 423 534)");
    //run(eval, env, "(define sqr (lambda (x y) (+ (* x x) (* y y))))");
    //run(eval, env, "(sqr 3 4)");
    //run(eval, env, "((lambda (x y) (+ (* x x) (* y y))) 3 4)");
    //run(eval, env, "(define (sqr x y) (+ (* x x) (* y y)))");
    //run(eval, env, "(sqr 3 4)");
    //run(eval, env, "(1 2 3 (+ 1 4))");
    //run(eval, env, "(cons 1 (cons 2 3))");
    run(eval, env, "(define (factorials n) ( cond ((= n 1) 1) (else (* n (factorials (- n 1))))))");
    assert(dynamic_cast<Integer*>(run(eval, env, "(factorials 5)"))->_num == 120);
    run(eval, env, "(+ 7 3)");
    run(eval, env, "(- 7 3)");
    run(eval, env, "(* 7 3)");
    run(eval, env, "(/ 7 3)");

    run(eval, env, "(+ 7.2 3)");
    run(eval, env, "(- 7.2 3)");
    run(eval, env, "(* 7.2 3)");
    run(eval, env, "(/ 7.2 3)");

    run(eval, env, "(+ 7 3.4)");
    run(eval, env, "(- 7 3.4)");
    run(eval, env, "(* 7 3.4)");
    run(eval, env, "(/ 7 3.4)");

    run(eval, env, "(+ 7.2 3.4)");
    run(eval, env, "(- 7.2 3.4)");
    run(eval, env, "(* 7.2 3.4)");
    run(eval, env, "(/ 7.2 3.4)");

    run(eval, env, "(if (> 3 2) 3.0 2)");
    run(eval, env, "(if (< 3 2) 3.0 2)");
    run(eval, env, "*");
    run(eval, env, "((if #F * +) 3 4 5)");
    run(eval, env, "(define (abs x) \
                        (cond ((> x 0) x) \
                              ((= x 0) 0) \
                              ((< x 0) (- x))))");
    run(eval, env, "(abs  8)");
    run(eval, env, "(abs -8) (abs -8.4)");
    run(eval, env, "(car (1 2 3))");
    run(eval, env, "(cdr (1 2 3))");
    run(eval, env, "(car (cons (1 2 3) (4 5 6)))");
    run(eval, env, "(cdr (cons (1 2 3) (cons 12 (4 5 6))))");
    run(eval, env, "(cons (1 2 3) (cons 12 nil))");
    run(eval, env, "(define (sqr x y) \
                            (begin \
                             (define (internal_func x) (* x x x)) \
                             (+ (* x x) (* y y) (internal_func y))))");
    run(eval, env, "(sqr 3 4)");
#endif


#endif

    return 0;
}
