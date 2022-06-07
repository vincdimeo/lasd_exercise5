
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>,
                 virtual public Vector<Data> {


private:

  // ...

protected:

  using Vector<Data>::size;

  using Vector<Data>::Elements;

  ulong numElements = 0;

public:

  // Default constructor
  StackVec() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const LinearContainer<Data>&); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec&);

  // Move constructor
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec();

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec<Data>&);

  // Move assignment
  StackVec& operator=(StackVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data>&) const noexcept;
  inline bool operator!=(const StackVec<Data>&) const noexcept;

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

  inline bool Empty() const noexcept override; // Override Container member

  inline ulong Size() const noexcept override; // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
