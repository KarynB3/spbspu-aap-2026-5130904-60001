#include <iostream>
#include <cstddef>

namespace mahlophe
{
  bool analyze(std::istream & in, std::size_t & count, std::size_t & sumDup, std::size_t & incSeq)
  {
    int prev1 = 0;
    int prev2 = 0;
    int x = 0;
    while (true)
    {
      if (!(in >> x))
      {
        return false;
      }
      if (x == 0)
      {
        return true;
      }
      if (count >= 1 && x > prev1)
      {
        ++incSeq;
      }
      if (count >= 2 && static_cast< long long >(x) == static_cast< long long >(prev1) + prev2)
      {
        ++sumDup;
      }
      prev2 = prev1;
      prev1 = x;
      ++count;
    }
  }
}

int main()
{
  std::size_t count = 0;
  std::size_t sumDup = 0;
  std::size_t incSeq = 0;
  if (!mahlophe::analyze(std::cin, count, sumDup, incSeq))
  {
    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }
  int result = 0;
  if (count < 3)
  {
    std::cerr << "Error: sequence is too short for SUM-DUP\n";
    result = 2;
  }
  else
  {
    std::cout << sumDup << "\n";
  }
  std::cout << incSeq << "\n";
  return result;
}
