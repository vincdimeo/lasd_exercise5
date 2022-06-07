
namespace lasd {

/* ************************************************************************** */

// Specific constructors

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& lc) {
  for(ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

/* ************************************************************************** */

// Copy constructor

template <typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>(bst) {}

// Move constructor

template <typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

// Move assignment

template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
inline bool BST<Data>::operator==(const BST<Data>& bst) const noexcept {
  if (bst.Size() != size) {
    return false;
  }
  else {
    BTInOrderIterator<Data> itThis(*this);
    BTInOrderIterator<Data> itBst(bst);

    while (!itThis.Terminated()) {
      if (*itThis != *itBst) {
        return false;
      }
      ++itThis;
      ++itBst;
    }
    return true;
  }
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept {
  return !(*this == bst);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
const Data& BST<Data>::Min() const {
  if (head != nullptr) {
    return FindPointerToMin(head)->value;
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
Data BST<Data>::MinNRemove() {
  if (head != nullptr) {
    return DataNDelete(DetachMin(head));
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
void BST<Data>::RemoveMin() {
  if (head != nullptr) {
    delete DetachMin(head);
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
const Data& BST<Data>::Max() const {
  if (head != nullptr) {
    return FindPointerToMax(head)->value;
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
  if (head != nullptr) {
    return DataNDelete(DetachMax(head));
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
void BST<Data>::RemoveMax() {
  if (head != nullptr) {
    delete DetachMax(head);
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& data) const {
  if (head != nullptr) {
    BST<Data>::NodeLnk* const& predNode = FindPointerToPredecessor(head, data);
    return (*predNode).value;
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& data) {
  if (head != nullptr) {
    BST<Data>::NodeLnk*& predNode = FindPointerToPredecessor(head, data);
    return DataNDelete(Detach(predNode));
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& data) {
  if (head != nullptr) {
    BST<Data>::NodeLnk*& predNode = FindPointerToPredecessor(head, data);
    delete Detach(predNode);
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& data) const {
  if (head != nullptr) {
    BST<Data>::NodeLnk* const& succNode = FindPointerToSuccessor(head, data);
    return (*succNode).value;
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& data) {
  if (head != nullptr) {
    BST<Data>::NodeLnk*& succNode = FindPointerToSuccessor(head, data);
    return DataNDelete(Detach(succNode));
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& data) {
  if (head != nullptr) {
    BST<Data>::NodeLnk*& succNode = FindPointerToSuccessor(head, data);
    delete Detach(succNode);
  }
  else {
    throw std::length_error("Error! Empty tree");
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
void BST<Data>::Insert(const Data& data) {
  BST<Data>::NodeLnk*& nodeLnk = FindPointerTo(head, data);

  if (nodeLnk == nullptr) {
    nodeLnk = new NodeLnk(data);
    size++;
  }
}

template <typename Data>
void BST<Data>::Insert(Data&& data) noexcept {
  Insert(std::move(data));
}

template <typename Data>
void BST<Data>::Remove(const Data& data) {
  if (Exists(data)) {
    delete Detach(FindPointerTo(head, data));
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from TestableContainer)

template <typename Data>
bool BST<Data>::Exists(const Data& data) const noexcept {
  return (FindPointerTo(head, data) != nullptr);
}

/* ************************************************************************** */

// Auxiliary member functions

template <typename Data>
Data BST<Data>::DataNDelete(NodeLnk* node) {
  Data data {};
  std::swap(data, node->value);
  delete node;
  return data;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& node) noexcept {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->leftNode == nullptr) {
    return Skip2Right(node);
  }
  else if (node->rightNode == nullptr) {
    return Skip2Left(node);
  }

  NodeLnk* maxNode = DetachMax(node->leftNode);
  std::swap(node->value, maxNode->value);
  return maxNode;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept {
  return Skip2Right(FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& node) noexcept {
  return Skip2Left(FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& node) noexcept {
  NodeLnk* left = nullptr;
  if (node != nullptr) {
    std::swap(left, node->leftNode);
    std::swap(left, node);
    size--;
  }

  return left;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& node) noexcept {
  NodeLnk* right = nullptr;
  if (node != nullptr) {
    std::swap(right, node->rightNode);
    std::swap(right, node);
    size--;
  }

  return right;
}

template <typename Data>
inline typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(BST<Data>::NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(BST<Data>::NodeLnk* const& node) const noexcept {
  NodeLnk* const* ptr = &node;
  NodeLnk* curr = node;

  if (curr != nullptr) {
    while (curr->leftNode != nullptr) {
      ptr = &curr->leftNode;
      curr = curr->leftNode;
    }
  }

  return *ptr;
}

template <typename Data>
inline typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(BST<Data>::NodeLnk*& node) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(BST<Data>::NodeLnk* const& node) const noexcept {
  NodeLnk* const* ptr = &node;
  NodeLnk* curr = node;

  if (curr != nullptr) {
    while (curr->rightNode != nullptr) {
      ptr = &curr->rightNode;
      curr = curr->rightNode;
    }
  }

  return *ptr;
}

template <typename Data>
inline typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, const Data& data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, data));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, const Data& data) const noexcept {
  NodeLnk* const* ptr = &node;
  NodeLnk* curr = node;

  while (curr != nullptr) {
    if (curr->value < data) {
      ptr = &curr->rightNode;
      curr = curr->rightNode;
    }
    else if (curr->value > data) {
      ptr = &curr->leftNode;
      curr = curr->leftNode;
    }
    else {
      break;
    }
  }

  return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& node, const Data& data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, data));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, const Data& data) const noexcept {
  NodeLnk* const* curr = &node;
  NodeLnk* const* ptr = nullptr;

  while ((*curr) != nullptr && (*curr)->value != data) {
    if ((*curr)->value < data) {
      ptr = curr;
      curr = &(*curr)->rightNode;
    }
    else {
      curr = &(*curr)->leftNode;
    }
  }

  if ((*curr) != nullptr && (*curr)->leftNode != nullptr) {
      ptr = &FindPointerToMax((*curr)->leftNode);
  }

  return *ptr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& node, const Data& data) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, data));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, const Data& data) const noexcept {
  NodeLnk* const* curr = &node;
  NodeLnk* const* ptr = nullptr;

  while ((*curr) != nullptr && (*curr)->value != data) {
    if ((*curr)->value < data) {
      curr = &(*curr)->rightNode;
    }
    else {
      ptr = curr;
      curr = &(*curr)->leftNode;
    }
  }

  if ((*curr) != nullptr && (*curr)->rightNode != nullptr) {
    ptr = &FindPointerToMin((*curr)->rightNode);
  }

  return *ptr;
}

/* ************************************************************************** */

}
