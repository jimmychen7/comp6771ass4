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

template <typename T> class const_btree_iterator;

// btree_iterator interface
template <typename T>
class btree_iterator {
    friend class const_btree_iterator<T>;
public:
    typedef std::forward_iterator_tag          iterator_category;
    typedef T                                  value_type;
    typedef std::ptrdiff_t                     difference_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;
    
    reference operator*() const;
    pointer operator->() const;
    btree_iterator& operator++();
    bool operator==(const btree_iterator& other) const;
    bool operator==(const const_btree_iterator<T>& other) const;
    bool operator!=(const btree_iterator& other) const;
    bool operator!=(const const_btree_iterator<T>& other) const;
    
    btree_iterator(std::shared_ptr<typename btree<T>::Node::Element> pointee);
    btree_iterator(typename btree<T>::Node::Element *pointee = nullptr);
private:
    std::shared_ptr<typename btree<T>::Node::Element> pointee_;
};

// const_btree_iterator interface
template <typename T>
class const_btree_iterator {
    friend class btree_iterator<T>;
public:
    typedef std::forward_iterator_tag          iterator_category;
    typedef T                                  value_type;
    typedef std::ptrdiff_t                     difference_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;
          
    bool operator==(const const_btree_iterator& other) const;
    bool operator==(const btree_iterator<T>& other) const;
    bool operator!=(const const_btree_iterator& other) const;
    bool operator!=(const btree_iterator<T>& other) const;
    
    const_btree_iterator(std::shared_ptr<typename btree<T>::Node::Element> pointee);
    const_btree_iterator(typename btree<T>::Node::Element *pointee = nullptr);
    const_btree_iterator(const btree_iterator<T>& it);
private:
    std::shared_ptr<typename btree<T>::Node::Element> pointee_;
};

// btree_iterator
template <typename T>
btree_iterator<T>::btree_iterator(std::shared_ptr<typename btree<T>::Node::Element> pointee)
    : pointee_{pointee} {
}

template <typename T>
btree_iterator<T>::btree_iterator(typename btree<T>::Node::Element *pointee)
    : pointee_{std::make_shared<typename btree<T>::Node::Element>(*pointee)} {
}

template <typename T> typename btree_iterator<T>::reference 
btree_iterator<T>::operator*() const {
    return pointee_.get()->getValue();
}

template <typename T>
T* btree_iterator<T>::operator->() const {
    return &(operator*());
}

//TODO
template <typename T> btree_iterator<T>& 
btree_iterator<T>::operator++() {
    assert(pointee_.get() != nullptr);
    pointee_ = pointee_.get()->next_;
    return *this;
}

template <typename T>
bool btree_iterator<T>::operator==(const btree_iterator& other) const {
    typename btree<T>::Node::Element *a = this->pointee_.get();
    typename btree<T>::Node::Element *b = other.pointee_.get();
    
    if(a == b) {
        return true;
    }
    
    if(a->getValue() == b->getValue() && a->getParent() == b->getParent()) {
        return true;
    }
    
    return false;
}

template <typename T>
bool btree_iterator<T>::operator==(const const_btree_iterator<T>& other) const {
    typename btree<T>::Node::Element *a = this->pointee_.get();
    typename btree<T>::Node::Element *b = other.pointee_.get();
    
    if(a == b) {
        return true;
    }
    
    if(a->getValue() == b->getValue() && a->getParent() == b->getParent()) {
        return true;
    }
    
    return false;
}

template <typename T>
bool btree_iterator<T>::operator!=(const btree_iterator& other) const {
    return !operator==(other);
}

template <typename T>
bool btree_iterator<T>::operator!=(const const_btree_iterator<T>& other) const {
    return !operator==(other);
}

//const_btree_iterator
template <typename T>
const_btree_iterator<T>::const_btree_iterator(std::shared_ptr<typename btree<T>::Node::Element> pointee)
    : pointee_{pointee} {
}

template <typename T>
const_btree_iterator<T>::const_btree_iterator(typename btree<T>::Node::Element *pointee)
    : pointee_{std::make_shared<typename btree<T>::Node::Element>(*pointee)} {
}

template <typename T>
const_btree_iterator<T>::const_btree_iterator(const btree_iterator<T>& it)
    : pointee_{it.pointee_}{
}

template <typename T>
bool const_btree_iterator<T>::operator==(const const_btree_iterator& other) const {
    typename btree<T>::Node::Element *a = this->pointee_.get();
    typename btree<T>::Node::Element *b = other.pointee_.get();
    
    if(a == b) {
        return true;
    }
    
    if(a->getValue() == b->getValue() && a->getParent() == b->getParent()) {
        return true;
    }
    
    return false;
}

template <typename T>
bool const_btree_iterator<T>::operator==(const btree_iterator<T>& other) const {
    typename btree<T>::Node::Element *a = this->pointee_.get();
    typename btree<T>::Node::Element *b = other.pointee_.get();
    
    if(a == b) {
        return true;
    }
    
    if(a->getValue() == b->getValue() && a->getParent() == b->getParent()) {
        return true;
    }
    
    return false;
}

template <typename T>
bool const_btree_iterator<T>::operator!=(const const_btree_iterator& other) const {
    return !operator==(other);
}

template <typename T>
bool const_btree_iterator<T>::operator!=(const btree_iterator<T>& other) const {
    return !operator==(other);
}

#endif
