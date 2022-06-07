
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public DictionaryContainer<Data>,
            virtual public BinaryTreeLnk<Data> {

private:

  // ...

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::head;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&); // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data>&);

  // Move constructor
  BST(BST<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST<Data>& operator=(const BST<Data>&);

  // Move assignment
  BST<Data>& operator=(BST<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BST<Data>&) const noexcept;
  inline bool operator!=(const BST<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Min() const; // (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  virtual void RemoveMin(); // (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const; // (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  virtual void RemoveMax(); // (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

  virtual const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual void Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  virtual void Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  virtual void Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

protected:

  // Auxiliary member functions

  Data DataNDelete(NodeLnk*);

  BST<Data>::NodeLnk* Detach(NodeLnk*&) noexcept;

  BST<Data>::NodeLnk* DetachMin(NodeLnk*&) noexcept;
  BST<Data>::NodeLnk* DetachMax(NodeLnk*&) noexcept;

  BST<Data>::NodeLnk* Skip2Left(NodeLnk*&) noexcept;
  BST<Data>::NodeLnk* Skip2Right(NodeLnk*&) noexcept;

  BST<Data>::NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept; // Both mutable & unmutable versions
  BST<Data>::NodeLnk* const& FindPointerToMin(NodeLnk* const&) const noexcept; // Both mutable & unmutable versions

  BST<Data>::NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept; // Both mutable & unmutable versions
  BST<Data>::NodeLnk* const& FindPointerToMax(NodeLnk* const&) const noexcept; // Both mutable & unmutable versions

  BST<Data>::NodeLnk*& FindPointerTo(NodeLnk*&, const Data&) noexcept; // Both mutable & unmutable versions
  BST<Data>::NodeLnk* const& FindPointerTo(NodeLnk* const&, const Data&) const noexcept; // Both mutable & unmutable versions

  BST<Data>::NodeLnk*& FindPointerToPredecessor(NodeLnk*&, const Data&) noexcept; // Both mutable & unmutable versions
  BST<Data>::NodeLnk* const& FindPointerToPredecessor(NodeLnk* const&, const Data&) const noexcept; // Both mutable & unmutable versions

  BST<Data>::NodeLnk*& FindPointerToSuccessor(NodeLnk*&, const Data&) noexcept; // Both mutable & unmutable versions
  BST<Data>::NodeLnk* const& FindPointerToSuccessor(NodeLnk* const&, const Data&) const noexcept; // Both mutable & unmutable versions

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
