
namespace lasd {

/* ************************************************************************** */

  // Specific constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const LinearContainer<Data>& lc) {
    size = lc.Size();
    Elements = new Data[size];

    while (fPos < size) {
      Elements[fPos] = lc[fPos];
      fPos++;
    }
  }

/* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& qv) {
    if (qv.size != 0) {
      iPos = qv.iPos;
      fPos = qv.iPos;

      if (qv.fPos < qv.iPos) {
        for(ulong i = qv.iPos; i < qv.size; i++) {
          Enqueue(qv[i]);
        }

        for(ulong i = 0; i < qv.fPos; i++) {
          Enqueue(qv[i]);
        }
      }
      else {
        for(ulong i = qv.iPos; i < qv.fPos; i++) {
          Enqueue(qv[i]);
        }
      }
    }
  }

  /* ************************************************************************ */

  // Move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& qv) noexcept {
    std::swap(Elements, qv.Elements);
    std::swap(size, qv.size);
    std::swap(iPos, qv.iPos);
    std::swap(fPos, qv.fPos);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  QueueVec<Data>::~QueueVec() {
    Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qv) {
    QueueVec<Data>* tempQvec = new QueueVec<Data>(qv);
    std::swap(*tempQvec, *this);
    return *this;
  }

  // Move assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qv) noexcept {
    std::swap(Elements, qv.Elements);
    std::swap(size, qv.size);
    std::swap(iPos, qv.iPos);
    std::swap(fPos, qv.fPos);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& qv) const noexcept {
    if ((Size() == qv.Size()) && (iPos == qv.iPos) && (fPos == qv.fPos)) {
      for(ulong i = iPos; i != fPos; i++) {
        if (Elements[i] != qv.Elements[i]) {
          return false;
        }

        if (i == size - 1) {
          i = 0;
        }
      }
      return true;
    }
    else {
      return false;
    }
  }

  template <typename Data>
  bool QueueVec<Data>::operator!=(const QueueVec<Data>& qv) const noexcept {
    return !(*this == qv);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)
  template <typename Data>
  Data& QueueVec<Data>::Head() const {
    if (!Empty()) {
      return Elements[iPos];
    }
    else {
      throw std::length_error("Error! Empty QueueVec");
    }
  }

  template <typename Data>
  Data& QueueVec<Data>::Head() {
    if (!Empty()) {
      return Elements[iPos];
    }
    else {
      throw std::length_error("Error! Empty QueueVec");
    }
  }

  template <typename Data>
  void QueueVec<Data>::Dequeue() {
    if (!Empty()) {
      if (iPos == (size - 1)) {
        iPos = 0;
      }
      else {
        iPos++;
      }
      Reduce();
    }
    else {
      throw std::length_error("Error! Empty QueueVec");
    }
  }

  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue() {
    if (!Empty()) {
      Data temp = Elements[iPos];
      if (iPos == (size - 1)) {
        iPos = 0;
      }
      else {
        iPos++;
      }
      Reduce();
      return temp;
    }
    else {
      throw std::length_error("Error! Empty QueueVec");
    }
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& data) {
    if (size == 0) {
      size = 2;
      Elements = new Data[size];
      Elements[iPos] = data;
    }
    else {
      Elements[fPos] = data;
    }

    if (fPos == (size - 1)) {
      fPos = 0;
    }
    else {
      fPos++;
    }

    Expand();
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& data) noexcept {
    if (size == 0) {
      size = 2;
      Elements = new Data[size];
      Elements[iPos] = std::move(data);
    }
    else {
      Elements[fPos] = std::move(data);
    }

    if (fPos == (size - 1)) {
      fPos = 0;
    }
    else {
      fPos++;
    }

    Expand();
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  template <typename Data>
  bool QueueVec<Data>::Empty() const noexcept {
    return (Size() == 0);
  }

  template <typename Data>
  ulong QueueVec<Data>::Size() const noexcept {
    if (fPos < iPos) {
      return (size - (iPos - fPos));
    }
    else {
      return (fPos - iPos);
    }
  }

  template <typename Data>
  void QueueVec<Data>::Clear() {
    Vector<Data>::Clear();
    iPos = 0;
    fPos = 0;
  }

  /* ************************************************************************ */

  // Auxiliary member functions
  template <typename Data>
  void QueueVec<Data>::Expand() {
    const ulong newsize = size * 2;
    Vector<Data>::Resize(newsize);
    SwapVectors(newsize);
  }

  template <typename Data>
  void QueueVec<Data>::Reduce() {
    const ulong newsize = size - (size / 4);
    Vector<Data>::Resize(newsize);
    SwapVectors(newsize);
  }

  template <typename Data>
  void QueueVec<Data>::SwapVectors(ulong nsize) {
    Data* tempElements = new Data[nsize] {};
    ulong j = 0;

    if (fPos < iPos) {
      for(ulong i = iPos; i < size; i++) {
        std::swap(Elements[i], tempElements[j]);
        j++;
      }

      for(ulong i = 0; i < fPos; i++) {
        std::swap(Elements[i], tempElements[j]);
        j++;
      }
    }
    else {
      for(ulong i = iPos; i < fPos; i++) {
        std::swap(Elements[i], tempElements[j]);
        j++;
      }

      std::swap(Elements, tempElements);
      size = nsize;
      fPos = fPos - iPos;
      iPos = 0;
      delete[] tempElements;
    }
  }

  /* ************************************************************************ */

}
