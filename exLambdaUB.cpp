#include <iostream>
#include <string>

auto makeLambda()
{
  const std::string val = "on stack created";
  return [&] { return val; };
}

int main()
{
  auto bad = makeLambda();
  std::cout << bad() << std::endl;
}
