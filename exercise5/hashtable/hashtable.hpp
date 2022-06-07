
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

// std::default_random_engine randomGen;

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:

  // returns the key
  ulong operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>,
                  virtual public MappableContainer<Data>,
                  virtual public FoldableContainer<Data> {

private:

  // ...

protected:

  using DictionaryContainer<Data>::size; // number of elements in HT
  ulong sizeHT = 256; // size of HashTable
  Hash<Data> hash;
  const ulong p = 108877;
  ulong a;
  ulong b;

public:

  // Constructor
  HashTable();

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract binary tree is possible.
  virtual bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong) = 0; // Resize the hashtable to a given size

protected:

  // Auxiliary member functions

  virtual ulong HashKey(const ulong) const noexcept; // returns the index

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
