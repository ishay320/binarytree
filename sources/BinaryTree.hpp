#include <string>
#include <iostream>
#include <iterator>
#include <queue>

namespace ariel
{
    template <typename T>
    class node //private class
    {
    public:
        T data;
        node<T> *left;
        node<T> *right;
        node<T> *parent;
        node(T _data, node<T> *parent) : data(_data), left(nullptr), right(nullptr), parent(parent) {}
        // node(const node<T> &n) : data(n.data), left(n.left != nullptr ? new node<T>(*n.left) : nullptr),
        //                          right(n.right != nullptr ? new node<T>(*n.right) : nullptr),
        //                          parent(nullptr) { std::cout << "probe\n"; }
    };

    template <typename T>
    class iterator // for inheritance
    {
    protected:
    public:
        node<T> *n;
        std::queue<node<T> *> queue;
        //constructor
        iterator(){}
        iterator(node<T> *n) : n(n) {}
        ~iterator() {}
        // iterator(iterator<T>& i)noexcept{}
        // iterator(iterator<T>&& i)noexcept{}

        T &operator*() const { return n->data; }
        T *operator->() { return &n->data; }
        iterator &operator++()
        {
            if (queue.empty())
            {
                n = nullptr;
            }
            else
            {
                n = queue.front();
                queue.pop();
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            if (queue.empty())
            {
                n = nullptr;
            }
            else
            {
                n = queue.front();
                queue.pop();
            }
            return tmp;
        }
        bool operator==(const iterator &b)
        {
            if (b.n == nullptr)
            {
                return this->n == nullptr;
            }
            return this->n->data == b.n->data;
        };
        bool operator!=(const iterator &b)
        {
            if (b.n == nullptr)
            {
                return !(this->n == nullptr);
            }
            return !(this->n->data == b.n->data);
        };
        iterator &operator=(const iterator &b)
        {
            if (this == &b)
            {
                return *this;
            }

            this->n = b.n;
            this->queue = b.queue;
            return *this;
        }
        void insert(node<T> *n)
        {
            queue.push(n);
        }
    };

    template <typename T>
    class BinaryTree
    {
    public:
        //inorder iterator
        class inorder_iterator : public iterator<T>
        {
        public:
            inorder_iterator(node<T> *n) : iterator<T>(n)
            {
                recursive(n);
                this->operator++();
            }

        private:
            void recursive(node<T> *n)
            {
                if (n == nullptr)
                {
                    return;
                }
                recursive(n->left);
                iterator<T>::insert(n);
                recursive(n->right);
            }
        };
        //preorder iterator
        class preorder_iterator : public iterator<T>
        {
        public:
            preorder_iterator(node<T> *n) : iterator<T>(n)
            {
                recursive(n);
                this->operator++();
            }

        private:
            void recursive(node<T> *n)
            {
                if (n == nullptr)
                {
                    return;
                }
                iterator<T>::insert(n);
                recursive(n->left);
                recursive(n->right);
            }
        };
        // postorder iterator
        class postorder_iterator : public iterator<T>
        {
        public:
            postorder_iterator(node<T> *n) : iterator<T>(n)
            {
                recursive(n);
                this->operator++();
            }

        private:
            void recursive(node<T> *n)
            {
                if (n == nullptr)
                {
                    return void();
                }
                recursive(n->left);
                recursive(n->right);
                iterator<T>::insert(n);
            }
        };

    private:
        // binary tree objects
        node<T> *root = nullptr;

        void recDel(node<T> *n) //recursive deleting
        {
            if (n == nullptr)
            {
                return;
            }
            recDel(n->left);
            recDel(n->right);
            delete (n);
        }

        void deep_copy(node<T> *from, node<T> *to)
        {
            if (from == nullptr || to == nullptr)
            {
                return void();
            }
            if (from->left != nullptr)
            {
                node<T> *l = new node<T>(from->left->data, to);
                to->left = l;
                deep_copy(from->left, to->left);
            }
            if (from->right != nullptr)
            {
                node<T> *r = new node<T>(from->right->data, to);
                to->right = r;
                deep_copy(from->right, to->right);
            }
        }

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(BinaryTree<T> &tree) //copy constructor
        {
            if (root != nullptr)
            {
                recDel(root);
            }
            node<T> *r = new node<T>(tree.root->data, nullptr);
            root = r;
            deep_copy(tree.root, root);
        }
        BinaryTree(BinaryTree<T> &&tree) noexcept //move constructor
        {
            root = tree.root;
            tree.root = nullptr;
        }
        BinaryTree<T> &operator=(const BinaryTree<T> &b)
        {
            if (this != &b)
            {
                recDel(root);
                node<T> *r = new node<T>(b.root->data, nullptr);
                root = r;
                deep_copy(b.root, root);
            }
            return *this;
        }

        BinaryTree<T> &operator=(BinaryTree<T> &&b) noexcept
        {
            root = b.root;
            b.root = nullptr;
            return *this;
        }

        BinaryTree<T> &add_root(T data)
        {
            if (root == nullptr)
            {
                root = new node<T>{data, nullptr};
                return *this;
            }
            node<T> *tmp = new node<T>{data, nullptr};
            tmp->right = root->right;
            tmp->left = root->left;
            delete root;
            root = tmp;
            return *this;
        }
        BinaryTree<T> &add_left(T search, T data)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("there is no root for this tree");
            }
            node<T> *tmp = searchTree(search, root);
            if (tmp != nullptr)
            {
                if (tmp->left == nullptr)
                {
                    node<T> *tmpLeft = new node<T>{data, tmp};
                    tmp->left = tmpLeft;
                    return *this;
                }
                tmp->left->data = data;
                return *this;
            }
            throw std::invalid_argument("there is no such data in the tree");
        }
        BinaryTree<T> &add_right(T search, T data)
        {
            if (root == nullptr)
            {
                throw std::invalid_argument("there is no root for this tree");
            }
            node<T> *tmp = searchTree(search, root);
            if (tmp != nullptr)
            {
                if (tmp->right == nullptr)
                {
                    node<T> *tmpRight = new node<T>{data, tmp};
                    tmp->right = tmpRight;
                    return *this;
                }
                tmp->right->data = data;
                return *this;
            }
            throw std::invalid_argument("there is no such data in the tree");
        }
        friend std::ostream &operator<<(std::ostream &out, BinaryTree &b)
        { // need more oomff *(print inorder)
            for (auto i = b.begin(); i != b.end(); i++)
            {
                out << *i << " ";
            }
            return out;
        }
        preorder_iterator begin_preorder()
        {
            preorder_iterator iter(root);
            return iter;
        }
        preorder_iterator end_preorder()
        {
            return nullptr;
        }
        inorder_iterator begin_inorder()
        {
            inorder_iterator iter(root);
            return iter;
        }
        inorder_iterator end_inorder()
        {
            return nullptr;
        }
        postorder_iterator begin_postorder()
        {
            postorder_iterator iter(root);
            return iter;
        }
        postorder_iterator end_postorder()
        {
            return nullptr;
        }
        inorder_iterator begin()
        {
            inorder_iterator iter(root);
            return iter;
        }
        inorder_iterator end()
        {
            return nullptr;
        }
        node<T> *searchTree(T data, node<T> *n)
        {
            if (n == nullptr)
            {
                return nullptr;
            }

            if (n->data == data)
            {
                return n;
            }
            node<T> *r = searchTree(data, n->right);
            node<T> *l = searchTree(data, n->left);
            if (r != nullptr)
            {
                return r;
            }
            if (l != nullptr)
            {
                return l;
            }
            return nullptr;
        }
        ~BinaryTree()
        { //clear via iterator post
            recDel(root);
        }
    };
}