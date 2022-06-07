
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> {

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeLnk : virtual public BinaryTree<Data>::Node {

  private:

    // ...

  protected:



  public:

    Data value;
    NodeLnk* leftNode = nullptr;
    NodeLnk* rightNode = nullptr;

    // Constructor
    NodeLnk(const Data&);

    /* ********************************************************************** */

    // Destructor
    ~NodeLnk();

    /* ********************************************************************** */

    // Copy assignment
    NodeLnk& operator=(const NodeLnk&);

    // Move assignment
    NodeLnk& operator=(NodeLnk&&) noexcept;

    /* ********************************************************************** */

    // Specific constructors
    NodeLnk(const LinearContainer<Data>&, ulong);

    /* ********************************************************************** */

    // Specific member functions

    Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const noexcept override; // Immutable access to the element (concrete function should not throw exceptions)

    bool IsLeaf() const noexcept override; // (concrete function should not throw exceptions)
    bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

    NodeLnk& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    NodeLnk& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

    /* ********************************************************************** */

  };

  NodeLnk* head = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>&) const noexcept;
  bool operator!=(const BinaryTreeLnk<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  struct BinaryTreeLnk<Data>::NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
