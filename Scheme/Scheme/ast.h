#ifndef __AST_H__
#define __AST_H__

namespace scheme
{
    namespace ast
    {

        class ast_node
        {

        };

        class ast_literal : public ast_node
        {

        };

        class ast_proceduce_call : public ast_node
        {

        };

        class ast_conditional : public ast_node
        {

        };

        class ast_lambda : public ast_node
        {

        };

        class ast_assignment : public ast_node
        {

        };

        class ast_variable : public ast_node
        {

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
            virtual void visti(ast_variable &ast) = 0;
            virtual void visit(ast_derived_expr &ast) = 0;
            virtual void visit(ast_macro_use &ast) = 0;
            virtual void visit(ast_macro_block &ast) = 0;
        };
    }
}

#endif // !__AST_H__

