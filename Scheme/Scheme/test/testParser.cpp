#include <string>

#include "../input.h"
#include "../lexer.h"
#include "../ast.h"
#include "../parser.h"

using namespace std;
using namespace scheme::ast;
using namespace scheme::lexer;
using namespace scheme::parser;

class string_input : public input
{
public:
    string_input(const char *str) : file(str) { position = file.begin();}
    virtual ~string_input() {}
    virtual int getc() {
        if (position == file.end())
            return -1;
        int c = *position;
        position++;
        return c;
    }
    virtual void ungetc(int c) {
        if (position != file.begin())
            position--;
    }
protected:
    string file;
    string::iterator position;
};

class visitor : public ast_visitor
{
public:
    visitor() = default;
    
    virtual void visit(ast_literal &ast) override
    {
        cout << ast.get_name();
    }
    
    virtual void visit(ast_proceduce_call &ast) override
    {
        cout << "(";
        ast.get_function->accept(*this);
        for (auto i : ast.get_operand())
        {
            cout << ' ';
            i->accept(*this);
        }
        cout << ")";
    }
    
    virtual void visit(ast_conditional &ast) override
    {
        cout << "(if ";
        ast->get_test()->accept(*this);
        cout << ' ';
        ast->get_consequent()->accept(*this);
        if ((auto alter = ast->get_alternate()) != nullptr)
        {
            cout << ' ';
            alter->accept(*this);
        }
        cout << ")";
    }
    
    virtual void visit(ast_lambda &ast) override
    {
        
    }
    
    virtual void visit(ast_assignment &ast) = 0;
    virtual void visit(ast_variable &ast) = 0;
    virtual void visit(ast_begin &ast) = 0;
    virtual void visit(ast_define_function &ast) = 0;
    virtual void visit(ast_define_variable &ast) = 0;
    virtual void visit(ast_body &ast) = 0;
}