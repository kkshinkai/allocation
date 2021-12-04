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

#endif // Allocation_example_hpp__
