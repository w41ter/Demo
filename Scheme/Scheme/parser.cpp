#include <exception>
#include "parser.h"

namespace scheme
{
    namespace parser
    {
        ast_node * parser::parser_expr()
        {
            advance();
            return parser_sexpr();
        }

        ast_node * parser::parser_sexpr()
        {
            using lexer::token_kind;

            switch (this->token.kind)
            {
            case token_kind::TK_ID:
                return new ast::ast_variable(this->token.value.string.str);
            case token_kind::TK_CHAR:
            case token_kind::TK_STRING:
            case token_kind::TK_NUMBER:
            case token_kind::TK_REAL:
            case token_kind::TK_COMPLEX:
                return new ast::ast_literal(this->token);
            case token_kind::TK_LPAREN:
            {
                advance();
                if (this->token.kind == token_kind::TK_KEYWORD)
                {
                    auto node = parser_keyword();
                    match(token_kind::TK_RPAREN);
                    return node;
                }
                else if (this->token.kind == token_kind::TK_RPAREN)
                {
                    return new ast::ast_literal(this->token);
                }
                else
                {
                    auto node = new ast::ast_proceduce_call();
                    while (this->token.kind != token_kind::TK_RPAREN)
                    {
                        node->push_back(parser_sexpr());
                        advance();
                    }
                    return node;
                }
            }
            default:
                throw std::runtime_error("error");
            }
        }
        ast_node * parser::parser_keyword()
        {
            using lexer::token_kind;
            using lexer::token_value;

            switch (this->token.val)
            {
            case token_value::TV_LAMBDA:
                return parser_lambda();
            case token_value::TV_IF:
                return parser_if();
            case token_value::TV_SET:
                return parser_set();
            default:
                break;
            }
        }
        ast_node * parser::parser_lambda()
        {
            using lexer::token_kind;
            using lexer::token_value;

            advance();
            auto *node = new ast::ast_lambda();
            if (token_kind::TK_LPAREN == token.kind)
            {
                advance();
                while (token_kind::TK_ID == token.kind)
                {
                    node->push_argument(new ast::ast_variable(token.value.string.str));
                    advance();
                }
                if (token.kind == token_kind::TK_DOT)
                {
                    advance();
                    if (token_kind::TK_ID != token.kind)
                    {
                        throw std::runtime_error("need var");
                    }
                    node->push_formal(new ast::ast_variable(token.value.string.str));
                    advance();
                }
                match(token_kind::TK_RPAREN);
            }
            else if (token_kind::TK_ID == token.kind)
            {
                node->push_formal(new ast::ast_variable(this->token.value.string.str));
                advance();
            }
            else
            {
                throw std::runtime_error("error");
            }
            node->push_body(parser_body());
            match(token_kind::TK_RPAREN);
            return node;
        }
        ast_node * parser::parser_if()
        {
            advance();
            ast::ast_conditional *if_ = new ast::ast_conditional();
            if_->push_test(parser_expr());
            if_->push_consequent(parser_expr());
            if (lexer::token_kind::TK_RPAREN != token.kind)
                if_->push_alternate(parser_expr());
            match(lexer::token_kind::TK_RPAREN);
            return if_;
        }
        ast_node * parser::parser_set()
        {
            advance();
            ast::ast_assignment *set = new ast::ast_assignment();
            if (lexer::token_kind::TK_ID != token.kind)
                throw std::runtime_error("È±ÉÙ¶ÔÏó");
            set->push_var(new ast::ast_variable(token.value.string.str));
            advance();
            set->push_expr(parser_expr());
        }

        ast_node * parser::parser_body()
        {
            return nullptr;
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
            {   // todo more humantic information
                throw std::runtime_error("Exception ...");
            }
        }
    }
}