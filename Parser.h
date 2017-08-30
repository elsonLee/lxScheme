#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <string>
#include <vector>

#include "Expr.h"

namespace lx {

class Env;

class Tokenizer
{
    public:
        static std::vector<std::string> run (const std::string& str);
};

class Parser
{
    private:
        static bool is_digit (char c)
        {
            if (c >= '0' && c <= '9') {
                return true;
            } else {
                return false;
            }
        }

        // FIXME
        static bool is_integer (const std::string& token)
        {
            bool ret = false;
            uint32_t size = token.size();
            if (is_digit(token[0]) ||
                ((token[0] == '+' || token[0] == '-') && size > 1)) {
                ret = true;
                for (uint32_t i = 1; i < size; i++) {
                    if (!is_digit(token[i])) {
                        ret = false;
                        break;
                    }
                }
            }
            return ret;
        }

        // FIXME
        static bool is_float (const std::string& token)
        {
            bool ret = false;
            uint32_t size = token.size();
            if (is_digit(token[0]) ||
                ((token[0] == '+' || token[0] == '-') && size > 1)) {
                ret = true;
                bool has_dot = false;
                for (uint32_t i = 1; i < size; i++) {
                    if (token[i] == '.') {
                        if (!has_dot) {
                            has_dot = true;
                            continue;
                        } else {
                            ret = false;
                            break;
                        }
                    }
                    if (!is_digit(token[i])) {
                        ret = false;
                        break;
                    }
                }
            }
            return ret;
        }

    public:

        static Expr* run (std::vector<std::string>::const_iterator& iter);

        static Expr* run (const std::vector<std::string>& tokens);
};

}

#endif // PARSER_H
