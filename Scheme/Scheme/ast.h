#ifndef __AST_H__
#define __AST_H__

#include <vector>

#include "lexer.h"

namespace scheme
{
    namespace ast
    {
        class ast_node;
        class ast_literal;
        class ast_proceduce_call;
        class ast_conditional;
        class ast_lambda;
        class ast_assignment;
        class ast_variable;
        class ast_begin;
        class ast_define_function;
        class ast_define_variable;
        class ast_body;

        class ast_visitor
        {
        public:
            virtual void visit(ast_literal &ast) = 0;
            virtual void visit(ast_proceduce_call &ast) = 0;
            virtual void visit(ast_conditional &ast) = 0;
            virtual void visit(ast_lambda &ast) = 0;
            virtual void visit(ast_assignment &ast) = 0;
            virtual void visit(ast_variable &ast) = 0;
            virtual void visit(ast_begin &ast) = 0;
            virtual void visit(ast_define_function &ast) = 0;
            virtual void visit(ast_define_variable &ast) = 0;
            virtual void visit(ast_body &ast) = 0;
        };

        class ast_node
        {
        public:
            virtual void accept(ast_visitor &v) = 0;
        };

        class ast_literal : public ast_node
        {
        public:
            ast_literal(lexer::token tok) : token(tok) {}
            lexer::token get_token() const { return token; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            lexer::token token;
        };

        class ast_proceduce_call : public ast_node
        {
        public:
            ast_proceduce_call() {}

            void push_back(ast_node *node) { this->operand.push_back(node); }
            void push_function(ast_node *node) { function = node; }
            ast_node *get_function() const { return function; }
            std::vector<ast_node*> &get_operand() { return operand; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }

        protected:
            ast_node *function;
            std::vector<ast_node*> operand;
        };

        class ast_conditional : public ast_node
        {
        public:
            ast_conditional() : alternate(nullptr) {}

            void push_test(ast_node *node) { test = node; }
            void push_consequent(ast_node *node) { consequent = node; }
            void push_alternate(ast_node *node) { alternate = node; }
            ast_node *get_test() const { return test; }
            ast_node *get_consequent() const { return consequent; }
            ast_node *get_alternate() const { return alternate; }
            virtual void accept(ast_visitor &v) { v.visit(*this); }
        protected:
            ast_node *test;
            ast_node *consequent;
            ast_node *alternate;
        };

        class ast_lambda : public ast_node
        {
        public:
            ast_lambda() {}

            void push_argument(ast_variable *v) { arguments.push_back(v); }
            void push_body(ast_body *node) { body = node; }

            std::vector<ast_variable*> &get_arguments() { return arguments; }
            ast_body *get_body() const { return body; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            std::vector<ast_variable*> arguments;
            ast_body *body;
        };

        class ast_assignment : public ast_node
        {
        public:
            ast_assignment() {}
            void push_var(ast_variable *v) { var = v; }
            void push_expr(ast_node *node) { expr = node; }
            ast_variable *get_variable() const { return var; }
            ast_node *get_expr() const { return expr; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            ast_variable *var;
            ast_node *expr;
        };

        class ast_variable : public ast_node
        {
        public:
            ast_variable(const char *n) : name(n) {}

            const char *get_name() const { return name; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            const char *name;
        };

        class ast_begin : public ast_node
        {
        public:
            ast_begin() = default;

            void push_back(ast_node *node) { this->exprs.push_back(node); }
            std::vector<ast_node*> &get_exprs() { return exprs; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            std::vector<ast_node*> exprs;
        };

        class ast_define_variable : public ast_node
        {
        public:
            ast_define_variable() = default;

            void push_var(const char *v) { var = v; }
            void push_expr(ast_node *node) { expr = node; }
            const char *get_variable() const { return var; }
            ast_node *get_expr() const { return expr; }
            virtual void accept(ast_visitor &v) { v.visit(*this); }
        protected:
            const char *var;
            ast_node *expr;
        };

        class ast_define_function : public ast_node
        {
        public:
            ast_define_function() = default;

            void push_name(const char *n) { name = n; }
            void push_param(const char *p) { param.push_back(p); }
            void push_body(ast_node *b) { body = b; }
            const char *get_name() const { return name; }
            std::vector<const char*> &get_params() { return param; }
            ast_node *get_body() const { return body; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            const char *name;
            std::vector<const char*> param;
            ast_node *body;
        };

        class ast_body : public ast_node
        {
        public:
            ast_body() = default;
            void push_expr(ast_node *expr) { exprs.push_back(expr); }
            std::vector<ast_node*> get_exprs() { return exprs; }
            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            std::vector<ast_node *> exprs;
        };
    }
}

#endif // !__AST_H__

