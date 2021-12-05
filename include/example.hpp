#ifndef Allocation_example_hpp__
#define Allocation_example_hpp__

#include <allocation.hpp>

class string_val: public c_heap_object {
 private:
  const char *string;

  static char *strcpy(const char *str);

 public:
  explicit string_val(const char *str) { string = strcpy(str); }

  ~string_val() {
    free_heap(const_cast<void *>(reinterpret_cast<const void *>(string)));
  }

};

class stack_integer: public stack_object {
 private:
  int value; // All fields are allocated on the stack.

 public:
  explicit stack_integer(int value): value(value) { DEBUG_PRINTER; }
  ~stack_integer() { DEBUG_PRINTER; }

  [[nodiscard]] int get_value() const { return value; }
};

#endif // Allocation_example_hpp__
