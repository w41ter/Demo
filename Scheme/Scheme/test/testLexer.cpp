#define TEST_MAIN
#include "UnitTest.h"

#include <string>
#include <assert.h>

#include "../input.h"
#include "../lexer.h"

using namespace std;
using namespace scheme::lexer;

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

#define Except(k)               \
do {                            \
    TEST_CHECK(tok.kind == k);  \
    tok = lex.get();            \
} while (0)     

TEST_CASE(testLexer) {
    const char *data = "\
        ((define var b))   \
        () + - \
        #f #t \"sgttr\" 12 0.2 #\\b \
    ";
    string_input in(data);
    lexer lex(in);
    token tok = lex.get();
    
    Except(token_kind::TK_LPAREN);
    Except(token_kind::TK_LPAREN);
    Except(token_kind::TK_KEYWORD);
    Except(token_kind::TK_ID);
    Except(token_kind::TK_ID);
    Except(token_kind::TK_RPAREN);
    Except(token_kind::TK_RPAREN);
    Except(token_kind::TK_LPAREN);
    Except(token_kind::TK_RPAREN);
    Except(token_kind::TK_ID);
    Except(token_kind::TK_ID);
    Except(token_kind::TK_BOOL);
    Except(token_kind::TK_BOOL);
    Except(token_kind::TK_STRING);
    Except(token_kind::TK_NUMBER);
    Except(token_kind::TK_REAL);
    Except(token_kind::TK_CHAR);
}