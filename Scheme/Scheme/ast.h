#ifndef __AST_H__
#define __AST_H__

#include <vector>

namespace scheme
{
    namespace ast
    {
        class ast_visitor;

        class ast_node
        {
        public:
            virtual void accept(ast_visitor &v) = 0;
        };

        class ast_literal : public ast_node
        {
        public:
            ast_literal(lexer::token tok) : token(tok) {}

            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            lexer::token token;
        };

        class ast_proceduce_call : public ast_node
        {
        public:
            ast_proceduce_call() {}

            void push_back(ast_node *node)
            {
                this->operand.push_back(node);
            }

            virtual void accept(ast_visitor &v) override { v.visit(*this); }

        protected:
            std::vector<ast_node*> operand;
        };

        class ast_conditional : public ast_node
        {
        public:
            ast_conditional() : alternate(nullptr) {}

            void push_test(ast_node *node) { test = node; }
            void push_consequent(ast_node *node) { consequent = node; }
            void push_alternate(ast_node *node) { alternate = node; }

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
            void push_formal(ast_variable *v) { var = v; }
            void push_body(ast_node *node) { body = node; }

            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            std::vector<ast_variable*> arguments;
            ast_variable *var;
            ast_node *body;
        };

        class ast_assignment : public ast_node
        {
        public:
            ast_assignment() {}
            void push_var(ast_variable *v) { var = v; }
            void push_expr(ast_node *node) { expr = node; }

            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            ast_variable *var;
            ast_node *expr;
        };

        class ast_variable : public ast_node
        {
        public:
            ast_variable(const char *n) : name(n) {}

            virtual void accept(ast_visitor &v) override { v.visit(*this); }
        protected:
            const char *name;
        };

        class ast_derived_expr : public ast_node
        {

        };

        class ast_macro_use : public ast_node
        {

        };

        class ast_macro_block : public ast_node
        {

        };

        //template<typename T>
        class ast_visitor
        {
        public:
            virtual void visit(ast_literal &ast) = 0;
            virtual void visit(ast_proceduce_call &ast) = 0;
            virtual void visit(ast_conditional &ast) = 0;
            virtual void visit(ast_lambda &ast) = 0;
            virtual void visit(ast_assignment &ast) = 0;
            virtual void visit(ast_variable &ast) = 0;
            virtual void visit(ast_derived_expr &ast) = 0;
            virtual void visit(ast_macro_use &ast) = 0;
            virtual void visit(ast_macro_block &ast) = 0;
        };
    }
}

#endif // !__AST_H__

