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
        node *left;
        node *right;
        node *parent;
        node(T _data, node *parent) : data(_data), left(nullptr), right(nullptr), parent(parent) {}
    };

    template <typename T>
    class iterator // for inheritance
    {
    protected:
        node<T> *n;
        std::queue<node<T> *> queue;

    public:
        //constructor
        iterator(node<T> *n) : n(n) {}
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
                if (this->n == nullptr)
                {
                    return true;
                }
                return false;
            }
            return this->n->data == b.n->data;
        };
        bool operator!=(const iterator &b)
        {
            if (b.n == nullptr)
            {
                if (this->n == nullptr)
                {
                    return false;
                }
                return true;
            }
            return this->n->data != b.n->data;
        };
        iterator &operator=(const iterator &b)
        {
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
                    return;
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
                    return;
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
                    return;
                recursive(n->left);
                recursive(n->right);
                iterator<T>::insert(n);
            }
        };
    private:
        // binary tree objects
        node<T> *root;
        void recDel(node<T> *n)
        {
            if (n == nullptr)
            {
                return void();
            }
            recDel(n->left);
            recDel(n->right);
            delete (n);
        }

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree &add_root(T data)
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
        BinaryTree &add_left(T search, T data)
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
        BinaryTree &add_right(T search, T data)
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