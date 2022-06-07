
namespace lasd {

/* ************************************************************************** */

  // Copy assignment <Node>

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(const struct BinaryTreeVec<Data>::NodeVec& node) {
    value = node.value;
    index = node.index;
    nodeVec = node.nodeVec;
    return *this;
  }

  // Move assignment <Node>

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::operator=(struct BinaryTreeVec<Data>::NodeVec&& node) noexcept {
    std::swap(value, node.value);
    std::swap(index, node.index);
    std::swap(nodeVec, node.nodeVec);
    return *this;
  }

/* ************************************************************************** */

  // Specific member functions <Node>

  template <typename Data>
  Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return value;
  }

  template <typename Data>
  const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return value;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
    return !(HasLeftChild() || HasRightChild());
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return ((2 * index + 1) < nodeVec->Size());
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return ((2 * index + 2) < nodeVec->Size());
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if (HasLeftChild()) {
      return *((*nodeVec)[2 * index + 1]);
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if (HasRightChild()) {
      return *((*nodeVec)[2 * index + 2]);
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

/* ************************************************************************** */

  // Default constructor <BinaryTreeVec>
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec() {
    Vector<struct BinaryTreeVec<Data>::NodeVec*> vec = new Vector<struct BinaryTreeVec<Data>::NodeVec*>();
    size = 0;
  }

/* ************************************************************************** */

  // Specific constructors <BinaryTreeVec>

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& lc) {
    vec = Vector<BinaryTreeVec<Data>::NodeVec*>(lc.Size());

    for(ulong i = 0; i < lc.Size(); i++) {
      BinaryTreeVec<Data>::NodeVec* node = new BinaryTreeVec<Data>::NodeVec();
      node->nodeVec = &vec;
      node->index = i;
      node->value = lc[i];
      vec[i] = node;
    }

    size = lc.Size();
  }

/* ************************************************************************** */

  // Copy constructor <BinaryTreeVec>

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
    vec = btv.vec;
    size = btv.size;
  }

  // Move constructor <BinaryTreeVec>

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv) noexcept {
    std::swap(vec, btv.vec);
    std::swap(size, btv.size);
  }

/* ************************************************************************** */

  // Destructor <BinaryTreeVec>

  template <typename Data>
  BinaryTreeVec<Data>::~BinaryTreeVec() {
    Clear();
  }

/* ************************************************************************** */

  // Copy assignment <BinaryTreeVec>

  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& btv) {
    BinaryTreeVec<Data>* tempBtv = new BinaryTreeVec<Data>(btv);
    std::swap(*this, *tempBtv);
    delete tempBtv;
    return *this;
  }

  // Move assignment <BinaryTreeVec>

  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& btv) noexcept {
    std::swap(vec, btv.vec);
    std::swap(size, btv.size);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators <BinaryTreeVec>

  template <typename Data>
  bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& btv) const noexcept {
    return (vec == btv.vec);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& btv) const noexcept {
    return !(*this == btv);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from BinaryTree) <BinaryTreeVec>

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if (size > 0) {
      return *vec[0];
    }
    else {
      throw std::length_error("Error! Empty vector");
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Container) <BinaryTreeVec>

  template <typename Data>
  void BinaryTreeVec<Data>::Clear() {
    vec.Clear();
    size = 0;
  }

/* ************************************************************************** */

  // Specific member functions (inherited from BreadthMappableContainer) <BinaryTreeVec>

  template <typename Data>
  void BreadthMappableContainer<Data>::MapBreadth(const MapFunctor fun, void* par) {
    MapBreadth(fun, par);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from BreadthFoldableContainer) <BinaryTreeVec>

  template <typename Data>
  void BreadthFoldableContainer<Data>::FoldBreadth(FoldFunctor fun, const void* par, void* acc) const {
    FoldBreadth(fun, par, acc);
  }

/* ************************************************************************** */

}
