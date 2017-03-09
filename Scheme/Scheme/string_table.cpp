#include <string.h>
#include "string_table.h"
namespace scheme
{
    namespace util
    {
        static unsigned int ELFHash(const char *str, int len)
        {
            unsigned int h = 0;
            unsigned int x = 0;
            int i;

            for (i = 0; i < len; ++i)
            {
                h = (h << 4) + *str++;
                if ((x = h & 0xF0000000) != 0)
                {
                    h ^= x >> 24;
                    h &= ~x;
                }
            }

            return h;
        }

        string_table::~string_table()
        {
            for (auto i : this->table)
            {
                delete []i;
            }
        }

        const char * string_table::insert(const char * str, int len)
        {
            char *string = new char[len + 1];
            strncpy(string, str, len);
            string[len] = '\0';
            this->table.push_back(string);
            return string;
        }

        string_table & string_table::instance()
        {
            static string_table table;
            return table;
        }

        identi_table::~identi_table()
        {
            for (auto &i : this->table)
            {
                string *str = i.second;
                while (str != nullptr)
                {
                    string *tmp = str;
                    str = str->next;
                    delete []tmp->str;
                    delete tmp;
                }
                i.second = nullptr;
            }
        }

        const char * identi_table::insert(const char * str, int len)
        {
            unsigned int index = ELFHash(str, len) % this->hash_mod;
            string *s = this->table[index];
            while (s != nullptr)
            {
                if (strncmp(s->str, str, len) == 0)
                {
                    return s->str;
                }
                s = s->next;
            }
            s = new string;
            char *tmp = new char[len + 1];
            strncpy(tmp, str, len);
            tmp[len] = '\0';
            s->str = tmp;
            s->next = this->table[index];
            this->table[index] = s;
            return s->str;
        }

        identi_table & identi_table::instance()
        {
            static identi_table table(1024);
            return table;
        }

    }
}

