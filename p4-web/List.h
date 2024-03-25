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
    bool empty() const {
        return first == nullptr && last == nullptr;
    }
    
    //EFFECTS: returns the number of elements in this List
    //HINT:    Traversing a list is really slow.  Instead, keep track of the size
    //         with a private member variable.  That's how std::list does it.
    int size() const{
        return counter;
    }
    
    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T & front(){
        assert(!empty());
        return first->datum;
    }
    
    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T & back(){
        assert(!empty());
        return last->datum;
    }
    
    //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum){
        Node* node = new Node{ first, nullptr, datum };
        if (empty()) first = last = node;
        else {
            first->prev = node;
            first = node;
        }
        counter++;
    }
    
    //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum){
        Node* node = new Node{ nullptr, last, datum };
        if (empty()) first = last = node;
        else {
            last->next = node;
            last = node;
        }
        counter++;
    }
    
    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list
    void pop_front(){
        assert(!empty());
        Node *victim = first;           // temporary keeps track of old first
        if (first != last) {
            first = first->next;
            first->prev = nullptr;
        } else {
            first = last = nullptr;
        }
        delete victim;
        counter--;
    }
    
    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back(){
        assert(!empty());
        Node *victim = last;           // temporary keeps track of old first
        if (first != last) {
            last = last->prev;
            last->next = nullptr;
        } else {
            first = last = nullptr;
        }
        delete victim;
        counter--;
    }
    
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all items from the list
    void clear(){
        while (!empty()) {
            pop_front();
        }
    }
    
    //default constructor
    List<T>() : first(nullptr), last(nullptr), counter(0) {};
    
    //big three
    List(const List &other) : List() {
        copy_all(other);
    }
    
    List<T> & operator=(const List<T> &rhs) {
        if (this != &rhs) {
            clear();
            copy_all(rhs);
        }
        return *this;
    }
    
    ~List() {
        clear();
    }
    
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
  int counter;

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
    Iterator() : node_ptr(nullptr) {};

    Iterator(const List<T>::Iterator& other) : node_ptr(other.node_ptr) {};

	Iterator &operator=(const List<T>::Iterator& rhs) {
        node_ptr = rhs.node_ptr;
        return *this;
	}

	~Iterator() {}

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

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
    Iterator(Node *node_ptr) : node_ptr(node_ptr) {};

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    if (i.node_ptr == first) {
		pop_front();
    } else if (i.node_ptr == last) {
		pop_back();
	} else {
        i.node_ptr->prev->next = i.node_ptr->next;
        i.node_ptr->next->prev = i.node_ptr->prev;
        delete i.node_ptr;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if (i == begin()) {
		push_front(datum);
    } else if (i == end()) {
		push_back(datum);
	} else {
        Node* node = new Node{ i.node_ptr, i.node_ptr->prev, datum };
        node->prev->next = node;
        node->next->prev = node;
    }
  }
};//List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
