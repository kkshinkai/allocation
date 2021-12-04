#include <example.hpp>
#include <cstdio>

int main() {

  printf("# Example for C-Heap object:");
  auto str = new string_val("Hello, world!");
  delete str;

  return 0;
}