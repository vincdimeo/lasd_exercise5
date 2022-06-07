
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  struct NodeVec : virtual public BinaryTree<Data>::Node {

  private:

    // ...

  protected:

    // ...

  public:

    Data value;
    ulong index = 0;
    Vector<NodeVec*>* nodeVec;

    /* ************************************************************************ */

    // Destructor
    ~NodeVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    NodeVec& operator=(const NodeVec&);

    // Move assignment
    NodeVec& operator=(NodeVec&&) noexcept;

    /* ************************************************************************ */

    // Specific member functions

    virtual Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
    virtual const Data& Element() const noexcept override; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept override; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

    virtual NodeVec& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    virtual NodeVec& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

    /* ************************************************************************ */
  };

  Vector<NodeVec*> vec;

public:

  // Default constructor
  BinaryTreeVec();

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  struct BinaryTreeVec<Data>::NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  // void MapBreadth(const MapFunctor, void*) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  // void FoldBreadth(FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
