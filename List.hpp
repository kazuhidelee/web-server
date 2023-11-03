#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

// You should add in a default constructor, destructor, copy constructor,
// and overloaded assignment operator, if appropriate. If these operations
// will work correctly without defining these, you can omit them. A user
// of the class must be able to create, copy, assign, and destroy Lists

template <typename T>
class List
{

  // OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  List()
      : next(nullptr), prev(nullptr), datum(0), size(0) {}

  // EFFECTS:  returns true if the list is empty
  bool empty() const
  {
    return first == nullptr;
  }

  // EFFECTS: returns the number of elements in this List
  // HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //          with a private member variable.  That's how std::list does it.
  int size() const
  {
    return size;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    assert(!empty());
    return first->datum;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    assert(!empty());
    return last->datum;
  }

  // EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum)
  {
    Node *p = new Node;
    p->datum = datum;
    p->next = first;
    p->prev = nullptr;
    first->prev = p;
    first = p;

    size += 1;
  }

  // EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    Node *p = new Node;
    p->datum = datum;
    p->prev = last;
    p->next = nullptr;
    last->next = p;
    last = p;

    size += 1;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
    assert(!empty());
    Node *victim = first;
    first = first->next;
    first->prev = nullptr;
    delete victim;

    size -= 1;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
    assert(!empty());
    Node *victim = last;
    last = last->prev;
    last->next = nullptr;
    delete victim;

    size -= 1;
  }

  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes all items from the list
  void clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

private:
  // a private type
  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
  };

  // REQUIRES: list is empty
  // EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other)
  {
    assert(!(other.empty()));
    while (next != nullptr)
    {
      Node *p = new Node;
      first->datum = this->datum;
      first->next = this->next;
      first->prev = this->prev;
      // fix::
        }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last;  // points to last Node in list, or nullptr if list is empty
  int size = 0;

public:
  ////////////////////////////////////////
  class Iterator
  {
    // OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator &operator--()
    {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator &operator++()
    {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T &operator*() const
    {
      assert(node_ptr);
      return node_ptr->datum;
    }

    bool operator==(Iterator i) const
    {
      return node_ptr == i.node_ptr;
    }

    bool operator!=(Iterator i) const
    {
      return !(node_ptr == i.node_ptr);
    }

  private:
    Node *node_ptr; // current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p)
        : node_ptr(p) {}
    Iterator()
        : node_ptr(nullptr) {}

  }; // List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
    return Iterator(last->next);
  }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: may invalidate other list iterators
  // EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
    delete i.node_ptr;
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {
    (i.node_ptr)->push_front(datum);
  }

}; // List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
