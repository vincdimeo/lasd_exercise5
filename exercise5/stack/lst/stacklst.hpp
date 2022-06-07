
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>,
                 virtual public List<Data> {


private:

  // ...

protected:

  using List<Data>::size;

  using List<Data>::head;

  // ...

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst<Data>&);

  // Move constructor
  StackLst(StackLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst();

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst<Data>&);

  // Move assignment
  StackLst& operator=(StackLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst<Data>&) const noexcept;
  bool operator!=(const StackLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) noexcept override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
