
namespace lasd {

/* ************************************************************************** */

  // Constructor
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& data) {
    value = data;
    leftNode = nullptr;
    rightNode = nullptr;
  }

/* ************************************************************************** */

  // Destructor
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
    delete leftNode;
    delete rightNode;
  }

/* ************************************************************************** */

  // Copy assignment
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const struct BinaryTreeLnk<Data>::NodeLnk& node) {
    NodeLnk* newNode = new NodeLnk(node);
    std::swap(*this, *newNode);
    return *this;
  }

  // Move assignment
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(struct BinaryTreeLnk<Data>::NodeLnk&& node) noexcept {
    std::swap(value, node.value);
    std::swap(leftNode, node.leftNode);
    std::swap(rightNode, node.rightNode);
    return *this;
  }

/* ************************************************************************** */

  // Specific constructors
  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const LinearContainer<Data>& lc, ulong i) {
    value = lc[i];

    if ((2 * i + 1) < lc.Size()) {
      leftNode = new NodeLnk(lc, (2 * i + 1));
    }

    if ((2 * i + 2) < lc.Size()) {
      rightNode = new NodeLnk(lc, (2 * i + 2));
    }
  }

/* ************************************************************************** */

  // Specific member functions

  template <typename Data>
  Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return value;
  }

  template <typename Data>
  const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return value;
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {
    return !(HasLeftChild() || HasRightChild());
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return (leftNode != nullptr);
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return (rightNode != nullptr);
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    if (leftNode != nullptr) {
      return *leftNode;
    }
    else {
      throw std::length_error("Error! Out of range");
    }
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    if (rightNode != nullptr) {
      return *rightNode;
    }
    else {
      throw std::length_error("Error! Out of range");
    }
  }

/* ************************************************************************** */

  // Default constructor <BinaryTreeLnk>
  // template <typename Data>
  // BinaryTreeLnk<Data>::BinaryTreeLnk() {
  //   size = 0;
  //   head = new struct BinaryTreeLnk<Data>::NodeLnk();
  // }

/* ************************************************************************** */

  // Specific constructor <BinaryTreeLnk>
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& lc) {
    if (lc.Size() > 0) {
      head = new NodeLnk(lc, 0);
      size = lc.Size();
    }
  }

/* ************************************************************************** */

  // Copy constructor <BinaryTreeLnk>
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& btl) {
    if (btl.size > 0) {
      head = &btl.Root();
      size = btl.size;
    }
  }

  // Move constructor <BinaryTreeLnk>
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& btl) noexcept {
    std::swap(head, btl.head);
    std::swap(size, btl.size);
  }

/* ************************************************************************** */

  // Destructor <BinaryTreeLnk>
  template <typename Data>
  BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    Clear();
  }

/* ************************************************************************** */

  // Copy assignment <BinaryTreeLnk>
  template <typename Data>
  BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& btl) {
    BinaryTreeLnk<Data>* tempBtl = new BinaryTreeLnk<Data>(btl);
    std::swap(*this, *tempBtl);
    delete tempBtl;
    return *this;
  }

  // Move assignment <BinaryTreeLnk>
  template <typename Data>
  BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& btl) noexcept {
    std::swap(head, btl.head);
    std::swap(size, btl.size);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators <BinaryTreeLnk>

  template <typename Data>
  bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& btl) const noexcept {
    return (head == btl.head);
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& btl) const noexcept {
    return !(*this == btl);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from BinaryTree) <BinaryTreeLnk>

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    if (size > 0) {
      return *head;
    }
    else {
      throw std::length_error("Error! Empty BinaryTreeLnk");
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Container) <BinaryTreeLnk>

  template <typename Data>
  void BinaryTreeLnk<Data>::Clear() {
    delete head;
    head = nullptr;
    size = 0;
  }

/* ************************************************************************** */

}
