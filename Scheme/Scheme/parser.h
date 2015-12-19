#ifndef __PARSER_H__
#define __PARSER_H__

#include "lexer.h"
#include "ast.h"

namespace scheme
{
    namespace parser
    {
        using ast::ast_node;

        class parser
        {
        public:
            parser(lexer::lexer &l) : lexer(l) {}

            ast_node *parser_sexpr();

        protected:
            void advance();
            void match(lexer::token_kind kind);

        protected:
            lexer::lexer lexer;
            lexer::token token;
        };
    }
}
#endif // !__PARSER_H__

