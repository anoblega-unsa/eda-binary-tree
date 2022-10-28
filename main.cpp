
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<class T>
struct Node
{
    T m_data;
    Node *m_right;
    Node *m_left;

    Node(T data):m_data(data), m_right(nullptr), m_left(nullptr){}

    friend std::ostream &operator<<(std::ostream &os, Node<T> const &n) { 
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
struct BTS
{
    Node<T> *m_root;
    BTS():m_root(nullptr){}

    Node<T> * damInsert(Node<T>* current, T data, bool left=false){
        if(current==nullptr) return new Node<T>(data);
        if(left){
            current->m_left = damInsert(current->m_left, data, left);
        }else{
            current->m_right = damInsert(current->m_right, data, left);
        }
        return current;
    }

    void damInsert(T data, bool left = false){
        m_root = damInsert(m_root, data, left);
    }

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

    void dot(ofstream &file, Node<T>* current){
        if (current==nullptr)
        {
            return;
        }else{
            current->dot(file);
            dot(file, current->m_left);
            dot(file, current->m_right);
        }
    }


    Node<T>* insert(Node<T>* current, T data){
        if(current==nullptr) return new Node<T>(data);
        else{
            if(data < current->m_data){
                current->m_left = insert(current->m_left, data);
            }else if(data > current->m_data){
                current->m_right = insert(current->m_right, data);
            }
        }
        return current;
    }

    void insert(T data){
        m_root = insert(m_root, data);
    }

    Node<T>* find(Node<T>* current, T key){
        if(current==nullptr || current->m_data == key) return current;
        else if(key < current->m_data){
            return find(current->m_left, key);
        }
        return find(current->m_right, key);
    }

    Node<T>* find(T key){
        return find(m_root, key);
    }


    void inOrder(){
        // sin recursion
    }

    void preOrder(){
        //sin recursion
    }

    void PostOrder(){
        //sin recursion
    }
    
    void LevelTraverse(){
        //implementar
    }

    void deleteNode(T key){

    }
};


int main() {

    BTS<int> t1 = BTS<int>();

    t1.insert(8);
    t1.insert(1);
    t1.insert(5);
    t1.insert(3);
    t1.insert(7);
    t1.insert(20);
    
    t1.dot("tree.dot");

    return 0;
}