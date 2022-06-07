
namespace lasd {

/* ************************************************************************** */

// Specific constructor

template <typename Data>
Vector<Data>::Vector(const ulong nsize) {
  Elements = new Data[nsize]{};
  size = nsize;
}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& lc) {
  size = lc.Size();
  Elements = new Data[size]{};

  for(ulong i = 0; i < size; i++) {
    Elements[i] = lc[i];
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vc) {
  Elements = new Data[vc.size]{};
  std::copy(vc.Elements, vc.Elements + vc.size, Elements);
  size = vc.size;
}

/* ************************************************************************** */

// Move constructor

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& vc) noexcept {
  std::swap(Elements, vc.Elements);
  std::swap(size, vc.size);
}

/* ************************************************************************** */

// Destructor

template <typename Data>
Vector<Data>::~Vector() {
  delete[] Elements;
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vc) {
  Vector<Data>* tmp = new Vector<Data>(vc);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

/* ************************************************************************** */

// Move assignment

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vc) noexcept {
  std::swap(Elements, vc.Elements);
  std::swap(size, vc.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool Vector<Data>::operator==(const Vector& vc) const noexcept {
  if (size == vc.size) {
    for(ulong i; i < size; i++) {
      if (Elements[i] != vc.Elements[i]) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector& vc) const noexcept {
  return !(*this == vc);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
void Vector<Data>::Resize(const ulong nsize) {
  if (nsize == 0) {
    Clear();
  }
  else if (nsize != size) {
    ulong limit = (size < nsize) ? size : nsize;
    Data* tmp = new Data[nsize]{};

    for(ulong i = 0; i < limit; i++) {
      std::swap(Elements[i], tmp[i]);
    }

    std::swap(Elements, tmp);
    size = nsize;
    delete[] tmp;
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)
template <typename Data>
void Vector<Data>::Clear() {
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
Data& Vector<Data>::Front() const {
  if (size != 0) {
    return Elements[0];
  }
  else {
    throw std::length_error("Error! Empty vector");
  }
}

template <typename Data>
Data& Vector<Data>::Back() const {
  if (size != 0) {
    return Elements[size - 1];
  }
  else {
    throw std::length_error("Error! Empty vector");
  }
}

template <typename Data>
Data& Vector<Data>::operator[](const ulong i) const {
  if (i < size) {
    return Elements[i];
  }
  else {
    throw std::out_of_range("Error! Index greater than size");
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)

template <typename Data>
inline void Vector<Data>::Map(MapFunctor fun, void* par) {
  MapPreOrder(fun, par);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer)

template <typename Data>
void Vector<Data>::MapPreOrder(MapFunctor fun, void* par) {
  for(ulong i = 0; i < size; i++) {
    fun(Elements[i], par);
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)

template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor fun, void* par){
  ulong i = size;
  while(i > 0) {
    fun(Elements[--i], par);
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)

template <typename Data>
inline void Vector<Data>::Fold(FoldFunctor fun, const void* val, void* acc) const {
  FoldPreOrder(fun, val, acc);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer)

template <typename Data>
inline void Vector<Data>::FoldPreOrder(FoldFunctor fun, const void* val, void* acc) const {
  for (ulong i = 0; i < size; i++) {
    fun(Elements[i], val, acc);
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)

template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor fun, const void* val, void* acc) const{
  ulong i = size;
  while(i > 0) {
    fun(Elements[--i], val, acc);
  }
}
}
