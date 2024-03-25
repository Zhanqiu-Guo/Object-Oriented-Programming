#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front();

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back();

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum);

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back();

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear();

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    for (Node *node = other.first; node != nullptr; node = node->next) {
      push_back(node->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator() : node_ptr(nullptr) {};

    T & operator*() {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {};

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    i.node_ptr->prev->next = i.node_ptr->next;
		i.node_ptr->next->prev = i.node_ptr->prev;
		delete i.node_ptr;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    Node* node = new Node;
			node->datum = datum;
			node->prev = i.node_ptr->prev;
			node->next = i.node_ptr;
			(i.node_ptr)->prev->next = node;
      (i.node_ptr)->prev = node;
  }
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

//EFFECTS:  returns true if the list is empty
template<typename T>
bool List<T>::empty() const {
    return first == nullptr && last == nullptr;
}

//EFFECTS: returns the number of elements in this List
//HINT:    Traversing a list is really slow.  Instead, keep track of the size
//         with a private member variable.  That's how std::list does it.
template<typename T>
int List<T>::size() const{
    int counter = 0;
    for (Node *node_ptr = first; node_ptr; node_ptr = node_ptr->next){
        counter++;
    }
  }

//REQUIRES: list is not empty
//EFFECTS: Returns the first element in the list by reference
template<typename T>
T & List<T>::front(){
    assert(!empty());
    return first->datum;
}

//REQUIRES: list is not empty
//EFFECTS: Returns the last element in the list by reference
template<typename T>
T & List<T>::back(){
    assert(!empty());
    return last->datum;
  }

//EFFECTS:  inserts datum into the front of the list
template<typename T>
void List<T>::push_front(const T &datum){
    first = new Node{ first, nullptr, datum };
  }

//EFFECTS:  inserts datum into the back of the list
template<typename T>
void List<T>::push_back(const T &datum){
    last = new Node{ nullptr, last, datum };
  }

//REQUIRES: list is not empty
//MODIFIES: may invalidate list iterators
//EFFECTS:  removes the item at the front of the list
template<typename T>
void List<T>::pop_front(){
    assert(!empty());
    Node *victim = first;           // temporary keeps track of old first
    first = first->next;
    first->prev = nullptr;
    delete victim;
}

//REQUIRES: list is not empty
//MODIFIES: may invalidate list iterators
//EFFECTS:  removes the item at the back of the list
template<typename T>
void List<T>::pop_back(){
    assert(!empty());
    Node *victim = last;           // temporary keeps track of old first
    last = last->prev;
    last->next = nullptr;
    delete victim;
  }

//MODIFIES: may invalidate list iterators
//EFFECTS:  removes all items from the list
template<typename T>
void List<T>::clear(){
    while (!empty()) {
       pop_front();
     }
  }

//REQUIRES: list is empty
//EFFECTS:  copies all nodes from other to this
template<typename T>
void List<T>::copy_all(const List<T> &other){
    for (Node *node_ptr = other.first; node_ptr; node_ptr = node_ptr->next) {
      push_back(node_ptr->datum);
    }
}

//big three
template<typename T>
List<T>::List(const List &other) : List() {
  push_all(other);
}

template<typename T>
List<T> & List<T>::operator=(const List<T> &rhs) {
  if (this != &rhs) {
    clear();
    push_all(rhs);
  }
  return *this;
}

template<typename T>
List<T>::~List() {
  clear();
}

#endif // Do not remove this. Write all your code above this line.
