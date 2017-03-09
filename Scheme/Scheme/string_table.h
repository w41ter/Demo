#ifndef __STRING_TABLE_H__
#define __STRING_TABLE_H__

#include <list>
#include <unordered_map>

namespace scheme
{
    namespace util
    {
        class string_table
        {
        public:
            ~string_table();
            const char *insert(const char *str, int len);

            static string_table &instance();
        private:
            std::list<const char *> table;
        };

        class identi_table
        {
            struct string
            {
                const char *str;
                int len;
                string *next;
            };
        public:
            identi_table(unsigned int hm) : hash_mod(hm) {}
            ~identi_table();

            const char *insert(const char *str, int len);

            static identi_table &instance();
        private:
            unsigned int hash_mod;
            std::unordered_map<unsigned int, string*> table;
        };
    }
}

#endif // !__STRING_TABLE_H__

