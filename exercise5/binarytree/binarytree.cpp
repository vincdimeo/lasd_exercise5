
#include "../queue/lst/queuelst.hpp"
#include "../stack/lst/stacklst.hpp"

namespace lasd {

/* ************************************************************************** */

  // Comparison operators <Node>

  template <typename Data>
  bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept {
    if (Element() != node.Element()) {
      return false;
    }
    if ((HasLeftChild() && !node.HasLeftChild()) || (!HasLeftChild() && node.HasLeftChild())) {
      return false;
    }

    if ((HasRightChild() && !node.HasRightChild()) || (!HasRightChild() && node.HasRightChild())) {
      return false;
    }

    if (IsLeaf() && node.IsLeaf()) {
      return true;
    }

    if (HasLeftChild()) {
      if (LeftChild() != node.LeftChild()) {
        return false;
      }
    }

    if (HasRightChild()) {
      if (RightChild() != node.RightChild()) {
        return false;
      }
    }

    return true;
  }

  template <typename Data>
  bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept {
    return !(*this == node);
  }

/* ************************************************************************** */

  // Comparison operators <BinaryTree>

  template <typename Data>
  bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {
    if (size == 0 && bt.size == 0) {
      return true;
    }

    if (size != bt.size) {
      return false;
    }

    if (Root() != bt.Root()) {
      return false;
    }

    return true;
  }

  template <typename Data>
  bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const noexcept {
    return !(*this == bt);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from MappableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::Map(MapFunctor fun, void* par) {
    MapPreOrder(fun, par);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from FoldableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
    FoldPreOrder(fun, par, acc);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from PreOrderMappableContainer)

  template <typename Data>
  void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par) {
    if (size > 0) {
      MapPreOrder(fun, par, Root());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from PreOrderFoldableContainer)

  template <typename Data>
  void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
    if (size > 0) {
      FoldPreOrder(fun, par, acc, Root());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from PostOrderMappableContainer)

  template <typename Data>
  void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par) {
    if (size > 0) {
      MapPostOrder(fun, par, Root());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from PostOrderFoldableContainer)

  template <typename Data>
  void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
    if (size > 0) {
      FoldPostOrder(fun, par, acc, Root());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from InOrderMappableContainer)

  template <typename Data>
  void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par) {
    if (size > 0) {
      MapInOrder(fun, par, Root());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from InOrderFoldableContainer)

  template <typename Data>
  void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const {
    if (size > 0) {
      FoldInOrder(fun, par, acc, Root());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from BreadthMappableContainer)

  template <typename Data>
  void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par) {
    if (size != 0) {
      BinaryTree<Data>::Node* tempNode;
      QueueLst<Node*> ql = QueueLst<Node*>();

      ql.Enqueue(&Root());

      do {
        tempNode = ql.HeadNDequeue();
        fun(tempNode->Element(), par);

        if (tempNode->HasLeftChild()) {
          ql.Enqueue(&tempNode->LeftChild());
        }

        if (tempNode->HasRightChild()) {
          ql.Enqueue(&tempNode->RightChild());
        }
      } while(!ql.Empty());
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from BreadthFoldableContainer)

  template <typename Data>
  void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const {
    if (size != 0) {
      BinaryTree<Data>::Node* tempNode;
      QueueLst<Node*> ql = QueueLst<Node*>();

      ql.Enqueue(&Root());

      do {
        tempNode = ql.HeadNDequeue();
        fun(tempNode->Element(), par, acc);

        if (tempNode->HasLeftChild()) {
          ql.Enqueue(&tempNode->LeftChild());
        }

        if (tempNode->HasRightChild()) {
          ql.Enqueue(&tempNode->RightChild());
        }
      } while(!ql.Empty());
    }
  }

/* ************************************************************************** */

  // Auxiliary member functions (for PreOrderMappableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::MapPreOrder(MapFunctor fun, void* par, Node& node) {
    fun(node.Element(), par);

    if (node.HasLeftChild()) {
      MapPreOrder(fun, par, node.LeftChild());
    }

    if (node.HasRightChild()) {
      MapPreOrder(fun, par, node.RightChild());
    }
  }

/* ************************************************************************** */

  // Auxiliary member functions (for PreOrderFoldableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node& node) const {
    fun(node.Element(), par, acc);

    if (node.HasLeftChild()) {
      FoldPreOrder(fun, par, acc, node.LeftChild());
    }

    if (node.HasRightChild()) {
      FoldPreOrder(fun, par, acc, node.RightChild());
    }
  }

/* ************************************************************************** */

  // Auxiliary member functions (for PostOrderMappableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::MapPostOrder(MapFunctor fun, void* par, Node& node) {

    if (node.HasLeftChild()) {
      MapPostOrder(fun, par, node.LeftChild());
    }

    if (node.HasRightChild()) {
      MapPostOrder(fun, par, node.RightChild());
    }

    fun(node.Element(), par);
  }

/* ************************************************************************** */

  // Auxiliary member functions (for PostOrderFoldableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node& node) const {

    if (node.HasLeftChild()) {
      FoldPostOrder(fun, par, acc, node.LeftChild());
    }

    if (node.HasRightChild()) {
      FoldPostOrder(fun, par, acc, node.RightChild());
    }

    fun(node.Element(), par, acc);
  }

/* ************************************************************************** */

  // Auxiliary member functions (for InOrderMappableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node& node) {
    if (node.HasLeftChild()) {
      MapInOrder(fun, par, node.LeftChild());
    }

    fun(node.Element(), par);

    if (node.HasRightChild()) {
      MapInOrder(fun, par, node.RightChild());
    }
  }

/* ************************************************************************** */

  // Auxiliary member functions (for InOrderFoldableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node& node) const {
    if (node.HasLeftChild()) {
      FoldInOrder(fun, par, acc, node.LeftChild());
    }

    fun(node.Element(), par, acc);

    if (node.HasRightChild()) {
      FoldInOrder(fun, par, acc, node.RightChild());
    }
  }

/* ************************************************************************** */

  // Auxiliary member functions (for BreadthMappableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par, Node* node) {}

/* ************************************************************************** */

  // Auxiliary member functions (for BreadthFoldableContainer) <BinaryTree>

  template <typename Data>
  void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc, Node* node) {}


/* ************************************************************************** */

  // Specific constructors <BTPreOrderIterator>

  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
    root = &bt.Root();
    node = root;
    stack = StackLst<struct BinaryTree<Data>::Node*>();
  }

/* ************************************************************************** */

  // Copy constructor <BTPreOrderIterator>

  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& btPre) {
    root = btPre.root;
    node = btPre.node;
    stack = btPre.stack;
  }

  // Move constructor <BTPreOrderIterator>

  template <typename Data>
  BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& btPre) noexcept {
    std::swap(root, btPre.root);
    std::swap(node, btPre.node);
    std::swap(stack, btPre.stack);
  }

/* ************************************************************************** */

  // Copy assignment <BTPreOrderIterator>

  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& btPre) {
    root = btPre.root;
    node = btPre.node;
    stack = btPre.stack;
    return *this;
  }

  // Move assignment <BTPreOrderIterator>

  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& btPre) noexcept {
    std::swap(root, btPre.root);
    std::swap(node, btPre.node);
    std::swap(stack, btPre.stack);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators <BTPreOrderIterator>

  template <typename Data>
  bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& btPre) const noexcept {
    return ((node == btPre.node) && (stack == btPre.stack));
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& btPre) const noexcept {
    return !(*this == btPre);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Iterator) <BTPreOrderIterator>

  template <typename Data>
  Data& BTPreOrderIterator<Data>::operator*() const {
    if (!Terminated()) {
      return node->Element();
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

  template <typename Data>
  bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (node == nullptr);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ForwardIterator) <BTPreOrderIterator>

  template <typename Data>
  BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if (!Terminated()) {
      if (node->HasRightChild()) {
        stack.Push((&node->RightChild()));
      }

      if (node->HasLeftChild()) {
        stack.Push((&node->LeftChild()));
      }

      if (stack.Empty()) {
        node = nullptr;
      }
      else {
        node = stack.TopNPop();
      }

      return *this;
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

/* ************************************************************************** */

    // Specific member functions (inherited from ResettableIterator) <BTPreOrderIterator>

    template <typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept {
      if (root != nullptr) {
        node = root;
        stack.Clear();
      }
    }

/* ************************************************************************** */

  // Specific constructors <BTPostOrderIterator>

  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
    root = &bt.Root();
    node = root;
    last = node;
    stack = StackLst<struct BinaryTree<Data>::Node*>();

    while (!node->IsLeaf()) {
      if (node->HasLeftChild()) {
        stack.Push(node);
        node = &(node->LeftChild());
      }
      else if (node->HasRightChild()) {
        stack.Push(node);
        node = &(node->RightChild());
      }
    }
  }

/* ************************************************************************** */

  // Copy constructor <BTPostOrderIterator>

  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& btPost) {
    root = btPost.root;
    node = btPost.node;
    last = btPost.last;
    stack = btPost.stack;
  }

  // Move constructor <BTPostOrderIterator>

  template <typename Data>
  BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& btPost) noexcept {
    std::swap(root, btPost.root);
    std::swap(node, btPost.node);
    std::swap(last, btPost.last);
    std::swap(stack, btPost.stack);
  }

/* ************************************************************************** */

  // Copy assignment <BTPostOrderIterator>

  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& btPost) {
    root = btPost.root;
    node = btPost.node;
    last = btPost.last;
    stack = btPost.stack;
    return *this;
  }

  // Move assignment <BTPostOrderIterator>

  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& btPost) {
    std::swap(root, btPost.root);
    std::swap(node, btPost.node);
    std::swap(last, btPost.last);
    std::swap(stack, btPost.stack);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators <BTPostOrderIterator>

  template <typename Data>
  bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& btPost) const noexcept {
    return ((node == btPost.node) && (stack == btPost.stack));
  }

  template <typename Data>
  bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& btPost) const noexcept {
    return !(*this == btPost);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Iterator) <BTPostOrderIterator>

  template <typename Data>
  Data& BTPostOrderIterator<Data>::operator*() const {
    if (!Terminated()) {
      return node->Element();
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

  template <typename Data>
  bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (node == nullptr);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ForwardIterator) <BTPostOrderIterator>

  template <typename Data>
  BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if (!Terminated()) {

      if (!stack.Empty()) {
        node = stack.TopNPop();

        if (node->HasRightChild()) {
          if (&node->RightChild() != last) {
            stack.Push(node);
            node = &node->RightChild();

            while (!node->IsLeaf()) {
              if (node->HasLeftChild()) {
                stack.Push(node);
                node = &(node->LeftChild());
              }
              else if (node->HasRightChild()) {
                stack.Push(node);
                node = &(node->RightChild());
              }
            }
          }
        }
      }
      else {
        node = nullptr;
      }

      last = node;

      return *this;
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ResettableIterator) <BTPostOrderIterator>

  template <typename Data>
  void BTPostOrderIterator<Data>::Reset() noexcept {
    if (root != nullptr) {
      node = root;
      stack.Clear();

      while (!node->IsLeaf()) {
        if (node->HasLeftChild()) {
          stack.Push(node);
          node = &(node->LeftChild());
        }
        else if (node->HasRightChild()) {
          stack.Push(node);
          node = &(node->RightChild());
        }
      }
    }
  }

/* ************************************************************************** */

  template <typename Data>
  typename BinaryTree<Data>::Node& BTInOrderIterator<Data>::MostLeftNode(typename BinaryTree<Data>::Node* nod) {
    while (nod->HasLeftChild()) {
      stack.Push(nod);
      nod = &(nod->LeftChild());
    }

    return *nod;
  }

/* ************************************************************************** */

  // Specific constructors <BTInOrderIterator>

  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
    root = &bt.Root();
    node = &MostLeftNode(root);
  }

/* ************************************************************************** */

  // Copy constructor <BTInOrderIterator>

  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& btIn) {
    root = btIn.root;
    node = btIn.node;
    stack = btIn.stack;
  }

  // Move constructor <BTInOrderIterator>

  template <typename Data>
  BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& btIn) noexcept {
    std::swap(root, btIn.root);
    std::swap(node, btIn.node);
    std::swap(stack, btIn.stack);
  }

/* ************************************************************************** */

  // Copy assignment <BTInOrderIterator>

  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& btIn) {
    root = btIn.root;
    node = btIn.node;
    stack = btIn.stack;
    return *this;
  }

  // Move assignment <BTInOrderIterator>

  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& btIn) noexcept {
    std::swap(root, btIn.root);
    std::swap(node, btIn.node);
    std::swap(stack, btIn.stack);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators <BTInOrderIterator>

  template <typename Data>
  bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& btIn) const noexcept {
    return ((node == btIn.node) && (stack == btIn.stack));
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& btIn) const noexcept {
    return !(*this == btIn);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Iterator) <BTInOrderIterator>

  template <typename Data>
  Data& BTInOrderIterator<Data>::operator*() const {
    if (!Terminated()) {
      return node->Element();
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

  template <typename Data>
  bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (node == nullptr);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ForwardIterator) <BTInOrderIterator>

  template <typename Data>
  BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if (!Terminated()) {
      if (node->HasRightChild()) {
          node = &MostLeftNode(&(node->RightChild()));
      }
      else if (!stack.Empty()) {
        node = stack.TopNPop();
      }
      else {
        node = nullptr;
      }

      return *this;
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ResettableIterator) <BTInOrderIterator>

  template <typename Data>
  void BTInOrderIterator<Data>::Reset() noexcept {
    if (root != nullptr) {
      node = root;
      stack.Clear();

      while (node->HasLeftChild()) {
        stack.Push(node);
        node = &node->LeftChild();
      }
    }
  }

/* ************************************************************************** */

  // Specific constructors <BTBreadthIterator>

  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
    root = &bt.Root();
    node = root;
    queue = QueueLst<struct BinaryTree<Data>::Node*>();
  }

/* ************************************************************************** */

  // Copy constructor <BTBreadthIterator>

  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& btBreadth) {
    root = btBreadth.root;
    node = btBreadth.node;
    queue = btBreadth.queue;
  }

  // Move constructor <BTBreadthIterator>

  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& btBreadth) noexcept {
    std::swap(root, btBreadth.root);
    std::swap(node, btBreadth.node);
    std::swap(queue, btBreadth.queue);
  }

/* ************************************************************************** */

  // Copy assignment <BTBreadthIterator>

  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& btBreadth) {
    root = btBreadth.root;
    node = btBreadth.node;
    queue = btBreadth.queue;
    return *this;
  }

  // Move assignment <BTBreadthIterator>

  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& btBreadth) noexcept {
    std::swap(root, btBreadth.root);
    std::swap(node, btBreadth.node);
    std::swap(queue, btBreadth.queue);
    return *this;
  }

/* ************************************************************************** */

  // Comparison operators <BTBreadthIterator>

  template <typename Data>
  bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& btBreadth) const noexcept {
    return ((node == btBreadth.node) && (queue == btBreadth.queue));
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& btBreadth) const noexcept {
    return !(*this == btBreadth);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from Iterator) <BTBreadthIterator>

  template <typename Data>
  Data& BTBreadthIterator<Data>::operator*() const {
    return node->Element();
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (node == nullptr);
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ForwardIterator) <BTBreadthIterator>

  template <typename Data>
  BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if (!Terminated()) {
      if (node->HasLeftChild()) {
        queue.Enqueue(&node->LeftChild());
      }

      if (node->HasRightChild()) {
        queue.Enqueue(&node->RightChild());
      }

      if (queue.Empty()) {
        node = nullptr;
      }
      else {
        node = queue.HeadNDequeue();
      }
    }
    else {
      throw std::out_of_range("Error! Out of range");
    }

    return *this;
  }

/* ************************************************************************** */

  // Specific member functions (inherited from ResettableIterator) <BTBreadthIterator>

  template <typename Data>
  void BTBreadthIterator<Data>::Reset() noexcept {
    if (root != nullptr) {
      node = root;
      queue.Clear();
    }
  }

/* ************************************************************************** */
}
