#include "includes.h"

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

    T back() { if (empty()) return tail; }

    T front() { if (empty()) return head; }

    size_t size() { return Size; }

    bool empty() { return head; }

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



