// Implementation of splay tree on implicit key.  Emulates sequence of elements.
// Supports concatenating (merging), splitting and reversing sequences with
// log(n) complexity on average.

#ifndef DSALGLIB_REVERSALTREE_H
#define DSALGLIB_REVERSALTREE_H

#include <stdint.h>
#include <string>
#include <array>
#include <memory>
#include <iterator>
#include <type_traits>


#define STR_DETAIL(x) #x
#define STR(x) STR_DETAIL(x)
#if defined(DEBUG)
#define EXPECTS(cond) if (!(cond))\
throw std::runtime_error("Precondition failure at " __FILE__ ":"\
                         STR(__LINE__));
#else
#define EXPECTS(cond)
#endif

namespace dsa {

template <class T, class... Ts>
std::unique_ptr<T> make_unique(Ts&&... ts) {
    return std::unique_ptr<T>(new T(std::forward<Ts&&>(ts)...));
}

template<class T, class U = T>
T exchange(T& obj, U&& new_value)
{
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}

template<bool B, class T, class F>
struct conditional {
    typedef T type;
};

template<class T, class F>
struct conditional<false, T, F> {
    typedef F type;
};

template <bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

template <class T>
class ReversalTree {
    public:
        template <bool IsConst>
        class Iterator;

        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = Iterator<false>;
        using const_iterator = Iterator<true>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    private:
        class Node;

    public:
        ReversalTree() {}
        ReversalTree(const ReversalTree&) = delete;
        ReversalTree(ReversalTree&&);

        template <class ForwardIterator>
        ReversalTree(ForwardIterator begin, ForwardIterator end);

        ReversalTree(std::initializer_list<T> ilist) : ReversalTree(ilist.begin(),
                                                              ilist.end()) {}

        ReversalTree& operator=(const ReversalTree&) = delete;
        ReversalTree& operator=(ReversalTree&&);

        bool empty() const noexcept {
            return !dummy_.son_[0];
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

        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        const_reverse_iterator crend() const;

    private:
        Node& root() const {
            return *(dummy_.son_[0]);
        }

        bool isRoot(const Node& node) const {
            return node.dad_ == node.dad_->dad_;
        }

        template <class ForwardIterator>
        std::unique_ptr<Node> buildTree(ForwardIterator, ForwardIterator);

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
        explicit Node(T data = T()) : data_(std::move(data)) {
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
            using std::swap;
            if (reverse_) {
                swap(son_[0], son_[1]);
                for (bool dir : {0, 1}) {
                    if (son_[dir]) {
                        son_[dir]->reverse_ ^= 1;
                    }
                }
                reverse_ = false;
            }
        }

        void link(std::unique_ptr<Node>&& son, bool dir) {
            son_[dir] = std::move(son);
            if (son_[dir]) {
                son_[dir]->dad_ = this;
            }
            updateSubtreeSize();
        }

    public:
        T data_;
        std::array<std::unique_ptr<Node>, 2> son_;
        Node* dad_;
        typename ReversalTree<T>::size_type subtree_size_ = 1;
        bool reverse_ = false;
};

template <class T>
template <bool IsConst>
class ReversalTree<T>::Iterator :
        public std::iterator<std::forward_iterator_tag, T> {
    friend class ReversalTree<T>;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ReversalTree::value_type;
        // using difference_type = std::allocator<T>::difference_type;
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
auto ReversalTree<T>::buildTree(ForwardIterator begin,
                             ForwardIterator end) -> std::unique_ptr<Node> {
    const auto dist = std::distance(begin, end);
    if (dist == 0) {
        return nullptr;
    }
    if (dist == 1) {
        return make_unique<Node>(*begin);
    }
    auto mid = begin;
    std::advance(mid, dist / 2);
    auto result = make_unique<Node>(*mid);
    result->link(buildTree(begin, mid), 0);
    result->link(buildTree(++mid, end), 1);
    return result;
}

template <class T>
void ReversalTree<T>::clear() {
    dummy_.son_[0] = nullptr;
    dummy_.updateSubtreeSize();
}

template <class T>
void ReversalTree<T>::swap(ReversalTree<T>& rhs) noexcept {
    using std::swap;
    swap(rhs.dummy_.son_[0], dummy_.son_[0]);
    if (dummy_.son_[0]) {
        dummy_.son_[0]->dad_ = &dummy_;
    }
    if (rhs.dummy_.son_[0]) {
        rhs.dummy_.son_[0]->dad_ = &rhs.dummy_;
    }
    dummy_.updateSubtreeSize();
    rhs.dummy_.updateSubtreeSize();
}

template <class T>
void ReversalTree<T>::rotate(Node& u) {
    if (&u == &dummy_ || isRoot(u)) {
        throw std::runtime_error("Attempt to rotate root");
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
    Node* p = &root();
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
        throw std::out_of_range(std::string("Index ") + std::to_string(i) +
                                " is greater than size() which is " +
                                std::to_string(size()));
    }
    splay(findNode(i));
    return root().data_;
}

template <class T>
auto ReversalTree<T>::at(size_type i) const -> const_reference {
    if (i >= size()) {
        throw std::out_of_range(std::string("Index ") + std::to_string(i) +
                                " is greater than size() which is " +
                                std::to_string(size()));
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
    } catch (std::runtime_error) {
        return std::move(*this);
    }
    splay(*prev.node_);
    ReversalTree<T> result;
    result.dummy_.link(std::move(root().son_[1]), 0);
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
    root().link(std::move(rhs.dummy_.son_[0]), 1);
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
        throw std::runtime_error(std::string("Invalid range: [") +
                                 std::to_string(first) +
                                 ", " + std::to_string(last) + ")");
    }
    if (last > size()) {
        throw std::out_of_range(std::string("last index is ") +
                                std::to_string(last) +
                                " which is greater than size() which is " +
                                std::to_string(size()));
    }
    auto right = split(last);
    auto center = split(first);
    center.reverseTree();
    merge(std::move(center));
    merge(std::move(right));
}

template <class T>
auto ReversalTree<T>::insert(const_iterator it, T e) -> iterator {
    Node* new_node = nullptr;
    if (!it.node_->son_[0]) {
        it.node_->link(make_unique<Node>(std::move(e)), 0);
        new_node = it.node_->son_[0].get();
    } else {
        Node* p = it.node_->son_[0].get();
        while (p->son_[1]) {
            p = p->son_[1].get();
        }
        p->link(make_unique<Node>(std::move(e)), 1);
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
    merge(std::move(right));
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
auto ReversalTree<T>::rbegin() -> reverse_iterator {
    return reverse_iterator(end());
}

template <class T>
auto ReversalTree<T>::rbegin() const -> const_reverse_iterator {
    return const_reverse_iterator(end());
}

template <class T>
auto ReversalTree<T>::crbegin() const -> const_reverse_iterator {
    return const_reverse_iterator(end());
}

template <class T>
auto ReversalTree<T>::rend() -> reverse_iterator {
    return reverse_iterator(begin());
}

template <class T>
auto ReversalTree<T>::rend() const -> const_reverse_iterator {
    return const_reverse_iterator(begin());
}

template <class T>
auto ReversalTree<T>::crend() const -> const_reverse_iterator {
    return const_reverse_iterator(begin());
}


template <class T>
template <bool IsConst>
ReversalTree<T>::Iterator<IsConst>&
ReversalTree<T>::Iterator<IsConst>::operator++() {
    if (node_->dad_ == node_) {
        throw std::runtime_error("Calling operator++ for end iterator");
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
ReversalTree<T>::Iterator<IsConst>&
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
                throw std::runtime_error(
                        "Calling operator-- for begin iterator");
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
