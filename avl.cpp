
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template<class T>
struct AVLNode
{
    T m_data;
    AVLNode *m_right;
    AVLNode *m_left;
    int m_height;

    AVLNode(T data):m_data(data), m_right(nullptr), m_left(nullptr), m_height(1){}

    friend std::ostream &operator<<(std::ostream &os, AVLNode<T> const &n) { 
        return os << n.m_data;
    }

    void dot(ostream &file){
        file<<"node_"<<m_data<<" [label = \"<l> | <m> "<< m_data <<" | <r>\"];\n";
        if(m_left){
            file<<"node_"<<m_data<<":l -> node_"<<m_left->m_data<<":m;\n";
        }
        if(m_right){
            file<<"node_"<<m_data<<":r -> node_"<<m_right->m_data<<":m;\n";
        }
    }
};


template<class T>
struct AVLTree
{
    AVLNode<T> *m_root;
    AVLTree():m_root(nullptr){}



    // Plotting a Tree
    void dot(string filename){
        ofstream mydot;
        mydot.open(filename, ios::out);

        mydot << "digraph g {\n";
        mydot << "node [shape=record, height=0.1];\n";
        dot(mydot, m_root);
        mydot << "}";
        mydot.close();
    }

    void dot(ofstream &file, AVLNode<T>* current){
        if (current==nullptr)
        {
            return;
        }else{
            current->dot(file);
            dot(file, current->m_left);
            dot(file, current->m_right);
        }
    }


    int height(AVLNode<T> *node){
        if(node==nullptr) return 0;
        return node->m_height;
    }

    // left -> right
    AVLNode<T>* rightRotation(AVLNode<T>* current){
        AVLNode<T>* temp = current->m_left;
        current->m_left = temp->m_right;
        temp->m_right = current;
        current->m_height = max(height(current->m_left), height(current->m_right)) + 1;
        temp->m_height = max(height(temp->m_left), current->m_height) + 1;

        return temp;
    }

    // right -> left
    AVLNode<T>* leftRotation(AVLNode<T>* current){
        AVLNode<T>* temp = current->m_right;
        current->m_right = temp->m_left;
        temp->m_left = current;
        current->m_height = max(height(current->m_left), height(current->m_right)) + 1;
        temp->m_height = max(height(temp->m_right), current->m_height) + 1;

        return temp;
    }

    int get_balance(AVLNode<T> *current)
    {
        if(current==nullptr) return 0;
        return height(current->m_left) - height(current->m_right);
    }


    AVLNode<T>* insert(AVLNode<T>* current, T data){
        if(current==nullptr) return new AVLNode<T>(data);
        if(data < current->m_data)
            current->m_left = insert(current->m_left, data);
        else if(data > current->m_data)
            current->m_right = insert(current->m_right, data);
        else
            return current;

        current->m_height = max(height(current->m_left), height(current->m_right)) + 1;
        int factor = get_balance(current);
        if(factor > 1){ // izquierda es mayor
            if( data < current->m_left->m_data) return rightRotation(current);
            else if (data > current->m_left->m_data) 
            {
                current->m_left = leftRotation(current->m_left);
                return rightRotation(current);
            }
        }
        if(factor < -1){ // derecha es mayor
            if( data > current->m_right->m_data) return leftRotation(current);
            else if (data > current->m_right->m_data) 
            {
                current->m_right = rightRotation(current->m_right);
                return leftRotation(current);
            }
        }
        return current;
    }

    void insert(T data){
        m_root = insert(m_root, data);
    }
    
    AVLNode<T>* maxNode(AVLNode<T>* current){
        if(current==nullptr || current->m_right==nullptr) return current;
        return maxNode(current->m_right);
    }

    AVLNode<T>* deleteNode(AVLNode<T>* current, T key){
        if(current==nullptr) return current;

        if(key < current->m_data){
            current->m_left = deleteNode(current->m_left, key);
        }else if(key > current->m_data){
            current->m_right = deleteNode(current->m_right, key);
        } else {
            if (current->m_left == nullptr){
                AVLNode<T>* temp = current->m_right;
                free(current);
                current = temp;
            }else if(current->m_right == nullptr){
                AVLNode<T>* temp = current->m_left;
                free(current);
                current = temp;
            }else {
                AVLNode<T>* temp = maxNode(current->m_left);

                current->m_data = temp->m_data;
                current->m_left = deleteNode(current->m_left, temp->m_data);
            }
        }

        if(current==nullptr)
            return current;

        // balance ...
        current->m_height = max(height(current->m_left), height(current->m_right)) + 1;
        int factor = get_balance(current);
        if(factor > 1){ // izquierda es mayor
            if( get_balance(current->m_left) >= 0) return ;
            else 
            {

            }
        }
        if(factor < -1){ // derecha es mayor
            if( get_balance(current->m_right) <= 0) return ;
            else
            {

            }
        }
        return current;
    }

    AVLNode<T>* find(AVLNode<T>* current, T key){
        if(current==nullptr || current->m_data == key) return current;
        else if(key < current->m_data){
            return find(current->m_left, key);
        }
        return find(current->m_right, key);
    }

    AVLNode<T>* find(T key){
        return find(m_root, key);
    }


};


int main() {

    AVLTree<int> t1 = AVLTree<int>();

    t1.insert(20);
    t1.insert(8);
    t1.insert(1);
    t1.insert(45);
    t1.insert(50);
    // t1.insert(7);
    // t1.insert(15);
    // t1.insert(50);
    // t1.insert(35);
    t1.insert(60);


    
    t1.dot("tree.dot");

    

    return 0;
}