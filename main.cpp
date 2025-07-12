#include <iostream>
#include "schedule.hpp"

void add(int x , int y)
{
  int s = x + y;
  std::cout << "x + y = " << s << '\n';
}

void multiply(int x , int y)
{
  int s = x * y;
  std::cout << "x * y = " << s << '\n';
}

int main()
{
  scheduler<int, int> s(3.f);
  s.add(add, 3, 5);
  s.add(multiply, 3, 5);

  std::cout << s.size() << '\n';

  s.run();
  return 0;
}
