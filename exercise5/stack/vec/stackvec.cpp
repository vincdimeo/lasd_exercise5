
namespace lasd {

/* ************************************************************************** */

  // Specific constructor
  template <typename Data>
  StackVec<Data>::StackVec(const LinearContainer<Data>& lc) {
    numElements = lc.Size();
    size = numElements * 2;
    Elements = new Data[size];

    for(ulong i = 0; i < numElements; i++) {
      Elements[i] = lc[i];
    }
  }

/* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  StackVec<Data>::StackVec(const StackVec<Data>& sv) {
    Elements = new Data[sv.size];
    std::copy(sv.Elements, sv.Elements + sv.numElements, Elements);
    size = sv.size;
    numElements = sv.numElements;
  }

  // Move constructor
  template <typename Data>
  StackVec<Data>::StackVec(StackVec<Data>&& sv) noexcept {
    std::swap(Elements, sv.Elements);
    std::swap(size, sv.size);
    std::swap(numElements, sv.numElements);
  }

/* ************************************************************************** */

  // Destructor
  template <typename Data>
  StackVec<Data>::~StackVec() {
    Clear();
  }

/* ************************************************************************** */

  // Copy assignment
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& sv) {
    StackVec<Data>* tempStackVec = new StackVec<Data>(sv);
    std::swap(*tempStackVec, *this);
    delete tempStackVec;
    return *this;
  }

  // Move assignment
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& sv) noexcept {
    std::swap(Elements, sv.Elements);
    std::swap(size, sv.size);
    std::swap(numElements, sv.numElements);
    return *this;
  }

/* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool StackVec<Data>::operator==(const StackVec<Data>& sv) const noexcept {
    if (numElements == sv.numElements) {
      for (ulong i = 0; i < numElements; i++) {
        if (Elements[i] != sv.Elements[i]) {
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
  bool StackVec<Data>::operator!=(const StackVec<Data>& sv) const noexcept {
    return !(*this == sv);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  template <typename Data>
  Data& StackVec<Data>::Top() const {
    if (size != 0) {
      return Elements[numElements - 1];
    }
    else {
      throw std::length_error("Error! Empty StackVec");
    }
  }

  template <typename Data>
  Data& StackVec<Data>::Top() {
    if (size != 0) {
      return Elements[numElements - 1];
    }
    else {
      throw std::length_error("Error! Empty StackVec");
    }
  }

  template <typename Data>
  void StackVec<Data>::Pop() {
    if (size != 0) {
      numElements--;
      if (numElements == 0) {
        Clear();
      }
      else {
        Reduce();
      }
    }
    else {
      throw std::length_error("Error! Empty StackVec");
    }
  }

  template <typename Data>
  Data StackVec<Data>::TopNPop() {
    if (size != 0) {
      Data topValue = Elements[numElements - 1];
      Pop();
      return topValue;
    }
    else {
      throw std::length_error("Error! Empty StackVec");
    }
  }

  template <typename Data>
  void StackVec<Data>::Push(const Data& data) {
    if (size == 0) {
      size = 3;
      Elements = new Data[size]; // verificare che funziona, altrimenti usare else
    }
    Elements[numElements] = data;
    numElements++;
    Expand();
  }

  template <typename Data>
  void StackVec<Data>::Push(Data&& data) noexcept {
    if (size == 0) {
      size = 3;
      Elements = new Data[size]; // verificare che funziona, altrimenti usare else
    }
    Elements[numElements] = std::move(data);
    numElements++;
    Expand();
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  template <typename Data>
  bool StackVec<Data>::Empty() const noexcept {
    return (numElements == 0);
  }

  template <typename Data>
  ulong StackVec<Data>::Size() const noexcept {
    return numElements;
  }

  template <typename Data>
  void StackVec<Data>::Clear() {
    numElements = 0;
    Vector<Data>::Clear();
  }


  /* ************************************************************************ */

  // Auxiliary member functions

  template <typename Data>
  void StackVec<Data>::Expand() {
    if ((numElements > 0) && ((size - numElements) <= 2)) {
      Vector<Data>::Resize(size * 2);
    }
  }

  template <typename Data> // da modificare
  void StackVec<Data>::Reduce() {
    if ((numElements > 0) && ((size - numElements) >= 4)) {
      Vector<Data>::Resize(size - 2);
    }
  }

}
