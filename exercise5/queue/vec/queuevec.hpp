
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,
                 virtual public Vector<Data> {


private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::Elements;
  ulong iPos = 0; // initial position
  ulong fPos = 0; // final position

public:

  // Default constructor
  QueueVec() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec&);

  // Move constructor
  QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec();

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec<Data>&);

  // Move assignment
  QueueVec& operator=(QueueVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec<Data>&) const noexcept;
  bool operator!=(const QueueVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  Data& Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override; // Override Container member

  inline ulong Size() const noexcept override; // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();
  void SwapVectors(ulong);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
