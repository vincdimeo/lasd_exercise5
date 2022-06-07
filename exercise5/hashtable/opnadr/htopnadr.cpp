
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newsize) {
  sizeHT = newsize;
  table.Resize(sizeHT);
  controllerTable.Resize(sizeHT);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& lc) {
  table.Resize(lc.Size());
  controllerTable.Resize(lc.Size());

  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newsize, const LinearContainer<Data>& lc) {
  sizeHT = newsize;
  table.Resize(sizeHT);
  controllerTable.Resize(sizeHT);

  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& htOpnAdr) {
  table = htOpnAdr.table;
  controllerTable = htOpnAdr.controllerTable;
  size = htOpnAdr.size;
  sizeHT = htOpnAdr.sizeHT;
  a = htOpnAdr.a;
  b = htOpnAdr.b;
}

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& htOpnAdr) noexcept {
  std::swap(table, htOpnAdr.table);
  std::swap(controllerTable, htOpnAdr.controllerTable);
  std::swap(size, htOpnAdr.size);
  std::swap(sizeHT, htOpnAdr.sizeHT);
  std::swap(a, htOpnAdr.a);
  std::swap(b, htOpnAdr.b);
}

/* ************************************************************************** */

// Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& htOpnAdr) {
  table = htOpnAdr.table;
  controllerTable = htOpnAdr.controllerTable;
  size = htOpnAdr.size;
  sizeHT = htOpnAdr.sizeHT;
  a = htOpnAdr.a;
  b = htOpnAdr.b;
  return *this;
}

// Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& htOpnAdr) noexcept {
  std::swap(table, htOpnAdr.table);
  std::swap(controllerTable, htOpnAdr.controllerTable);
  std::swap(size, htOpnAdr.size);
  std::swap(sizeHT, htOpnAdr.sizeHT);
  std::swap(a, htOpnAdr.a);
  std::swap(b, htOpnAdr.b);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& htOpnAdr) const noexcept {
  if ((size == 0) && (htOpnAdr.size == 0)) {
    return true;
  }

  if (size == htOpnAdr.size) {
    for(ulong i = 0; i < size; i++) {
      if ((int)controllerTable[i] == 1) {
        if (!(htOpnAdr.Exists(table[i]))) {
          return false;
        }
      }
    }
    return true;
  }

  return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& htOpnAdr) const noexcept {
  return !(*this == htOpnAdr);
}

/* ************************************************************************** */

// Specific member functions (inherited from HashTable)

template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong nsize) {
  HashTableOpnAdr<Data> ht(nsize);

  for(ulong i = 0; i < sizeHT; i++) {
    if ((int)controllerTable[i] == 1) {
      ht.Insert(table[i]);
    }
  }

  *this = std::move(ht);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
void HashTableOpnAdr<Data>::Insert(const Data& data) {
  ulong index = FindEmpty(data);

  if (index < sizeHT) {
    table[index] = data;
    controllerTable[index] = (char)1;
    size++;
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Insert(Data&& data) noexcept {
  ulong index = FindEmpty(data);

  if (index < sizeHT) {
    table[index] = std::move(data);
    controllerTable[index] = (char)1;
    size++;
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Remove(const Data& data) {
  ulong index = Find(data);

  if (index != sizeHT) {
    controllerTable[index] = (char)2;
    size--;
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept {
  if (size == 0) {
    return false;
  }

  ulong index = Find(data);

  return (index != sizeHT);
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor fun, void* par) {
  for(ulong i = 0; i < size; i++) {
    if ((int)controllerTable[i] == 1) {
      table.MapPreOrder(fun, par);
    }
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  for(ulong i = 0; i < size; i++) {
    if ((int)controllerTable[i] == 1) {
      table.FoldPreOrder(fun, par, acc);
    }
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
  table.Clear();
  controllerTable.Clear();
  size = 0;
  sizeHT = 256;
  table.Resize(sizeHT);
  controllerTable.Resize(sizeHT);
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data& data) const noexcept {
  ulong base = HashKey(hash(data));
  ulong tempIndex = base;

  bool test = controllerTable[tempIndex] == 1 && table[tempIndex] == data;
  if (test) {
    return tempIndex;
  }
  else {
    for(ulong i = 1; (int)controllerTable[tempIndex] != 0 && !test; i++) {
      tempIndex = (base + ProbFun(i)) % sizeHT;
      test = controllerTable[tempIndex] == 1 && table[tempIndex] == data;
    }

    if (test) {
      return tempIndex;
    }
    else {
      return sizeHT; // valore gia presente
    }
  }
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data data) noexcept {
  if (size >= (sizeHT / 2)) {
    Resize(sizeHT * 2);
  }

  ulong base = HashKey(hash(data));
  ulong tempIndex = base;

  if ((int)controllerTable[tempIndex] == 0) {
    return tempIndex;
  }
  else {
    bool test = controllerTable[tempIndex] == 1 && table[tempIndex] == data;

    for(ulong i = 1; (int)controllerTable[tempIndex] != 0 && !test; i++) {
      tempIndex = (base + ProbFun(i)) % sizeHT;
      test = controllerTable[tempIndex] == 1 && table[tempIndex] == data;
    }

    if (test) {
      return sizeHT; // valore gia presente
    }
    else {
      return tempIndex;
    }
  }
}

/* ************************************************************************** */
}
