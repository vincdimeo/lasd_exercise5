
namespace lasd {

/* ************************************************************************** */

  // Specific constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const LinearContainer<Data>& lc) {
    size = 0;
    for(ulong i = 0; i < lc.Size(); i++) {
      Enqueue(lc[i]);
    }
  }

/* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const QueueLst<Data>& ql) {
    struct List<Data>::Node* tempNode = ql.head;
    for(ulong i = 0; i < ql.size; i++) {
      Enqueue(tempNode->value);
      tempNode = tempNode->next;
    }
    size = ql.size;
  }

  // Move constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(QueueLst<Data>&& ql) noexcept {
    std::swap(head, ql.head);
    std::swap(tail, ql.tail);
    std::swap(size, ql.size);
  }

/* ************************************************************************** */

  // Destructor
  template <typename Data>
  QueueLst<Data>::~QueueLst() {
    Clear();
  }

/* ************************************************************************** */

  // Copy assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& ql) {
    QueueLst<Data>* tempQlst = new QueueLst<Data>(ql);
    std::swap(*this, *tempQlst);
    delete tempQlst;
    return *this;
  }

  // Move assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& ql) noexcept {
    std::swap(head, ql.head);
    std::swap(tail, ql.tail);
    std::swap(size, ql.size);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators
  template <typename Data>
  bool QueueLst<Data>::operator==(const QueueLst<Data>& ql) const noexcept {
    return List<Data>::operator==(ql);
  }

  template <typename Data>
  bool QueueLst<Data>::operator!=(const QueueLst<Data>& ql) const noexcept {
    return !(*this == ql);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Queue)
  template <typename Data>
  Data& QueueLst<Data>::Head() const {
    return List<Data>::Front();
  }

  template <typename Data>
  Data& QueueLst<Data>::Head() {
    return List<Data>::Front();
  }

  template <typename Data>
  void QueueLst<Data>::Dequeue() {
    List<Data>::RemoveFromFront();
  }

  template <typename Data>
  Data QueueLst<Data>::HeadNDequeue() {
    return List<Data>::FrontNRemove();
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(const Data& data) {
    List<Data>::InsertAtBack(data);
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(Data&& data) noexcept {
    List<Data>::InsertAtBack(data);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Container)
  template <typename Data>
  void QueueLst<Data>::Clear() {
    while (size > 0) {
      Dequeue();
    }
  }

/* ************************************************************************** */

}
