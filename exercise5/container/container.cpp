
namespace lasd {

/* ************************************************************************** */

// Specific member functions LinearContainer

template <typename Data>
inline Data& LinearContainer<Data>::Front() const {
  if(size != 0) {
    return operator[](0);
  }
  else {
    throw std::length_error("Error! Empty linear container");
  }
}

template <typename Data>
inline Data& LinearContainer<Data>::Back() const {
  if(size != 0) {
    return operator[](size-1);
  }
  else {
    throw std::length_error("Error! Empty linear container");
  }
}

/* ************************************************************************** */

// Specific member functions FoldableContainer

template <typename Data>
void AuxFoldExists(const Data& dat, const void* val, void* exists) noexcept {
  if (dat == *((Data*)val)) {
    *((bool*)exists) = true;
  }
}

template <typename Data>
inline bool FoldableContainer<Data>::Exists(const Data& dat) const noexcept {
  bool exists = false;
  Fold(&AuxFoldExists<Data>, &dat, &exists);
  return exists;
}

/* ************************************************************************** */

// Specific member functions PreOrderMappableContainer

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void* par) {
  MapPreOrder(fun, par);
}

/* ************************************************************************** */

// Specific member functions PreOrderFoldableContainer

template <typename Data>
inline void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  FoldPreOrder(fun, par, acc);
}

/* ************************************************************************** */

// Specific member functions PostOrderMappableContainer

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFunctor fun, void* par) {
  MapPostOrder(fun, par);
}

/* ************************************************************************** */

// Specific member functions PostOrderFoldableContainer

template <typename Data>
inline void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  FoldPostOrder(fun, par, acc);
}

/* ************************************************************************** */

//Specific member functions (InOrderMappableContainer)

template <typename Data>
inline void InOrderMappableContainer<Data>::Map(MapFunctor fun, void* par){
  MapInOrder(fun,par);
}

/* ************************************************************************** */

//Specific member functions (InOrderFoldableContainer)

template <typename Data>
inline void InOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const{
  FoldInOrder(fun,par,acc);
}

/* ************************************************************************** */

//Specific member functions (BreadthMappableContainer)

template <typename Data>
inline void BreadthMappableContainer<Data>::Map(MapFunctor fun, void* par){
  MapBreadth(fun,par);
}

/* ************************************************************************** */

//Specific member functions (BreadthFoldableContainer)

template <typename Data>
inline void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const{
  FoldBreadth(fun,par,acc);
}

/* ************************************************************************** */

// Specific member functions (DictionaryContainer)

template <typename Data>
void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& lc) {
  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

template <typename Data>
void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& lc) noexcept {
  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

template <typename Data>
void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& lc) {
  for(ulong i = 0; i < lc.Size(); i++) {
    Remove(lc[i]);
  }
}

/* ************************************************************************** */

}
