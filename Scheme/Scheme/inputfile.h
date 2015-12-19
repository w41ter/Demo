#ifndef __INPUT_FILE_H__
#define __INPUT_FILE_H__

#include <fstream>

#include "input.h"

namespace scheme
{
    namespace lexer
    {


        class input_file : public input
        {
        public:
            input_file(const char *file);
            virtual ~input_file();

            virtual int getc() override;
            virtual void ungetc(int c) override;

        protected:
            std::fstream file;
        };
    }
}

#endif // __INPUT_FILE_H__