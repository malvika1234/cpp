#include <string>
#include <vector>

class Foo
{
public:
  template<typename... T>
  Foo(T&&... t)
  : mV{t...}
  {
  }

private:
  std::vector<std::string> mV;
};

class Bar
{
public:
  Bar(std::string&& t)
  : mString{t}
  {
  }

private:
  std::string mString;
};

int main()
{
  Foo{"a", "b", "c"};

  Foo{"x"};

  Bar{"bar"};
}
