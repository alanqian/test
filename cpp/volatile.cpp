#include <iostream>

using namespace std;

void a()
{
    int array[10];
    //volatile int array[10];
    for (int i = 0; i < 10; i++)
        array[i] = i*10;
}

void b()
{
    int array[10];
    for (int i = 0; i < 10; i++)
        cout << array[i] << endl;
}

int main()
{
    a();
    b();
}

