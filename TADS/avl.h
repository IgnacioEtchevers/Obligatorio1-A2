#pragma once
#include <cassert>
#include <stdexcept>

template <class T>
class avl {
private:
    struct avl_node {
        T data;
        int height = 1;
        avl_node* left = nullptr;
        avl_node* right = nullptr;

        avl_node(T data) {
            this->data = data;
        }
    };

    avl_node* root = nullptr;
    int count = 0;

    int height(avl_node* n) {
        if (n == nullptr) {
            return 0;
        };
        return n->height;
    }

    int max(int a, int b) {
        if (a > b){
            return a;
        };
        return b;
    }

    // -------- Rotaciones --------
    avl_node* leftRotation(avl_node* z) {
        avl_node* y = z->right;
        avl_node* yLeft = y->left;

        y->left = z;
        z->right = yLeft;

        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    avl_node* rightRotation(avl_node* z) {
        avl_node* y = z->left;
        avl_node* yRight = y->right;

        y->right = z;
        z->left = yRight;

        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    avl_node* leftRightRotation(avl_node* z) {
        z->left = leftRotation(z->left);
        return rightRotation(z);
    }

    avl_node* rightLeftRotation(avl_node* z) {
        z->right = rightRotation(z->right);
        return leftRotation(z);
    }

    avl_node* rebalance(avl_node* n) {
        int bF = height(n->left) - height(n->right);

        if (bF > 1) { // pesado izquierda
            if (height(n->left->right) > height(n->left->left)) {
                n = leftRightRotation(n);
            } else {
                n = rightRotation(n);
            }
        } else if (bF < -1) { // pesado derecha
            if (height(n->right->left) > height(n->right->right)) {
                n = rightLeftRotation(n);
            } else {
                n = leftRotation(n);
            }
        }
        return n;
    }

    avl_node* insert(T data, avl_node* n) {
        if (n == nullptr) {
            count++;
            return new avl_node(data);
        }

        if (data < n->data) {
            n->left = insert(data, n->left);
        } else if (data > n->data) {
            n->right = insert(data, n->right);
        } else {
            return n; // duplicado
        }

        n->height = 1 + max(height(n->left), height(n->right));
        return rebalance(n);
    }

    bool contains(T data, avl_node* n) {
        if (n == nullptr){
             return false;
        };
        if (data == n->data) {
            return true;
        };
        if (data < n->data) {
            return contains(data, n->left);
        } else {
            return contains(data, n->right);
        };
    }

    T get(T data, avl_node* n) {
        if (n == nullptr){
            throw std::runtime_error("No encontrado");
        };
        if (data == n->data) {
            return n->data;
        };
        if (data < n->data) {
            return get(data, n->left);
        } else {
            return get(data, n->right);
        };
    }

    T minNode(avl_node* n) {
        if (n->left != nullptr) {
            return minNode(n->left);
        };
        return n->data;
    }

    T maxNode(avl_node* n) {
        if (n->right != nullptr) {
            return maxNode(n->right);
        };
        return n->data;
    }

public:
    void insert(T data) {
        root = insert(data, root);
    }

    int size() {
        return count;
    }

    int getHeight() {
        return height(root);
    }

    bool contains(T data) {
        return contains(data, root);
    }

    T get(T data) {
        return get(data, root);
    }

    T min() {
        return minNode(root);
    }

    T max() {
        return maxNode(root);
    }
};
