#include <exception>
#include "parser.h"

namespace scheme
{
    namespace parser
    {
        ast_node * parser::parser_sexpr()
        {
            
        }
        void parser::advance()
        {
            this->token = this->lexer.get();
        }
        void parser::match(lexer::token_kind kind)
        {
            if (this->token.kind == kind)
            {
                advance();
            } 
            else
            {
                throw std::runtime_error("Exception ...");
            }
        }
    }
}