#ifndef __FOO_H__
#define  __FOO_H__

#include <iostream>

class foo_t {
public:
    foo_t();
    foo_t(int a, int b);
    ostream& dump(ostream& os);

private:
    int _a;
    int _b;
};

#endif // __FOO_H__
