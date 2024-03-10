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
        if (!empty())
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