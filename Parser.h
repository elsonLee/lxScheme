#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <string>
#include <vector>

#include "Expr.h"

namespace lx {

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
        static bool is_num (const std::string& token)
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

        static Expr* run (std::vector<std::string>::const_iterator& iter);

    public:

        static Expr* run (const std::vector<std::string>& tokens)   // FIXME
        {
            auto&& iter = tokens.begin();
            return run(iter);
        }
};

}

#endif // PARSER_H
