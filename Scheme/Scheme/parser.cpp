#include <iostream>
#include <stdexcept>
#include "parser.h"

namespace scheme
{
    namespace parser
    {
        ast_node * parser::parser_expr()
        {
            //std::cout << "begin parser:" << std::endl;
            return parser_sexpr();
        }

        ast_node * parser::parser_sexpr()
        {
            //std::cout << "parser_sexpr" << std::endl;
            using lexer::token_kind;

            switch (this->token.kind)
            {
            case token_kind::TK_END:
                return nullptr;
            case token_kind::TK_ID:
            {
                auto var = this->token.value.string.str;
                advance();
                return new ast::ast_variable(var);
            }
            case token_kind::TK_CHAR:
            case token_kind::TK_STRING:
            case token_kind::TK_NUMBER:
            case token_kind::TK_REAL:
            case token_kind::TK_BOOL:
            {
                auto tok = token;
                advance();
                return new ast::ast_literal(tok);
            }
            case token_kind::TK_LPAREN:
            {
                advance();
                if (this->token.kind == token_kind::TK_KEYWORD)
                {
                    auto node = parser_keyword();
                    //match(token_kind::TK_RPAREN);
                    return node;
                }
                else if (this->token.kind == token_kind::TK_RPAREN)
                {
                    auto tok = token;
                    advance();
                    return new ast::ast_literal(tok);
                }
                else
                {
                    auto node = new ast::ast_proceduce_call();
                    node->push_function(parser_sexpr());
                    while (this->token.kind != token_kind::TK_RPAREN)
                    {
                        node->push_back(parser_sexpr());
                    }
                    advance();
                    return node;
                }
            }
            default:
                throw std::runtime_error("error");
            }
        }

        ast_node * parser::parser_keyword()
        {
            //std::cout << "parser_keyword" << std::endl;
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
            case token_value::TV_BEGIN:
                return parser_begin();
            case token_value::TV_DEFINE:
                return parser_define();
            default:
                // todo
                break;
            }
        }

        ast_node * parser::parser_define()
        {
            //std::cout << "parser_define" << std::endl;
            using lexer::token_kind;

            advance();
            if (token.kind == token_kind::TK_LPAREN) 
            {
                auto node = new ast::ast_define_function();
                advance();
                if (token.kind != token_kind::TK_ID)
                {
                    // error
                }
                node->push_name(token.value.string.str);
                advance();
                while (token.kind == token_kind::TK_ID)
                {
                    node->push_param(token.value.string.str);
                    advance();
                }
                match(token_kind::TK_RPAREN, "need ) after define function params");
                node->push_body(parser_body());
                match(token_kind::TK_RPAREN, "need ) after define function body");
                return node;
            } 
            else if (token.kind == token_kind::TK_ID)
            {
                auto node = new ast::ast_define_variable();
                node->push_var(token.value.string.str);
                advance();
                node->push_expr(parser_sexpr());
                match(token_kind::TK_RPAREN, "need ) after define variable");
                //match(token_kind::TK_RPAREN);
                return node;
            }
            else
            {
                throw std::runtime_error("define just for function or variable!");
            }
        }

        ast_node * parser::parser_begin()
        {
            advance();
            auto node = new ast::ast_begin();
            do {
                node->push_back(parser_sexpr());
            } while (token.kind != lexer::token_kind::TK_RPAREN);
            advance();
            return node;
        }

        ast_node * parser::parser_lambda()
        {
            //std::cout << "parser_lambda" << std::endl;
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
                match(token_kind::TK_RPAREN, "need ) after lambda params");
            }
            else
            {
                throw std::runtime_error("error");
            }
            node->push_body(parser_body());
            match(token_kind::TK_RPAREN, "need ) after lambda body");
            return node;
        }

        ast_node * parser::parser_if()
        {
            //std::cout << "parser_if" << std::endl;
            advance();
            ast::ast_conditional *if_ = new ast::ast_conditional();
            if_->push_test(parser_expr());
            if_->push_consequent(parser_expr());
            if (lexer::token_kind::TK_RPAREN != token.kind)
                if_->push_alternate(parser_expr());
            match(lexer::token_kind::TK_RPAREN, "except ) after if");
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
            match(lexer::token_kind::TK_RPAREN, "need ) after set!");
            return set;
        }

        ast::ast_body * parser::parser_body()
        {
            auto node = new ast::ast_body();
            do {
                node->push_expr(parser_sexpr());
            } while (token.kind != lexer::token_kind::TK_RPAREN);
            return node;
        }

        void parser::advance()
        {
            //std::cout << "  get next token:" << std::endl;
            if (is_end)
                throw std::runtime_error("accident done the program find.");
            this->token = this->lexer.get();
            if (token.kind == lexer::token_kind::TK_END)
                is_end = true;
        }

        void parser::match(lexer::token_kind kind, const char *msg)
        {
            if (this->token.kind == kind)
            {
                advance();
            } 
            else
            {   // todo more humantic information
                throw std::runtime_error(msg);
            }
        }
    }
}