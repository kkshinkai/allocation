#include <allocation.hpp>

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <new>

// The global operator new should never be called since it will usually indicate
// a memory leak.
#ifndef ALLOW_OPERATOR_NEW_USAGE
void *operator new(size_t size) noexcept(false) {
  assert(false && "should not call global operator new");
}

void *operator new[](size_t size) noexcept(false) {
  assert(false && "should not call global operator new[]");
}

void* operator new(size_t size, const std::nothrow_t &nothrow_constant) noexcept {
  assert(false && "should not call global operator new");
}

void* operator new[](size_t size, std::nothrow_t &nothrow_constant) noexcept {
  assert(false && "should not call global operator new[]");
}

void operator delete(void *p) noexcept {
  assert(false && "should not call global delete");
}

void operator delete[](void* p) noexcept {
  assert(false && "should not call global delete []");
}
#endif // ALLOW_OPERATOR_NEW_USAGE

void allocated_object::print() const {
  std::cout << "AllocatedObj(" << this << ")";
}

void allocated_object::print_value() const {
  std::cout << "AllocatedObj(" << this << ")";
}

void *c_heap_object::operator new(size_t size) noexcept(false) { DEBUG_PRINTER;
  return static_cast<void *>(allocate_heap(size));
}

void c_heap_object::operator delete(void *p) noexcept { DEBUG_PRINTER;
  free_heap(p);
}
