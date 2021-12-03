#include <allocation.hpp>

#include <iostream>

void allocated_object::print() const {
  std::cout << "AllocatedObj(" << this << ")";
}

void allocated_object::print_value() const {
  std::cout << "AllocatedObj(" << this << ")";
}
