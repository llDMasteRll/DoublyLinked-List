#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <initializer_list>
#include <mutex>
#include <functional>

///STL
#include <array>
#include <list>
#include <deque>
#include <vector>

#include <map>
#include <set>

#include <stack>
#include <queue>
/// 


using namespace std;
using namespace chrono;
using namespace this_thread;

class Timer
{

    time_point<steady_clock> start, end;

public:
    Timer()
    {
        start = high_resolution_clock::now();
    }

    ~Timer()
    {
        end = high_resolution_clock::now();
        duration<double>duration = end - start;
        cout << "Time = " << duration.count()*10e6 << " s\n";
    }
};

template<class T>
class Tree
{
public:
    Tree() : Size(0), root(nullptr) {}
    Tree(initializer_list<T>Items)
    {
        for (auto c : Items)
            insert(c);
    }
    void insert(T data)
    {
        if (empty())
        {
            root = new Node<T>(data);
            ++Size;
        }
        else
        {
            Node<T>* parent = nullptr;
            Node<T>* current = root;

            while (current != nullptr)
            {
                parent = current;
                if (data < current->data)
                    current = current->left;
                else if (data > current->data)
                    current = current->right;
                else
                    return;
            }

            if (data < parent->data)
                parent->left = new Node<T>(data);
            else
                parent->right = new Node<T>(data);

            ++Size;
        }
    }

    void erase(T data)
    {
        Timer t;
        if (empty())
            return;

        Node<T>* parent = root;
        Node<T>* current = parent;

        while (current != nullptr)
        {
            if (data == current->data)
                break;

            parent = current;

            if (data < current->data)
                current = current->left;
            else if (data > current->data)
                current = current->right;
        }

        if (data < root->data)
        {
            if (data > parent->data)
            {
                if (current->left != nullptr)
                {
                    parent->right = current->left;
                    auto Connection = FindRightmost(current->left);
                    Connection->right = current->right;
                }
                else
                    parent->right = current->right;

                EraseElement(current);
            }
            else
            {
                if (current->right != nullptr)
                {
                    parent->left = current->right;
                    auto Connection = FindLeftmost(current->right);
                    Connection->left = current->left;
                }
                else
                    parent->left = current->left;

                EraseElement(current);
            }
        }
        else
        {
            if (data > parent->data)
            {
                if (current->left != nullptr)
                {
                    parent->right = current->left;
                    auto Connection = FindRightmost(current->left);
                    Connection->right = current->right;
                }
                else
                    parent->right = current->right;

                EraseElement(current);
            }
            else
            {
                if (current->right != nullptr)
                {
                    parent->left = current->right;
                    auto Connection = FindLeftmost(current->right);
                    Connection->left = current->left;
                }
                else
                    parent->left = current->left;

                EraseElement(current);
            }
        }
    }

    void Erase(T data)
    {
        Timer t2;
        bool LorR = 0;
        Node<T>* parent = root;
        Node<T>* current = parent;

        while (current != nullptr)
        {
            if (current->data == data)
            {
                if (LorR)
                {
                    if (current->left == nullptr)
                        parent->left = current->right;
                    else if (current->right == nullptr)
                        parent->left = current->left;
                    else
                    {
                        Node<T>* buffer = current->right;

                        while (buffer->left != nullptr)
                            buffer = buffer->left;

                        parent->left = current->right;
                        buffer->left = current->left;
                    }
                }
                else
                {
                    if (current->left == nullptr)
                        parent->right = current->right;
                    else if (current->right == nullptr)
                        parent->right = current->left;
                    else
                    {
                        Node<T>* buffer = current->left;

                        while (buffer->right != nullptr)
                            buffer = buffer->right;

                        parent->right = current->left;
                        buffer->right = current->right;
                    }
                }

                delete current;
                --Size;
                return;
            }

            parent = current;

            if (current->data > data)
            {
                current = current->left;
                LorR = 1;
            }
            else
            {
                current = current->right;
                LorR = 0;
            }

        }
    }
     
    pair<T, bool> find(T data)
    {
        if (!empty())
        {
            Node<T>* current = root;
            while (current != nullptr)
            {
                if (data == current->data)
                    return { current->data, true };
                else if (data < current->data)
                    current = current->left;
                else if (data > current->data)
                    current = current->right;
            }
            return { 0,false };
        }
    };

    void clear()
    {
        if(!empty())
            DeleteElements(root);
    }

    bool empty() { return root == nullptr; }
    int size() { return Size; }
    ~Tree() { clear(); }

private:
    template<class T>
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(T data = T(), Node* left = nullptr, Node* right = nullptr)
        {
            this->data = data;
            this->left = left;
            this->right = right;
        }
    };

    inline void EraseElement(Node<T>*& current)
    {
        delete current;
        current = nullptr;
        --Size;
    }
    bool DeleteElements(Node<T>*& current)
    {
        if (current->left != nullptr || current->right != nullptr)
        {   
            if (current->left != nullptr)
                DeleteElements(current->left);
            if (current->right != nullptr)
                DeleteElements(current->right);

            EraseElement(current);
            return false;
        }

        else
        {
            EraseElement(current);
            return false;
        }
    }

    Node<T>* FindLeftmost(Node<T>*& current)
    {
        if (current->left != nullptr)
            FindLeftmost(current->left);
        else
            return current;
    }
    Node<T>* FindRightmost(Node<T>*& current)
    {
        if (current->right != nullptr)
            FindRightmost(current->right);
        else
            return current;
    }

    size_t Size;
    Node<T>* root;
};

template<typename T>
class List
{
public:
    List() : Size(0), head(nullptr), tail(nullptr) {}
    List(initializer_list<T>& Items)
    {
        for (auto& c : Items)
        {
        }
    }

    T back() { }
    T front() { }
    size_t size() 
    { 
        return Size; 
    }
    bool empty() { }

    void push_front(T val)
    {

    }

    void emplace_front(T& data)
    {

    }

    void push_back(T val)
    {

    }

    void emplace_back(T& data)
    {

    }

    void pop_front()
    {

    }
       
    void pop_back()
    {

    }

    void insert(T val)
    {

    }
    void remove(T val)
    {

    }

    void remove_if(function<bool>_Pred)
    {

    }
    
    /*void erase()*/
    void sort()
    {

    }

    void unique()
    {

    }

    T At(const int index)
    {

    }

    T& operator[](const int index) const
    {

    }

    List& operator=(const List& Other)
    {

    }

    vector<T> _Get_container()
    {

    }

    list<T> _Get_container()
    {

    }

    deque<T> _Get_container()
    {

    }

    set<T> _Get_container()
    {

    }

    stack<T> _Get_container()
    {

    }

    queue<T> _Get_container()
    {

    }

private:
    template<typename T>
    struct Node
    {
        T val;
        Node* prev;
        Node* next;
        Node(T val = T(), Node* prev = nullptr, Node* next = nullptr)
        {
            this->val = val;
            this->prev = prev;
            this->next = next;
        }
    };

    size_t Size;
    Node<T>* head;
    Node<T>* tail;
};

void main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "ru");
    system("chcp 1251");
    system("cls");
    /*Tree<int>D({ 5, 4, 12, -2, 0, 9, 7, 20, 18, 118, 16, 19, 50, 120, -5 });
    Tree<int>A({ 5, 4, 12, -2, 0, 9, 7, 20, 18, 118, 16, 19, 50, 120, -5 });*/
    /*thread th([&]() { cout << "Andrew: "; Timer t; A.Erase(20); });
    sleep_for(20ms);
    thread th2([&]() { cout << "Denys: "; Timer t; D.erase(20); });
    th.join();
    th2.join();*/
    /*
    {
        Timer t;
        A.clear();
    }*/
    /*Tree<int>A;
    Tree<int>B;
    vector<int>V;
    for (int i = 0; i < 1000; i++)
        V.emplace_back(i);

    random_shuffle(V.begin(), V.end());

    for (auto c : V)
    {
        A.insert(c);
        B.insert(c);
    }

    {
        Timer t;
        A.erase(800);
    }

    {
        Timer t;
        B.Erase(800);
    }*/

    list<int>J{ 1,2,3,4,5,6,7,8,9,0 };

}



