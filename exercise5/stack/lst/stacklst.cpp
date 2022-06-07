
namespace lasd {

/* ************************************************************************** */

  // Specific constructor
  template <typename Data>
  StackLst<Data>::StackLst(const LinearContainer<Data>& lc) {
    size = 0;
    for(int i = lc.Size() - 1; i >= 0; i--) {
      Push(lc[i]);
    }
  }

  /* ************************************************************************ */

  // Copy constructor
  template <typename Data>
  StackLst<Data>::StackLst(const StackLst<Data>& sl) {
    StackLst<Data> tempLst;
    struct List<Data>::Node* tempNode = sl.head;

    for (ulong i = 0; i < sl.size; i++) {
      tempLst.Push(tempNode->value);
      tempNode = tempNode->next;
    }

    tempNode = tempLst.head;

    for (ulong i = 0; i < sl.size; i++) {
      Push(tempNode->value);
      tempNode = tempNode->next;
    }
  }

  // Move constructor
  template <typename Data>
  StackLst<Data>::StackLst(StackLst<Data>&& sl) noexcept {
    std::swap(head, sl.head);
    std::swap(size, sl.size);
  }

  /* ************************************************************************ */

  // Destructor
  template <typename Data>
  StackLst<Data>::~StackLst() {
    List<Data>::Clear();
  }

  /* ************************************************************************ */

  // Copy assignment
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& sl) {
    StackLst<Data>* tempStackLst = new StackLst<Data>(sl);
    std::swap(*this, *tempStackLst);
    delete tempStackLst;
    return *this;
  }

  // Move assignment
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& sl) noexcept {
    std::swap(head, sl.head);
    std::swap(size, sl.size);
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  template <typename Data>
  bool StackLst<Data>::operator==(const StackLst<Data>& sl) const noexcept {
    return List<Data>::operator==(sl);
  }

  template <typename Data>
  bool StackLst<Data>::operator!=(const StackLst<Data>& sl) const noexcept {
    return !((*this) == sl);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  template <typename Data>
  Data& StackLst<Data>::Top() const {
    return List<Data>::Front();
  }

  template <typename Data>
  Data& StackLst<Data>::Top() {
    return List<Data>::Front();
  }

  template <typename Data>
  void StackLst<Data>::Pop() {
    List<Data>::RemoveFromFront();
  }


  template <typename Data>
  Data StackLst<Data>::TopNPop() {
    return List<Data>::FrontNRemove();
  }

  template <typename Data>
  void StackLst<Data>::Push(const Data& data) {
    List<Data>::InsertAtFront(data);
  }

  template <typename Data>
  void StackLst<Data>::Push(Data&& data) noexcept {
    List<Data>::InsertAtFront(data);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  template <typename Data>
  void StackLst<Data>::Clear() {
    while (size > 0) {
      Pop();
    }
  }

  /* ************************************************************************ */
}
