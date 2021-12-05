#ifndef Allocation_allocation_hpp__
#define Allocation_allocation_hpp__

#include <cstdlib>
#include <cstdio>

#define DEBUG_PRINTER printf("%s\n", __func__)

// ------------------------ Basic allocation functions -------------------------

// enum class alloc_fail_strategy { EXIT_OOM, RETURN_NULL };

inline char *allocate_heap(size_t size) { DEBUG_PRINTER;
  // `malloc()` returns a null pointer on failure. `malloc(0)` will return
  // either a null pointer or a unique pointer that can be successfully passed
  // to `free()`. To eliminate this uncertainty, `size` will be converted to `1`
  // if it is zero.
  if (size == 0)
    size = 1;

  return static_cast<char *>(malloc(size));
}

inline char *reallocate_heap(char *old, size_t size) { DEBUG_PRINTER;
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

inline void free_heap(void *p) { DEBUG_PRINTER; free(p); }

// -------------------------- Allocation base class ----------------------------

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
  virtual void print() const;
  virtual void print_value() const;
};

// ----------------------------- C-Heap object ---------------------------------

// C-heap objects are allocated in the C heap (managed by `free` and `malloc`).
// Any class that needs to be allocated by `new` and `delete` must be a subclass
// of it.
class c_heap_object ALLOCATION_SUPER_CLASS {
 public:
  void *operator new(size_t size) noexcept(false);
  void operator delete(void *p) noexcept;
};

// ------------------------------ Stack object ---------------------------------

// Base class for objects allocated on the stack only. Calling `new` or `delete`
// will result in fatal error.
class stack_object ALLOCATION_SUPER_CLASS {
 private:
  void *operator new(size_t size) noexcept(false);
  void *operator new[](size_t size) noexcept(false);
  void operator delete(void *p) noexcept;
  void operator delete[](void *p) noexcept;
};

#endif // Allocation_allocation_hpp__
