#ifndef Allocation_allocation_hpp__
#define Allocation_allocation_hpp__

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

#endif // Allocation_allocation_hpp__
