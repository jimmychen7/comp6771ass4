#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <cassert>
/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)

template <typename T> class btree;

// btree_iterator interface
template <typename T>
class btree_iterator {
public:
    typedef std::ptrdiff_t                     difference_type;
    typedef std::forward_iterator_tag          iterator_category;
    typedef T                                  value_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;
    
    reference operator*() const;
    pointer operator->() const;
    btree_iterator& operator++();
    bool operator==(const btree_iterator& other) const;
    bool operator!=(const btree_iterator& other) const;

    btree_iterator(typename btree<T>::Node::Element *pointee = nullptr);
private:
    typename btree<T>::Node::Element *pointee_;
};

// const_btree_iterator interface
template <typename T>
class const_btree_iterator {
public:
private:
};

// btree_iterator
template <typename T>
btree_iterator<T>::btree_iterator(typename btree<T>::Node::Element *pointee)
    : pointee_{pointee} {
}


template <typename T> typename btree_iterator<T>::reference 
btree_iterator<T>::operator*() const {
    return pointee_->value_;
}

template <typename T>
T* btree_iterator<T>::operator->() const {
    return &(operator*());
}

template <typename T> btree_iterator<T>& 
btree_iterator<T>::operator++() {
    assert(pointee_ != nullptr);
    pointee_ = pointee_->next_;
    return *this;
}

template <typename T>
bool btree_iterator<T>::operator==(const btree_iterator<T>& other) const {
    return this->pointee_ == other.pointee_;
}

template <typename T>
bool btree_iterator<T>::operator!=(const btree_iterator& other) const {
    return !operator==(other);
}

//const_btree_iterator


#endif
