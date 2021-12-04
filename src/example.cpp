#include <example.hpp>
#include <allocation.hpp>
#include <cstring>

char *string_val::strcpy(const char *str) {
  size_t size = strlen(str);
  char *cpy_str = allocate_heap(size + 1);
  if (cpy_str == nullptr) return nullptr;
  ::strcpy(cpy_str, str);
  return cpy_str;
}
