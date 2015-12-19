#ifndef __INPUT_H__
#define __INPUT_H__

#include "language_extend.h"

namespace scheme
{
    namespace lexer
    {
        /// interface of input.
        class input : public uncopiable
        {
        public:
            input() {}
            virtual ~input() {};
            virtual int getc() = 0;
            virtual void ungetc(int c) = 0;
        };
    }
}

#endif // __INPUT_H__
