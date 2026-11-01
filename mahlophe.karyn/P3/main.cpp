#include <fstream>
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "Error: expected 3 arguments\n";
    return 2;
  }

  const std::string mode = argv[1];

  if (mode != "1" && mode != "2") {
    std::cerr << "Error: invalid mode\n";
    return 2;
  }

  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  std::ofstream output(argv[3]);

  if (!output.is_open()) {
    std::cerr << "Error: cannot open output file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;

  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
    std::cerr << "Error: invalid matrix dimensions\n";
    return 2;
  }

  if (mode == "1" && (rows == 0 || cols == 0)) {
    output << "0\n";
    return 0;
  }

  if (mode == "2" && (rows == 0 || cols == 0)) {
    output << rows << ' ' << cols << '\n';
    return 0;
  }

  if (cols > 0
      && static_cast< unsigned long long >(rows)
          > static_cast< unsigned long long >(__SIZE_MAX__ / static_cast< std::size_t >(cols))) {
    std::cerr << "Error: matrix is too large\n";
    return 2;
  }

  const std::size_t size = static_cast< std::size_t >(rows) * static_cast< std::size_t >(cols);

  std::unique_ptr< long long[] > matrix(new long long[size]);

  for (std::size_t i = 0; i < size; ++i) {
    if (!(input >> matrix[i])) {
      std::cerr << "Error: not enough matrix data\n";
      return 2;
    }
  }

  if (mode == "1") {
    int count = 0;

    for (int offset = 1; offset < cols; ++offset) {
      bool contains_zero = false;
      const int length = (rows < cols - offset) ? rows : cols - offset;

      for (int i = 0; i < length; ++i) {
        const std::size_t index
            = static_cast< std::size_t >(i) * static_cast< std::size_t >(cols) + static_cast< std::size_t >(i + offset);

        if (matrix[index] == 0) {
          contains_zero = true;
          break;
        }
      }

      if (!contains_zero) {
        ++count;
      }
    }

    for (int offset = 1; offset < rows; ++offset) {
      bool contains_zero = false;
      const int length = (rows - offset < cols) ? rows - offset : cols;

      for (int j = 0; j < length; ++j) {
        const std::size_t index
            = static_cast< std::size_t >(j + offset) * static_cast< std::size_t >(cols) + static_cast< std::size_t >(j);

        if (matrix[index] == 0) {
          contains_zero = true;
          break;
        }
      }

      if (!contains_zero) {
        ++count;
      }
    }

    output << count << '\n';
  } else {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        const int top = i;
        const int left = j;
        const int bottom = rows - 1 - i;
        const int right = cols - 1 - j;

        const int layer
            = (top < bottom ? (top < left ? (top < right ? top : right) : (left < right ? left : right))
                            : (bottom < left ? (bottom < right ? bottom : right) : (left < right ? left : right)));

        const std::size_t index
            = static_cast< std::size_t >(i) * static_cast< std::size_t >(cols) + static_cast< std::size_t >(j);

        matrix[index] += layer + 1;
      }
    }

    output << rows << ' ' << cols << '\n';

    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        const std::size_t index
            = static_cast< std::size_t >(i) * static_cast< std::size_t >(cols) + static_cast< std::size_t >(j);

        if (j > 0) {
          output << ' ';
        }

        output << matrix[index];
      }

      output << '\n';
    }
  }

  return 0;
}
