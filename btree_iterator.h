#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)

class btree_iterator {
public:
    btree_iterator();
    ~btree_iterator();
private:
};

class const_btree_iterator {
public:
    const_btree_iterator();
    ~const_btree_iterator();
private:
};
    
#endif
