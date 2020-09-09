#include <cstdio>
#include <vector>

int square(int a)
{
  return a * a;
}

int main()
{
  std::vector<int> v;

  for(int i = 0; i < 10; ++i) {
    v.push_back(i);
  }

  for(std::vector<int>::iterator it = v.begin();
      it != v.end();
      ++it) {
    const int sqrt = square(*it);
    printf("[%d] %d\n", *it, sqrt);
  }
}
