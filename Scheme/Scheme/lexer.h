#ifndef __LEXER_H__
#define __LEXER_H__

#include <queue>

#include "input.h"

namespace scheme
{
    namespace lexer
    {
        enum class token_kind
        {
            TK_ID,
            TK_CHAR,
            TK_BOOL,
            TK_STRING,
            TK_COMPLEX,
            TK_REAL,
            TK_NUMBER,      
            TK_LPAREN,      // (
            TK_RPAREN,      // )
            TK_DOT,         // .
            TK_COMMA,       // ,
            TK_COMMA_AT,    // ,@
            TK_BACKTICKS,   // `
            TK_QUOTE,       // '
            TK_DONT_KNOW,   // #(
            TK_KEYWORD,
            TK_END,
        };

        enum class token_value
        {
            TV_VAR,

            // bool
            TV_FALSE,
            TV_TRUE,

            // keyword
            TV_IF,          // if
            TV_ELSE,        // else
            TV_QUOTE,       // quote
            TV_LAMBDA,      // lambda
            TV_SET,         // set!
            TV_BEGIN,       // begin 
            TV_COND,        // cond 
            TV_AND,         // and 
            TV_OR,          // or 
            TV_CASE,        // case
            TV_LET,         // let 
            TV_LET_SATR,    // let* 
            TV_LETREC,      // letrec 
            TV_DO,          // do 
            TV_DELAY,       // delay 
            TV_QUASIQUTO,   // quasiquote
            TV_IS,          // => 
            TV_DEFINE,      // define 
            TV_UNQUOTE,     // unquote 
            TV_UNQUOTE_SPLICING,    // unquote-splicing
        };

        struct token
        {
            token_kind kind;
            token_value val;
            unsigned int line, col;
            union {
                char c;
                int num;
                float fnum;
                struct {
                    int real;
                    int comp;
                } complex;
                struct {
                    const char *str;
                    int len;
                } string;
            } value;
        };

        void init_keywords();

        class lexer
        {
        public:
            lexer(input &i) : in(i), line(0), col(0) { init_keywords(); }

            token peek(int index);
            token get();

        protected:
            token make_token(int real, int comp);
            token make_token(token_kind k);
            token make_token(char c);
            token make_token(bool s);
            token make_token(const char *str, int len = 1);
            token make_token(int num);
            token make_token(float fnum);

            token get_char();
            token get_next();
            token get_identifier(char ch);
            token get_peculiar_identifier(char ch);
            token get_number(char ch);
            token get_dot();
            token get_pound_special();
            token get_string();

            bool is_delimiter(char ch);
            bool is_initial(char ch);
            bool is_special_initial(char ch);
            bool is_subsequent(char ch);

            int to_number(char ch);
            int get_real(int radix, char ch);

            void skip_comment(void);
        protected:
            input &in;

            std::queue<token> token_pool;

            int line;
            int col;
        };
    }
}

#endif // __LEXER_H__
