#include <iostream>
#include <vector>

int main()
{
  std::vector< long long > sequence;
  long long number = 0;

  while (std::cin >> number && number != 0) {
    sequence.push_back(number);
  }

  if (!std::cin && !std::cin.eof()) {
    std::cerr << "Error: invalid input\n";
    return 2;
  }

  if (sequence.size() < 3) {
    std::cerr << "Error: sequence must contain at least 3 elements\n";
    return 2;
  }

  int sum_duplicates = 0;
  int increasing_elements = 0;

  for (std::size_t i = 2; i < sequence.size(); ++i) {
    if (sequence[i] == sequence[i - 1] + sequence[i - 2]) {
      ++sum_duplicates;
    }
  }

  for (std::size_t i = 1; i < sequence.size(); ++i) {
    if (sequence[i] > sequence[i - 1]) {
      ++increasing_elements;
    }
  }

  std::cout << sum_duplicates << '\n';
  std::cout << increasing_elements << '\n';

  return 0;
}
