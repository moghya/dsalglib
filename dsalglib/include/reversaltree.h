// Implementation of splay tree on implicit key.  Emulates sequence of elements.
// Supports concatenating (merging), splitting and reversing sequences with
// log(n) complexity on average.

#ifndef DSALGLIB_REVERSALTREE_H
#define DSALGLIB_REVERSALTREE_H

#include "memory/unique_ptr.h"


namespace dsa {

using size_t = unsigned int;

template<class T, class U = T>
T exchange(T& obj, U&& new_value)
{
    T old_value = rvalue_cast(obj);
    obj = forward<U>(new_value);
    return old_value;
}

template<bool B, class T, class F>
struct conditional {
    using type = T;
};

template<class T, class F>
struct conditional<false, T, F> {
    using type = F;
};

template <bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

template <class ForwardIterator>
size_t iterator_distance(ForwardIterator first, ForwardIterator last) {
    size_t result = 0;
    while (first != last) {
        ++first;
        ++result;
    }
    return result;
}

template <class ForwardIterator>
ForwardIterator advance(ForwardIterator it, size_t steps) {
    for (size_t i = 0; i < steps; ++i) {
        ++it;
    }
    return it;
}

template <class T>
class ReversalTree {
    public:
        template <bool IsConst>
        class Iterator;

        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;

    private:
        class Node;

    public:
        ReversalTree() {}
        ReversalTree(const ReversalTree&) = delete;
        ReversalTree(ReversalTree&&);

        template <class ForwardIterator>
        ReversalTree(ForwardIterator begin, ForwardIterator end);

        ReversalTree& operator=(const ReversalTree&) = delete;
        ReversalTree& operator=(ReversalTree&&);

        bool empty() const noexcept {
            return !root_ptr();
        }

        size_type size() const noexcept {
            return dummy_.leftSubtreeSize();
        }

        void clear();

        // Return reference to element at given position.
        // Average complexity is O(log size()).
        // Recently accessed elements are accessed faster.
        reference at(size_type index);
        const_reference at(size_type index) const;

        reference front() {
            return at(0);
        }
        const_reference front() const {
            return at(0);
        }

        reference back() {
            return at(size() - 1);
        }
        const_reference back() const {
            return at(size() - 1);
        }

        // Remove elements in [left_size, size()) and return new tree with those
        // elements.
        // Complexity: O(log size())
        ReversalTree split(size_type left_size);

        // Split before given iterator.
        ReversalTree split(const_iterator);

        // Append elements from rhs to this tree.
        // Complexity: O(log size())
        void merge(ReversalTree&& rhs);

        // Reverse elements in range [first, last)
        // Complexity: O(log size())
        void reverse(size_type first, size_type last);

        iterator insert(const_iterator, T);

        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);

        void swap(ReversalTree& rhs) noexcept;

        // Iterating doesn't change tree structure.
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

    private:
        Node& root() const {
            return *(dummy_.son_[0]);
        }

        unique_ptr<Node>& root_ptr() const {
            return dummy_.son_[0];
        }

        bool isRoot(const Node& node) const {
            return node.dad_ == node.dad_->dad_;
        }

        template <class ForwardIterator>
        unique_ptr<Node> buildTree(ForwardIterator, ForwardIterator);
        template <class ForwardIterator>
        unique_ptr<Node> buildTree(ForwardIterator, ForwardIterator, size_t dist);

        void rotate(Node&);

        // Move node up making it root while rebalancing nodes on its path.
        void splay(Node&);

        Node& findNode(size_type index) const;

        void reverseTree() noexcept;

    private:
        mutable Node dummy_;
};

template <class T>
class ReversalTree<T>::Node {
    public:
        explicit Node(T data = T()) : data_(rvalue_cast(data)) {
            dad_ = this;
        }
        Node(const Node&) = delete;
        Node(Node&&) = default;

        bool whichSon() const noexcept {
            return dad_->son_[1].get() == this;
        }

        ReversalTree<T>::size_type leftSubtreeSize() const noexcept {
            return son_[0] ? son_[0]->subtree_size_ : 0;
        }

        void updateSubtreeSize() noexcept {
            subtree_size_ = 1;
            for (bool dir : {0, 1}) {
                if (son_[dir]) {
                    subtree_size_ += son_[dir]->subtree_size_;
                }
            }
        }

        void push() {
            if (reverse_) {
                swapit(son_[0], son_[1]);
                for (bool dir : {0, 1}) {
                    if (son_[dir]) {
                        son_[dir]->reverse_ ^= 1;
                    }
                }
                reverse_ = false;
            }
        }

        void link(unique_ptr<Node>&& son, bool dir) {
            son_[dir] = rvalue_cast(son);
            if (son_[dir]) {
                son_[dir]->dad_ = this;
            }
            updateSubtreeSize();
        }

    public:
        T data_;
        unique_ptr<Node> son_[2];
        Node* dad_;
        typename ReversalTree<T>::size_type subtree_size_ = 1;
        bool reverse_ = false;
};

template <class T>
template <bool IsConst>
class ReversalTree<T>::Iterator {
    friend class ReversalTree<T>;
    public:
        using value_type = ReversalTree::value_type;
        using reference = conditional_t<IsConst,
                                             ReversalTree::const_reference,
                                             ReversalTree::reference>;
        using pointer = conditional_t<IsConst,
                                           ReversalTree::const_pointer,
                                           ReversalTree::pointer>;

    public:
        Iterator() : node_(nullptr) {}
        Iterator(const Iterator<false>& rhs) {
            node_ = rhs.node_;
        }

        // Average complexity for increment / decrement operators is O(1)
        // Worst case complexity is O(height)
        Iterator& operator++();

        Iterator operator++(int) {
            auto result = *this;
            operator++();
            return result;
        }

        Iterator& operator--();

        Iterator operator--(int) {
            auto result = *this;
            operator--();
            return result;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.node_ == rhs.node_;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !operator==(lhs, rhs);
        }

        reference operator*() const {
            return node_->data_;
        }

        pointer operator->() const {
            return &node_->data_;
        }

        // Return index in containing ReversalTree.
        typename ReversalTree::size_type order() const;

    private:
        Iterator(ReversalTree::Node* node) : node_(node) {}

    private:
        ReversalTree::Node* node_;
};



template <class T>
ReversalTree<T>::ReversalTree(ReversalTree<T>&& rhs) {
    swap(rhs);
}

template <class T>
ReversalTree<T>& ReversalTree<T>::operator=(ReversalTree&& rhs) {
    swap(rhs);
    return *this;
}

template <class T>
template <class ForwardIterator>
ReversalTree<T>::ReversalTree(ForwardIterator begin, ForwardIterator end) {
    dummy_.link(buildTree(begin, end), 0);
}

template <class T>
template <class ForwardIterator>
auto ReversalTree<T>::buildTree(
    ForwardIterator begin,
    ForwardIterator end,
    size_t dist
) -> unique_ptr<Node> {
    if (dist == 0) {
        return nullptr;
    }
    if (dist == 1) {
        return make_unique<Node>(*begin);
    }
    const auto mid_pos = dist / 2;
    auto mid = advance(begin, mid_pos);
    auto result = make_unique<Node>(*mid);
    result->link(buildTree(begin, mid, mid_pos), 0);
    result->link(buildTree(++mid, end, dist - mid_pos - 1), 1);
    return result;
}
template <class T>
template <class ForwardIterator>
auto ReversalTree<T>::buildTree(
    ForwardIterator begin,
    ForwardIterator end
) -> unique_ptr<Node> {
    return buildTree(begin, end, iterator_distance(begin, end));
}

template <class T>
void ReversalTree<T>::clear() {
    root_ptr() = nullptr;
    dummy_.updateSubtreeSize();
}

template <class T>
void ReversalTree<T>::swap(ReversalTree<T>& rhs) noexcept {
    swapit(rhs.root_ptr(), root_ptr());
    if (root_ptr()) {
        root_ptr()->dad_ = &dummy_;
    }
    if (rhs.root_ptr()) {
        rhs.root_ptr()->dad_ = &rhs.dummy_;
    }
    dummy_.updateSubtreeSize();
    rhs.dummy_.updateSubtreeSize();
}

template <class T>
void ReversalTree<T>::rotate(Node& u) {
    if (&u == &dummy_ || isRoot(u)) {
        throw ("Attempt to rotate root");
    }
    Node& v = *u.dad_;
    Node& w = *v.dad_;
    const bool dir = u.whichSon();
    const bool dad_dir = v.whichSon();
    u.son_[!dir] = exchange(w.son_[dad_dir], exchange(v.son_[dir],
            exchange(u.son_[!dir], nullptr)));
    if (v.son_[dir]) {
        v.son_[dir]->dad_ = &v;
    }
    v.dad_ = &u;
    u.dad_ = &w;
    v.updateSubtreeSize();
    u.updateSubtreeSize();
    w.updateSubtreeSize();
}

template <class T>
void ReversalTree<T>::splay(Node& u) {
    EXPECTS(&u != &dummy_)
    while (!isRoot(u)) {
        Node& v = *u.dad_;
        if (isRoot(v)) {
            v.push();
            u.push();
            rotate(u);
        } else {
            v.dad_->push();
            v.push();
            u.push();
            const bool u_dir = u.whichSon();
            const bool v_dir = v.whichSon();
            if (u_dir == v_dir) {
                rotate(v);
                rotate(u);
            } else {
                rotate(u);
                rotate(u);
            }
        }
    }
}

template <class T>
auto ReversalTree<T>::findNode(size_type i) const -> Node& {
    size_type cumulated = 0;
    Node* p = root_ptr().get();
    while (true) {
        p->push();
        const size_type index = cumulated + p->leftSubtreeSize();
        if (index == i) {
            return *p;
        }
        if (i < index) {
            p = p->son_[0].get();
        } else {
            p = p->son_[1].get();
            cumulated = index + 1;
        }
    }
}

template <class T>
auto ReversalTree<T>::at(size_type i) -> reference {
    if (i >= size()) {
        throw "at(): index out of range";
    }
    splay(findNode(i));
    return root().data_;
}

template <class T>
auto ReversalTree<T>::at(size_type i) const -> const_reference {
    if (i >= size()) {
        throw "at(): index out of range";
    }
    return findNode(i).data_;
}

template <class T>
ReversalTree<T> ReversalTree<T>::split(size_type left_size) {
    return split(const_iterator(&findNode(left_size)));
}

template <class T>
ReversalTree<T> ReversalTree<T>::split(const_iterator it) {
    auto prev = it;
    try {
        --prev;
    } catch (...) {
        return rvalue_cast(*this);
    }
    splay(*prev.node_);
    ReversalTree<T> result;
    result.dummy_.link(rvalue_cast(root().son_[1]), 0);
    root().updateSubtreeSize();
    return result;
}

template <class T>
void ReversalTree<T>::merge(ReversalTree<T>&& rhs) {
    if (empty()) {
        swap(rhs);
        return;
    }
    if (rhs.empty()) {
        return;
    }
    splay(findNode(size() - 1));
    root().link(rvalue_cast(rhs.dummy_.son_[0]), 1);
}

template <class T>
void ReversalTree<T>::reverseTree() noexcept {
    if (!empty()) {
        root().reverse_ ^= true;
    }
}

template <class T>
void ReversalTree<T>::reverse(size_type first, size_type last) {
    if (first == 0 && last == size()) {
        reverseTree();
        return;
    }
    if (first > last) {
        throw "reverse(): first is greater than last";
    }
    if (last > size()) {
        throw "reverse(): last is greater than size";
    }
    auto right = split(last);
    auto center = split(first);
    center.reverseTree();
    merge(rvalue_cast(center));
    merge(rvalue_cast(right));
}

template <class T>
auto ReversalTree<T>::insert(const_iterator it, T e) -> iterator {
    Node* new_node = nullptr;
    if (!it.node_->son_[0]) {
        it.node_->link(make_unique<Node>(rvalue_cast(e)), 0);
        new_node = it.node_->son_[0].get();
    } else {
        Node* p = it.node_->son_[0].get();
        while (p->son_[1]) {
            p = p->son_[1].get();
        }
        p->link(make_unique<Node>(rvalue_cast(e)), 1);
        new_node = p->son_[1].get();
    }
    splay(*new_node);
    return iterator{new_node};
}

template <class T>
auto ReversalTree<T>::erase(const_iterator pos) -> iterator {
    const auto copy = pos;
    return erase(copy, ++pos);
}

template <class T>
auto ReversalTree<T>::erase(const_iterator first,
                         const_iterator last) -> iterator {
    auto right = split(last);
    split(first);
    merge(rvalue_cast(right));
    if (empty() || !root().son_[1]) {
        return end();
    } else {
        return iterator(root().son_[1].get());
    }
}

template <class T>
auto ReversalTree<T>::begin() -> iterator {
    if (empty()) {
        return end();
    }
    return iterator(&findNode(0));
}

template <class T>
auto ReversalTree<T>::begin() const -> const_iterator {
    if (empty()) {
        return end();
    }
    return const_iterator(&findNode(0));
}

template <class T>
auto ReversalTree<T>::cbegin() const -> const_iterator {
    if (empty()) {
        return cend();
    }
    return begin();
}

template <class T>
auto ReversalTree<T>::end() -> iterator {
    return iterator(&dummy_);
}

template <class T>
auto ReversalTree<T>::end() const -> const_iterator {
    return const_iterator(&dummy_);
}

template <class T>
auto ReversalTree<T>::cend() const -> const_iterator {
    return end();
}


template <class T>
template <bool IsConst>
typename ReversalTree<T>::template Iterator<IsConst>&
ReversalTree<T>::Iterator<IsConst>::operator++() {
    if (node_->dad_ == node_) {
        throw ("Calling operator++ for end iterator");
    }
    node_->push();
    if (node_->son_[1]) {
        node_ = node_->son_[1].get();
        node_->push();
        while (node_->son_[0]) {
            node_ = node_->son_[0].get();
            node_->push();
        }
    } else {
        while (node_->whichSon()) {
            node_ = node_->dad_;
        }
        node_ = node_->dad_;
    }
    return *this;
}

template <class T>
template <bool IsConst>
typename ReversalTree<T>::template Iterator<IsConst>&
ReversalTree<T>::Iterator<IsConst>::operator--() {
    node_->push();
    if (node_->son_[0]) {
        node_ = node_->son_[0].get();
        node_->push();
        while (node_->son_[1]) {
            node_ = node_->son_[1].get();
            node_->push();
        }
    } else {
        while (!node_->whichSon()) {
            node_ = node_->dad_;
            if (node_->dad_ == node_) {
                throw ("Calling operator-- for begin iterator");
            }
        }
        node_ = node_->dad_;
    }
    return *this;
}

template <class T>
template <bool IsConst>
auto ReversalTree<T>::Iterator<IsConst>::order() const -> size_type {
    size_type result = node_->leftSubtreeSize();
    Node* p = node_;
    while (p->dad_ != p->dad_->dad_) {
        if (p->whichSon()) {
            p = p->dad_;
            result += p->leftSubtreeSize() + 1;
        } else {
            p = p->dad_;
        }
    }
    return result;
}

} //namespace dsa

#endif //DSALGLIB_REVERSALTREE_H
