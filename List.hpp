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
  // default constructor
  List()
      : first(nullptr), last(nullptr), count(0) {}

  // copy constructor
  List(const List<T> &other)
  {
    first = nullptr;
    last = nullptr;
    count = 0;
    copy_all(other);
  }

  // destructor
  ~List()
  {
    clear();
  }
  // assignment
  List &operator=(const List<T> &other)
  {
    if (this == &other)
    {
      return *this;
    }
    first = nullptr;
    last = nullptr;
    count = 0;

    clear();
    copy_all(other);

    return *this;
  }

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
    return count;
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
    if (first != nullptr)
    {
      first->prev = p;
    }
    first = p;
    if (last == nullptr)
    {
      last = p;
    }

    count += 1;
  }

  // EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    Node *p = new Node;
    p->datum = datum;
    p->prev = last;
    p->next = nullptr;
    if (last != nullptr)
    {
      last->next = p;
    }
    last = p;
    if (first == nullptr)
    {
      first = p;
    }

    count += 1;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
    assert(!empty());
    Node *victim = first;
    first = first->next;
    if (first != nullptr)
    {
      first->prev = nullptr;
    }
    else
    {
      last = nullptr;
    }
    delete victim;

    count -= 1;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
    assert(!empty());
    Node *victim = last;
    last = last->prev;
    if (last != nullptr)
    {
      last->next = nullptr;
    }
    else
    {
      first = nullptr;
    }
    delete victim;

    count -= 1;
  }

  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes all items from the list
  void clear()
  {
    while (!empty())
    {
      pop_front();
    }
    first = nullptr;
    last = nullptr;
    count = 0;
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
    for (Node *np = other.first; np; np = np->next)
    {
      push_back(np->datum);
    }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last;  // points to last Node in list, or nullptr if list is empty
  int count;

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

    Iterator()
        : node_ptr(nullptr) {}

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
    assert(!(i.node_ptr == nullptr));

    Node *remove = i.node_ptr;
    Node *remove_next = remove->next;
    Node *remove_prev = remove->prev;
    if (remove_next != nullptr)
    {
      remove_next->prev = remove_prev;
    }
    else
    {
      last = remove_prev;
    }

    if (remove_prev != nullptr)
    {
      remove_prev->next = remove_next;
    }
    else
    {
      first = remove_next;
    }

    delete remove;
    count -= 1;
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {
    assert(!(i.node_ptr == nullptr));
    Node *insert = new Node;
    insert->datum = datum;

    Node *curr = i.node_ptr;
    Node *before = curr->prev;

    insert->next = curr;
    insert->prev = before;
    curr->prev = insert;
    if (before != nullptr)
    {
      before->next = insert;
    }
    else
    {
      first = insert;
    }

    count += 1;
  }

}; // List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
