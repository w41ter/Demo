#include <iostream>
#include <string>
#include <stdexcept>

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
        auto token = ast.get_token();
        switch (token.kind) 
        {
        case token_kind::TK_NUMBER:
            cout << token.value.num;
            break;
        case token_kind::TK_REAL:
            cout << token.value.fnum;
            break;
        case token_kind::TK_CHAR:
            cout << token.value.c;
            break;
        case token_kind::TK_STRING:
            cout << token.value.string.str;
            break;
        case token_kind::TK_BOOL:
            cout << ((token.val == token_value::TV_TRUE) ? "#t" : "#f");
            break;
        default:
            cout << "nil";
            break;
        }
    }
    
    virtual void visit(ast_proceduce_call &ast) override
    {
        cout << "(";
        ast.get_function()->accept(*this);
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
        ast.get_test()->accept(*this);
        cout << ' ';
        ast.get_consequent()->accept(*this);
        ast_node *alter = nullptr;
        if ((alter = ast.get_alternate()) != nullptr)
        {
            cout << ' ';
            alter->accept(*this);
        }
        cout << ")";
    }
    
    virtual void visit(ast_lambda &ast) override
    {
        cout << "(lambda ( ";
        auto &arguments = ast.get_arguments();
        if (arguments.size() > 0)
        {
            for (auto i : arguments)
            {
                i->accept(*this);
                cout << ' ';
            }
        }
        cout << ") ";
        ast.get_body()->accept(*this);
        cout << ")";
    }
    
    virtual void visit(ast_assignment &ast) override 
    {
        cout << "(set! ";
        ast.get_variable()->accept(*this);
        cout << ' ';
        ast.get_expr()->accept(*this);
        cout << ")";
    }
    
    virtual void visit(ast_variable &ast) override
    {
        cout << ast.get_name();
    }
    
    virtual void visit(ast_begin &ast) override
    {
        cout << "(begin";
        for (auto i : ast.get_exprs())
        {
            cout << ' ';
            i->accept(*this);
        }
        cout << ")";
    }
    
    virtual void visit(ast_define_function &ast) override
    {
        cout << "(define (" << ast.get_name();
        for (auto i : ast.get_params())
        {
            cout << ' ' << i;
        }
        cout << ") "; 
        ast.get_body()->accept(*this);
        cout << ")";
    }
    
    virtual void visit(ast_define_variable &ast) override 
    {
        cout << "(define " << ast.get_variable();
        cout << ' ';
        ast.get_expr()->accept(*this);
        cout << ")";
    }
    
    virtual void visit(ast_body &ast) override 
    {
        for (auto i : ast.get_exprs())
        {
            i->accept(*this);
        }
    }
};

int main(int argc, char**argv)
{
    const char *data = " (a b)\
              ((a b) a (b))                                              \
              (define x (expr)) \
              (define (func x) x)   \
              (define (func) (b x)) \
              (set! x (var s))  \
              (set! x b)        \
              (lambda (x y) (body)) \
              (lambda () x)         \
              ((lambda (x y) (body) (body))(a b))    \
              (if x x)              \
              (if x x x)            \
              (if (condtion) x)     \
              (begin x x x x x x)   \
              ()                   \
              #f #t \"sgttr\" 12 0.2 #\\b \
     ";
    string_input in(data);
    lexer lex(in);
    parser pas(std::move(lex));
    visitor visit;
    ast_node *node = nullptr;
    try {
        while ((node = pas.parser_expr()) != nullptr)
        {
            node->accept(visit);
            cout << endl;
        }
    } catch (exception &e) {
        cout << "new exception:" << e.what() << endl;
    }
    return 0;
}