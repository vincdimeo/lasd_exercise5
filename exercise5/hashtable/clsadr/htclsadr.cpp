
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newsize) {
  sizeHT = newsize;
  table.Resize(sizeHT);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& lc) {
  table.Resize(lc.Size());

  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newsize, const LinearContainer<Data>& lc) {
  sizeHT = newsize;
  table.Resize(sizeHT);

  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& htClsAdr) {
  table = htClsAdr.table;
  size = htClsAdr.size;
  sizeHT = htClsAdr.sizeHT;
  a = htClsAdr.a;
  b = htClsAdr.b;
}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& htClsAdr) noexcept {
  std::swap(table, htClsAdr.table);
  std::swap(size, htClsAdr.size);
  std::swap(sizeHT, htClsAdr.sizeHT);
  std::swap(a, htClsAdr.a);
  std::swap(b, htClsAdr.b);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& htClsAdr) {
  table = htClsAdr.table;
  size = htClsAdr.size;
  sizeHT = htClsAdr.sizeHT;
  a = htClsAdr.a;
  b = htClsAdr.b;
  return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& htClsAdr) noexcept {
  std::swap(table, htClsAdr.table);
  std::swap(size, htClsAdr.size);
  std::swap(sizeHT, htClsAdr.sizeHT);
  std::swap(a, htClsAdr.a);
  std::swap(b, htClsAdr.b);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& htClsAdr) const noexcept {
  if ((size == 0) && (htClsAdr.size == 0)) {
    return true;
  }

  if(size == htClsAdr.size) {
    for(ulong i = 0; i < size; i++) {
      BTInOrderIterator<Data> itThis(table[i]);
      while (!itThis.Terminated()) {
        if (!(htClsAdr.Exists(*itThis))) {
          return false;
        }
        ++itThis;
      }
      return true;
    }
  }

  return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& htClsAdr) const noexcept {
  return !(*this == htClsAdr);
}

/* ************************************************************************** */

// Specific member functions (inherited from HashTable)

template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong nsize) {
  HashTableClsAdr<Data> ht(nsize);

  for(ulong i = 0; i < size; i++) {
    BTInOrderIterator<Data> itThis(table[i]);
    while (!itThis.Terminated()) {
      ht.Insert(*itThis);
      ++itThis;
    }
  }

  *this = std::move(ht);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
void HashTableClsAdr<Data>::Insert(const Data& data) {
  ulong key = hash(data);

  if (!table[HashKey(key)].Exists(data)) {
    table[HashKey(key)].Insert(data);
    size++;
  }
}

template <typename Data>
void HashTableClsAdr<Data>::Insert(Data&& data) noexcept {
  ulong key = hash(data);

  if (!table[HashKey(key)].Exists(data)) {
    table[HashKey(key)].Insert(std::move(data));
    size++;
  }
}

template <typename Data>
void HashTableClsAdr<Data>::Remove(const Data& data) {
  ulong key = hash(data);
  table[HashKey(key)].Remove(data);
  size--;
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept {
  if (size == 0) {
    return false;
  }

  ulong key = hash(data);

  return table[HashKey(key)].Exists(data);
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void HashTableClsAdr<Data>::Map(MapFunctor fun, void* par) {
  for(ulong i = 0; i < sizeHT; i++) {
    table[i].MapPreOrder(fun, par);
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void HashTableClsAdr<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  for(ulong i = 0; i < sizeHT; i++) {
    table[i].FoldPreOrder(fun, par, acc);
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void HashTableClsAdr<Data>::Clear() {
  table.Clear();
  sizeHT = 256;
  size = 0;
  table.Resize(sizeHT);
}

/* ************************************************************************** */
}
