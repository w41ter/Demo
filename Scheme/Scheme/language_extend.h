#ifndef __LANGUAGE_EXTEND_H__
#define __LANGUAGE_EXTEND_H__

//
// defend heritable.
//
template <typename OnlyFriend>
class uninheritable
{
    friend OnlyFriend;
    uninheritable(void) {}
};

class uncopiable
{
public:
    uncopiable() {}
    uncopiable(const uncopiable &) = delete;
};

#endif // !__LANGUAGE_EXTEND_H__

