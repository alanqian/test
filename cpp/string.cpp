#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, const char* argv[]) 
{
  string s("abc");
  string t;

  t = s;   // Data typically shared between s and t.
  printf("t=%p, s=%p\n", s.data(), t.data());

  if (1)
  {
    char& c(s[1]);
    printf("t=%p, s=%p\n", s.data(), t.data());

    c = 'z';     // How many strings does this modify?
    if (t[1] == 'z') {
      printf("wrong\n");
    } else {
      printf("right\n");
    }
  }
}

