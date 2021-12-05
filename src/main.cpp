#include <example.hpp>
#include <cstdio>

int main() {

  printf("\n# Example for C-Heap object:\n");
  auto str = new string_val("Hello, world!");
  delete str;

  printf("\n# Example for Stack object:\n");
  {
    auto stack_i = stack_integer(42);
    printf("%d\n", stack_i.get_value());

    // auto err = new stack_integer(42);
    //            ^^^ error: 'operator new' is a private member of 'stack_object'
  }

  return 0;
}