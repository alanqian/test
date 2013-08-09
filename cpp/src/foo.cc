#include "foo.h"


foo_t::foo_t()
{
    _a = _b = 0;
}

foo_t::foo_t(int a, int b)
{
    _a = a;
    _b = b;
}

ostream& foo_t::dump(ostream& os)
{
    os << "foo_t: {_a: " << _a << "; _b: " << _b << ";}" << endl;
    return os;
}

