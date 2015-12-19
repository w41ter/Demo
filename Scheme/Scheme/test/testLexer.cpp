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

#define Except(k) \
do { \
    assert(tok.kind == k);  \
    tok = lex.get();        \
} while (0)     

int main() {
    const char *data = "\
        ((let var b))   \
        #()'`,,@. + - ...\
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
    Except(token_kind::TK_DONT_KNOW);
    Except(token_kind::TK_RPAREN);    
    Except(token_kind::TK_QUOTE);
    Except(token_kind::TK_BACKTICKS);
    Except(token_kind::TK_COMMA);
    Except(token_kind::TK_COMMA_AT);
    Except(token_kind::TK_DOT);    
    Except(token_kind::TK_ID);
    Except(token_kind::TK_ID);
    Except(token_kind::TK_ID);
    return 0;
}