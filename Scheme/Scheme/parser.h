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
            parser(lexer::lexer &&l) : lexer(std::move(l)), is_end(false) { advance(); }

            ast_node *parser_expr();

        protected:
            ast_node *parser_sexpr();
            ast_node *parser_keyword();
            ast::ast_body *parser_body();
            ast_node *parser_lambda();
            ast_node *parser_if();
            ast_node *parser_set();
            ast_node *parser_begin();
            ast_node *parser_define();

            void advance();
            void match(lexer::token_kind kind, const char *msg);

        protected:
            lexer::lexer &&lexer;
            lexer::token token;
            bool is_end;
        };
    }
}
#endif // !__PARSER_H__

