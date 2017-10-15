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
    typedef std::bidirectional_iterator_tag    iterator_category;
    typedef T                                  value_type;
    typedef std::ptrdiff_t                     difference_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;
    
    typedef typename btree<T>::Node Node;
    typedef typename btree<T>::Node::Element Element;
    
    reference operator*() const;
    pointer operator->() const;
    btree_iterator& operator++();
    btree_iterator operator++(int);
    bool operator==(const btree_iterator& other) const;
    bool operator==(const const_btree_iterator<T>& other) const;
    bool operator!=(const btree_iterator& other) const;
    bool operator!=(const const_btree_iterator<T>& other) const;
    
    btree_iterator(const btree<T>& tree, Element *pointee);
    btree_iterator(const btree<T>& tree, std::string pos);
private:
    std::vector<std::shared_ptr<Element>> toVector(const btree<T>& tree);
    
    std::vector<std::shared_ptr<Element>> elems_;
    unsigned int index_;
};

// const_btree_iterator interface
template <typename T>
class const_btree_iterator {
    friend class btree_iterator<T>;
public:
    typedef std::bidirectional_iterator_tag    iterator_category;
    typedef T                                  value_type;
    typedef std::ptrdiff_t                     difference_type;
    typedef T*                                 pointer;
    typedef T&                                 reference;
    
    typedef typename btree<T>::Node Node;
    typedef typename btree<T>::Node::Element Element;
          
    bool operator==(const const_btree_iterator& other) const;
    bool operator==(const btree_iterator<T>& other) const;
    bool operator!=(const const_btree_iterator& other) const;
    bool operator!=(const btree_iterator<T>& other) const;
    

    const_btree_iterator(const btree<T>& tree, Element *pointee);
    const_btree_iterator(const btree<T>& tree, std::string pos);
private:
    std::vector<std::shared_ptr<Element>> toVector(const btree<T>& tree);
    
    std::vector<std::shared_ptr<Element>> elems_;
    unsigned int index_;
};

// btree_iterator
template <typename T>
btree_iterator<T>::btree_iterator(const btree<T>& tree
                                , typename btree<T>::Node::Element *elem)
    : elems_{}
    , index_{} {
    elems_ = toVector(tree);
    for(unsigned int i = 0; i < elems_.size(); ++i) {
        if(elems_.at(0)->value_ == elem->value_) {
            index_ = i;
        }        
    }
}

template <typename T>
btree_iterator<T>::btree_iterator(const btree<T>& tree
                                                , std::string pos)
    : elems_{} 
    , index_{} {
    elems_ = toVector(tree);
    if(pos == "begin") {
        index_ = 0;
    } else if (pos == "end") {
        index_ = elems_.size();
    }
}

template <typename T>
std::vector<std::shared_ptr<typename btree<T>::Node::Element>> 
btree_iterator<T>::toVector(const btree<T>& tree) {
    typedef typename btree<T>::Node Node;
    typedef typename btree<T>::Node::Element Element;
    
    std::vector<std::shared_ptr<Element>> vector{};
    auto nodesToPrint = std::queue<std::shared_ptr<Node>>();
    
    nodesToPrint.push(tree.root_);
    while(!nodesToPrint.empty()) {
        Node *node = nodesToPrint.front().get();
        nodesToPrint.pop();
        
        auto elements = node->elems_;
        
        for (unsigned int i = 0; i < elements.size(); ++i) {
        
            vector.push_back(std::make_shared<Element>(elements.at(i)));
        }
        
        if(elements.size() == tree.maxNodeElems_) {
            auto firstElement = elements.at(0);
            std::shared_ptr<Node> leftChildPtr = firstElement.getLeftChild();
            std::shared_ptr<Node> rightChildPtr = firstElement.getRightChild();
            if(!leftChildPtr.get()->isEmpty()) {
                nodesToPrint.push(leftChildPtr);
            }
            if(!rightChildPtr.get()->isEmpty()) {
                nodesToPrint.push(rightChildPtr);
            }
            for (unsigned int i = 1; i < elements.size(); i++) {
                auto currElement = elements.at(i);
                rightChildPtr = currElement.getRightChild();
                if(!rightChildPtr.get()->isEmpty()) {
                    nodesToPrint.push(rightChildPtr);
                }
            }
        }
        
    }
    std::sort( vector.begin( ), vector.end( )
        , [ ]( const std::shared_ptr<Element>& lhs
                , const std::shared_ptr<Element>& rhs ) {
                    return lhs.get()->getValue() < rhs.get()->getValue();
                });
    return vector;
}

template <typename T> typename btree_iterator<T>::reference 
btree_iterator<T>::operator*() const {
    return elems_.at(index_).get()->value_;
}

template <typename T>
T* btree_iterator<T>::operator->() const {
    return &(operator*());
}

//TODO
template <typename T> btree_iterator<T>& 
btree_iterator<T>::operator++() {
    // assert(pointee_.get() != nullptr);
    if(index_ == elems_.size()) {
        return *this;
    } 
    index_++;
    return *this;
}

template <typename T> btree_iterator<T>
btree_iterator<T>::operator++(int dummy) {
    btree_iterator<T> result(*this);
    ++(*this);
    return result;
}

template <typename T>
bool btree_iterator<T>::operator==(const btree_iterator& other) const {
    if(index_ == other.index_) {
        return true;
    }
    
    return false;
}

template <typename T>
bool btree_iterator<T>::operator==(const const_btree_iterator<T>& other) const {
    typename btree<T>::Node::Element *a = elems_.at(index_).get();
    typename btree<T>::Node::Element *b = other.elems_.at(other.index_).get();
    
    if(a == b) {
        return true;
    }
    
    if(a->getValue() == b->getValue()) {
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
const_btree_iterator<T>::const_btree_iterator(const btree<T>& tree
                                    , typename btree<T>::Node::Element *elem)
    : elems_{}
    , index_{} {
    elems_ = toVector(tree);
    for(unsigned int i = 0; i < elems_.size(); ++i) {
        if(elems_.at(0).getValue() == elem->getValue()) {
            index_ = i;
        }        
    }
}

template <typename T>
const_btree_iterator<T>::const_btree_iterator(const btree<T>& tree
                                                            , std::string pos)
    : elems_{} 
    , index_{} {
    elems_ = toVector(tree);
    if(pos == "begin") {
        index_ = 0;
    } else if (pos == "end") {
        index_ = elems_.size();
    }
}

template <typename T>
std::vector<std::shared_ptr<typename btree<T>::Node::Element>> 
const_btree_iterator<T>::toVector(const btree<T>& tree) {
    typedef typename btree<T>::Node Node;
    typedef typename btree<T>::Node::Element Element;
    
    std::vector<std::shared_ptr<Element>> vector{};
    auto nodesToPrint = std::queue<std::shared_ptr<Node>>();
    
    nodesToPrint.push(tree.root_);
    while(!nodesToPrint.empty()) {
        Node *node = nodesToPrint.front().get();
        nodesToPrint.pop();
        
        auto elements = node->elems_;
        
        for (unsigned int i = 0; i < elements.size(); ++i) {
        
            vector.push_back(std::make_shared<Element>(elements.at(i)));
        }
        
        if(elements.size() == tree.maxNodeElems_) {
            auto firstElement = elements.at(0);
            std::shared_ptr<Node> leftChildPtr = firstElement.getLeftChild();
            std::shared_ptr<Node> rightChildPtr = firstElement.getRightChild();
            if(!leftChildPtr.get()->isEmpty()) {
                nodesToPrint.push(leftChildPtr);
            }
            if(!rightChildPtr.get()->isEmpty()) {
                nodesToPrint.push(rightChildPtr);
            }
            for (unsigned int i = 1; i < elements.size(); i++) {
                auto currElement = elements.at(i);
                rightChildPtr = currElement.getRightChild();
                if(!rightChildPtr.get()->isEmpty()) {
                    nodesToPrint.push(rightChildPtr);
                }
            }
        }
        
    }
    std::sort( vector.begin( ), vector.end( )
        , [ ]( const std::shared_ptr<Element>& lhs
                , const std::shared_ptr<Element>& rhs ) {
                    return lhs.get()->getValue() < rhs.get()->getValue();
                });
    return vector;
}

template <typename T>
bool const_btree_iterator<T>::operator==(const const_btree_iterator& other) const {
    typename btree<T>::Node::Element *a = this->pointee_.get();
    typename btree<T>::Node::Element *b = other.pointee_.get();
    
    if(a == b) {
        return true;
    }
    
    if(a->getValue() == b->getValue()) {
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
    
    if(a->getValue() == b->getValue()) {
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
