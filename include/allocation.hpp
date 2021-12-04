#ifndef Allocation_allocation_hpp__
#define Allocation_allocation_hpp__

#include <cstdlib>

// Basic allocation functions
inline char *allocate_heap(size_t size) {
  // `malloc()` returns a null pointer on failure. `malloc(0)` will return
  // either a null pointer or a unique pointer that can be successfully passed
  // to `free()`. To eliminate this uncertainty, `size` will be converted to `1`
  // if it is zero.
  if (size == 0)
    size = 1;

  return static_cast<char *>(malloc(size));
}

inline char *reallocate_heap(char *old, size_t size) {
  // For `realloc(old, size)`, if `old` is a null pointer, the `realloc`
  // function behaves like the `malloc` function for the specified size.
  // Otherwise, if `old` does not match a pointer earlier returned by a memory
  // management function, or if the space has been deallocated by a call to the
  // `free` or `realloc` function, the behavior is undefined. If memory for the
  // new object cannot be allocated, the old object is not deallocated and its
  // value is unchanged.

  // `realloc(nullptr, 0)` is the same as `malloc(0)`. I don't know why HotSpot
  // does not check if `size` is zero here.
  return static_cast<char *>(realloc(old, size));
}

inline char *free_heap(void *p) {
  free(p);
}

// All classes in the repo must be subclassed by one of these classes:
//
// - resource_object  - for objects that are allocated in resource area.
// - c_heap_object    - for objects that are allocated in the C heap (managed by
//                     `free` and `malloc`).
// - stack_object     - for objects allocated on the stack.
// - value_object     - for embedded objects.
// - all_static       - for classes used as name spaces.

#define ALLOCATION_SUPER_CLASS : public allocated_object

class allocated_object {
 public:
  void print() const;
  void print_value() const;
};

class c_heap_object ALLOCATION_SUPER_CLASS {
 public:
  void *operator new(size_t size) noexcept(false);
  void operator delete(void *p) noexcept;
};

#endif // Allocation_allocation_hpp__
