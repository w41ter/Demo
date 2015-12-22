#include <cctype>
#include <exception>
#include <map>
#include <assert.h>
#include <cstring>

#include "string_table.h"
#include "lexer.h"

namespace scheme
{
    namespace lexer
    {
        std::map<const char*, token_value> &keywords()
        {
            static std::map<const char*, token_value> key;
            return key;
        }

        void init_keywords()
        {
            using table = util::identi_table;

            auto &keyword = keywords();
            token_value token[] = {
                token_value::TV_IF,          // if
                token_value::TV_LAMBDA,      // lambda
                token_value::TV_SET,         // set!
                token_value::TV_BEGIN,       // begin 
                token_value::TV_LET,         // let 
                token_value::TV_DEFINE,      // define 
            };

            const char *name[] = { "if", "lambda", "set!", "begin", "let", "define" };
            int length = sizeof(token) / sizeof(char*);//std::end(token) - std::begin(token);
            for (int i = 0; i < length; ++i)
            {
                table::instance();
                const char *t = name[i];
                int a = strlen(name[i]);
                const char *tmp = table::instance().insert(name[i], strlen(name[i]));
                keyword[tmp] =
                    token[i];
            }
        }

        token_value is_keyword(const char *addr)
        {
            auto &keyword = keywords();
            if (keyword.count(addr) != 0)
            {
                return keyword[addr];
            }
            return token_value::TV_VAR;
        }

        token lexer::peek(int index)
        {
            assert(index > 0);
            while (this->token_pool.size() < index)
            {
                token t = this->get_next();
                if (t.kind == token_kind::TK_END)
                {
                    throw std::runtime_error("意外结束文件分析！");
                }
                this->token_pool.push(t);
            }
            return this->token_pool.front();
        }

        token lexer::get()
        {
            if (this->token_pool.size() > 1)
            {
                token t = this->token_pool.front();
                this->token_pool.pop();
                return t;
            }
            else
            {
                return this->get_next();
            }
        }
        
        token lexer::make_token(token_kind k)
        {
            token tok;
            tok.kind = k;
            tok.line = this->line;
            tok.col = this->col;
            return tok;
        }

        token lexer::make_token(char c)
        {
            token tok;
            tok.kind = token_kind::TK_CHAR;
            tok.value.c = c;
            tok.line = this->line;
            tok.col = this->col;
            return tok;
        }

        token lexer::make_token(bool s)
        {
            token tok;
            tok.kind = token_kind::TK_BOOL;
            tok.line = this->line;
            tok.col = this->col;
            tok.val = s ? token_value::TV_TRUE : token_value::TV_FALSE;
            return tok;
        }

        token lexer::make_token(const char * str, int len)
        {
            const char *tmp = util::identi_table::instance().insert(str, len);
            token_value tv = is_keyword(tmp);
            token tok;
            tok.kind = tv == token_value::TV_VAR ? token_kind::TK_ID : token_kind::TK_KEYWORD;
            tok.val = tv;
            tok.line = this->line;
            tok.col = this->col;
            tok.value.string.str = tmp;
            tok.value.string.len = len;
            return tok;
        }

        token lexer::make_token(int num)
        {
            token tok;
            tok.kind = token_kind::TK_NUMBER;
            tok.line = this->line;
            tok.col = this->col;
            tok.value.num = num;
            return tok;
        }

        token lexer::make_token(float fnum)
        {
            token tok;
            tok.kind = token_kind::TK_REAL;
            tok.line = this->line;
            tok.col = this->col;
            tok.value.fnum = fnum;
            return tok;
        }

        token lexer::get_char()
        {
            char ch = this->in.getc();
            if (std::isalpha(ch) || ch == ' ' || ch == '\n')
                return make_token(ch);
            throw std::runtime_error(std::string("invalid sharp-sign prefix #") + ch);
        }

        token lexer::get_next()
        {
            char ch;
            while ((ch = this->in.getc()) != -1) {
                switch (ch) {
                case ' ': case '\t': case '\n': case '\r':
                    if (ch == '\n')
                        ++this->line, this->col = 0;
                    else 
                        ++this->col; 
                    continue;
                case '(':
                    return make_token(token_kind::TK_LPAREN);
                case ')':                    
                    return make_token(token_kind::TK_RPAREN);
                case '\'':
                    return make_token(token_kind::TK_QUOTE);
                case '+':
                case '-':
                    return get_peculiar_identifier(ch);
                case ';':
                    skip_comment(); continue;
                case '"':
                    return get_string();
                case '#':
                    return get_pound_special();
                default:
                    if (std::isdigit(ch)) return get_number(ch);
                    if (is_initial(ch)) return get_identifier(ch);
                    throw std::runtime_error(std::string("invalid character: ") + ch);
                }
            }

            return make_token(token_kind::TK_END);
        }
        token lexer::get_identifier(char ch) 
        {
            std::string sym;
            do
            {
                if (std::isalpha(ch))
                    ch = std::tolower(ch);
                sym += ch;
                ch = this->in.getc();
            } while (is_subsequent(ch));
            if (!is_delimiter(ch))
                throw std::runtime_error(std::string("invalid identifier syntax ") + (char)this->in.getc());
            this->in.ungetc(ch);
            return make_token(sym.c_str(), sym.size());
        }

        token lexer::get_peculiar_identifier(char ch)
        {
            std::string sym(1, ch);
            char c = this->in.getc();
            this->in.ungetc(c);
            if (!is_delimiter(c))
                return get_number(ch);

            return make_token(sym.c_str(), sym.size());
        }

        int lexer::to_number(char ch)
        {
            if (std::isxdigit(ch))
                return ch - 'a' + 10;
            else
                return ch - '0';
        }

        int lexer::get_real(int radix, char ch)
        {
            int value = 0;
            if (std::isdigit(ch))
                throw std::runtime_error("need number");

            while (std::isxdigit(ch))
            {
                int v = to_number(ch);
                if (0 > v || radix <= v)
                    throw std::runtime_error(std::string("error radix character: ") + ch);
                value *= radix;
                value += v;
                ch = this->in.getc();
            }
            return value;
        }

        token lexer::get_number(char ch) 
        {
            int radix = 10;
            char exactness = ' ';
            // prefix 
            while (ch == '#')
            {
                ch = this->in.getc();
                switch (ch)
                {
                case 'i':
                    exactness = 'i';
                    break;
                case 'e':
                    exactness = 'e';
                    break;
                case 'b':
                    radix = 2;
                    break;
                case 'o':
                    radix = 8;
                    break;
                case 'x':
                    radix = 16;
                    break;
                }
                ch = this->in.getc();
            }
            // complex
            int value = 0, suffix = 0;
            bool sign = true;

            {
                if (ch == '+' || ch == '-')
                {
                    sign = '+' == ch;
                    ch = this->in.getc();
                }
                value = get_real(radix, ch);
                if (ch == '.')
                {
                    suffix = get_real(radix, ch);
                    float s = suffix;
                    while (s >= 1)
                        s /= 10;
                    s += value;
                    s *= sign ? 1 : -1;
                    return make_token(s);
                }
                return make_token(value * (sign ? 1 : -1));
            }
        }

        void lexer::skip_comment(void) 
        {
            char ch = ';';
            while (ch != '\r' && ch != '\n')
            {
                ch = this->in.getc();
            }
            this->line++;
            this->col = 0;
        }

        token lexer::get_string()
        {
            std::string str = "";
            bool state = false;
            while (true)
            {
                char ch = this->in.getc();
                if (state)
                {
                    if (ch == '\\')
                        str += '\\';
                    else if (ch == '"')
                        str += '"';
                    else if (ch == 'n')
                        str += '\n';
                    else if (ch == 'r')
                        str += '\r';
                    else if (ch == 't')
                        str += '\t';
                    else
                        throw std::runtime_error(std::string("unexcepted escape character \\") + ch);
                    state = false;
                    continue;
                }
                if (ch == '\\')
                {
                    state = true;
                    continue;
                }
                if (ch == '"')
                    break;
                str += ch;
            }
            
            token tok;
            tok.kind = token_kind::TK_STRING;
            tok.line = this->line;
            tok.col = this->col;
            tok.value.string.str = util::string_table::instance().insert(str.c_str(), str.size());
            tok.value.string.len = str.size();
            return tok;
        }

        token lexer::get_pound_special()
        {
            char ch = this->in.getc();
            switch (ch) 
            {
            case 't':
                ch = this->in.getc();
                this->in.ungetc(ch);
                if (!is_delimiter(ch))
                    throw std::runtime_error(std::string("invalid special #t" + ch));
                return make_token(true);
            case 'f':
                ch = this->in.getc();
                this->in.ungetc(ch);
                if (!is_delimiter(ch))
                    throw std::runtime_error(std::string("invalid special #f" + ch));
                return make_token(true);
            case 'b':
            case 'o':
            case 'd':
            case 'x':
            case 'i':
            case 'e':
                this->in.ungetc(ch);
                return get_number('#');
            case '\\':
                return get_char();
            default:
                throw std::runtime_error(std::string("invalid special #" + ch));
            }
        }

        bool lexer::is_special_initial(char ch) {
            static const char special[] = {
                '!', '$', '%', '&', '*', '/', ':', '<', '=',
                '>', '?', '^', '_', '~'
            };
            const int N = sizeof(special) / sizeof(char);

            const char *s;

            for (s = special; s < special + N && *s != ch; s++)
                ;
            return (s != special + N);
        }

        bool lexer::is_initial(char ch) 
        {
            return std::isalpha(ch) || is_special_initial(ch);
        }

        bool lexer::is_subsequent(char ch)
        {
            if (std::isdigit(ch) || ch == '+' || ch == '-' || ch == '.' || ch == '@')
                return true;
            return is_initial(ch);
        }

        bool lexer::is_delimiter(char ch)
        {
            static const char delimiters[] = {
                '\t', '\n', '\r', ' ', '"', '(', ')', ';'
            };
            const int N = sizeof(delimiters) / sizeof(char);
            const char *s;

            for (s = delimiters; s < delimiters + N && *s != ch; s++)
                ;
            return (s != delimiters + N);
        }
    }
}

