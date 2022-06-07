
namespace lasd {

/* ************************************************************************** */

// Specific constructors <Node>

template <typename Data>
List<Data>::Node::Node(Data&& data) noexcept {
  std::swap(value, data);
}

/* ************************************************************************** */

// Move constructor <Node>

template <typename Data>
List<Data>::Node::Node(Node&& node) noexcept {
  std::swap(value, node->value);
  std::swap(next, node->next);
}

/* ********************************************************************** */

// Comparison operators <Node>

template <typename Data>
bool List<Data>::Node::operator==(const Node& node) const noexcept {
  return ((value == node->value) && (*next == *node->next));
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node& node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************ */

// Specific constructor <List>

template <typename Data>
List<Data>::List(const LinearContainer<Data>& lc) {
  for(ulong i = 0; i < lc.Size(); i++) {
    InsertAtBack(lc[i]);
  }
}

/* ************************************************************************ */

// Copy constructor <List>

template <typename Data>
List<Data>::List(const List<Data>& list) {
  for(ulong i = 0; i < list.size; i++) {
    InsertAtBack(list[i]);
  }
  size = list.size;
}

// Move constructor <List>

template <typename Data>
List<Data>::List(List<Data>&& list) noexcept {
  std::swap(head, list.head);
  std::swap(tail, list.tail);
  std::swap(size, list.size);
}

/* ************************************************************************ */

// Destructor <List>

template <typename Data>
List<Data>::~List() {
  Clear();
}

/* ************************************************************************ */

// Copy assignment <List>

template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& list) {
  List<Data>* tempList = new List<Data>(list);
  std::swap(*this, *tempList);
  delete tempList;
  return *this;
}

// Move assignment <List>

template <typename Data>
List<Data>& List<Data>::operator=(List<Data>&& list) noexcept {
  std::swap(head, list.head);
  std::swap(tail, list.tail);
  std::swap(size, list.size);
  return *this;
}

/* ************************************************************************ */

// Comparison operators <List>

template <typename Data>
bool List<Data>::operator==(const List<Data>& list) const noexcept {
  if (size == list.size) {
    for(ulong i = 0; i < size; i++) {
      if ((*this)[i] != list[i]) {
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
bool List<Data>::operator!=(const List<Data>& list) const noexcept {
  return !((*this) == list);
}

/* ************************************************************************ */

// Specific member functions <List>

template <typename Data>
void List<Data>::InsertAtFront(const Data& newvalue) {
  Node* newnode = new Node(newvalue);
  newnode->next = head;
  if (head == nullptr) {
    tail = newnode;
  }
  head = newnode;
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& newvalue) noexcept {
  Node* newnode = new Node(std::move(newvalue));
  newnode->next = head;
  if (head == nullptr) {
    tail = newnode;
  }
  head = newnode;
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
  if (head != nullptr) {
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
  }
  else {
    throw std::length_error("Error! Empty list");
  }
}

template <typename Data>
Data List<Data>::FrontNRemove() {
  if (head != nullptr) {
    Node* temp = head;
    Data value = head->value;
    head = head->next;
    delete temp;
    size--;
    return value;
  }
  else {
    throw std::length_error("Error! Empty list");
  }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& newvalue) {
  Node* newnode = new Node(newvalue);
  newnode->next = nullptr;
  if (head == nullptr) {
    head = newnode;
    tail = newnode;
  }
  else {
    tail->next = newnode;
    tail = newnode;
  }
  size++;
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& newvalue) noexcept {
  Node* newnode = new Node(std::move(newvalue));
  newnode->next = nullptr;
  if (head == nullptr) {
    head = newnode;
    tail = newnode;
  }
  else {
    tail->next = newnode;
    tail = newnode;
  }
  size++;
}

/* ************************************************************************ */

// Specific member functions (inherited from Container) <List>

template <typename Data>
void List<Data>::Clear() {
  Node* curr = head;
  while (head != nullptr) {
    head = curr->next;
    curr->~Node();
    curr = head;
  }
  size = 0;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer) <List>

template <typename Data>
Data& List<Data>::Front() const {
  if (size != 0) {
    return head->value;
  }
  else {
    throw std::length_error("Error! Empty list");
  }
}

template <typename Data>
Data& List<Data>::Back() const {
  if (size != 0) {
    return tail->value;
  }
  else {
    throw std::length_error("Error! Empty list");
  }
}

template <typename Data>
Data& List<Data>::operator[](const ulong i) const {
  ulong j = 0;
  Node* curr = head;

  while ((curr != nullptr) && (j < i)) {
    curr = curr->next;
    j++;
  }

  if (curr != nullptr) {
    return curr->value;
  }
  else {
    throw std::length_error("Error! Unable to access this index");
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer) <List>

template <typename Data>
inline void List<Data>::Map(MapFunctor fun, void* par) {
  MapPreOrder(fun, par);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer) <List>

template <typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par) {
  Node* temp = head;
  MapPreOrder(fun, par, temp);
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer) <List>

template <typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par) {
  Node* temp = head;
  MapPostOrder(fun, par, temp);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer) <List>

template <typename Data>
inline void List<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  FoldPreOrder(fun, par, acc);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer) <List>

template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const {
  Node* temp = head;
  FoldPreOrder(fun, par, acc, temp);
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer) <List>

template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const {
  Node* temp = head;
  FoldPostOrder(fun, par, acc, temp);
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer) <List>

template <typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par, Node* node) {
  if(node != nullptr) {
    fun(node->value, par);
    MapPreOrder(fun, par, node->next);
  }
}

template <typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par, Node* node) {
  if(node != nullptr) {
    MapPostOrder(fun, par, node->next);
    fun(node->value, par);
  }
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer) <List>

template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
  if (node != nullptr) {
    fun(node->value, par, acc);
    FoldPreOrder(fun, par, acc, node->next);
  }
}

template <typename Data>
void List<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
  if (node != nullptr) {
    FoldPostOrder(fun, par, acc, node->next);
    fun(node->value, par, acc);
  }
}
}
