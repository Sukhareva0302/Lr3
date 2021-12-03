#include <iostream>
using namespace std;

class Iterator
{
public:
    virtual int next() = 0;
    virtual bool has_next() = 0;
};

class Node //class of the element of the Tree
{
private:

public:
    int data; //data in the node
    Node* left; //pointer to the left node
    Node* right; //pointer to the right node
    Node(int intdata)
    {
        data = intdata; //the initialized data is set as the head
        left = NULL; //the left node is set as 'NULL', as there no next node
        right = NULL;//the right node is set as 'NULL', as there no next node
    }
};

class Stack
{
private:
    class elem
    {
    public:
        Node* data;
        elem* next;
        elem(Node* new_data)
        {
            data = new_data;
            next = NULL;
        }
    };
    elem* head;
public:
    Stack()
    {
        head = NULL;
    }
    void push(Node* data)
    {
        elem* tmp = new elem(data);
        elem* cur = head;
        head = tmp;
        head->next=cur;
    }
    void pop()
    {
        if (head == NULL)
        {
            throw out_of_range("No more elements");
        }
        else
        {
            elem* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    Node* top()
    {
        if (head == NULL)
        {
            throw out_of_range("Empty");
        }
        else
        {
            return head->data;
        }
    }
};

class Queue
{
private:
    class elem
    {
    public:
        Node* data;
        elem* next;
        elem(Node* new_data)
        {
            data = new_data;
            next = NULL;
        }
    };
    elem* head;
    elem* last;
public:
    Queue()
    {
        head = NULL;
        last = NULL;
    }
    void push(Node* data)
    {
        elem* tmp = new elem(data);
        if (head == NULL)
        {
            head = tmp;
            last = tmp;
        }
        else
        {
            last->next = tmp;
            last = tmp;
        }
    }
    void pop()
    {
        if (head == NULL)
        {
            throw out_of_range("No more elements");
        }
        else
        {
            elem* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    Node* top()
    {
        if (head == NULL)
        {
            throw out_of_range("Empty");
        }
        else
        {
            return head->data;
        }
    }
};

class Tree {
private:
    Node* root; //beginning of the Tree
    bool search_data(int data, Node*& cur) //help to check if Tree has element with this data
    {
        if (cur != NULL)
        {
            if (cur->data != data)
            {
                if (cur->data > data)
                {
                    search_data(data, cur->left);
                }
                else
                {
                    search_data(data, cur->right);
                }
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    Node* search_prev_for_remove(int data, Node*& cur)
    {
        if ((cur->left != NULL)&&(cur->right != NULL))
        {

            if ((cur->left->data != data)&&(cur->right->data!=data))
            {
                if (cur->data > data)
                {
                    search_prev_for_remove(data, cur->left);
                }
                else
                {
                    search_prev_for_remove(data, cur->right);
                }
            }
            else
            {
                return cur;
            }
        }
        else
        {
            if (cur->left != NULL)
            {
                if(cur->left->data!=data)
                {
                    search_prev_for_remove(data, cur->left);
                }
                else
                {
                    return cur;
                }

            }
            else
            {
                if (cur->right != NULL)
                {
                    if (cur->right->data != data)
                    {
                        search_prev_for_remove(data, cur->right);
                    }
                    else
                    {
                        return cur;
                    }
                }
            }
        }
    }
    Node* search_for_remove(int data, Node*& cur)
    {
        if (cur != NULL)
        {
            if (cur->data != data)
            {
                if (cur->data > data)
                {
                    search_for_remove(data, cur->left);
                }
                else
                {
                    search_for_remove(data, cur->right);
                }
            }
            else
            {
                return cur;
            }
        }
        else
        {
            return NULL;
        }
    }
    Node* find_left_for_remove(Node* cur)
    {
        while (cur->left != NULL)
        {
            cur = cur->left;
        }
        return cur;
    }
public:
    Tree() //start of the new Tree
    {
        root = NULL;
    }
    bool search(int data) //checks if Tree has element with this data
    {
        return search_data(data, root);
    }
    void insert(int data) //inserts element in proper place in the Tree
    {
        Node** cur = &root; //current = (root adres)
        while ((*cur) != NULL)
        {
            Node& node = **cur;
            if (data <= node.data)
            {
                cur = &(node.left);
            }
            else
            { 
                cur = &(node.right);
            }
        }
        *cur = new Node(data);
    }
    void remove(int data) //removes element with this data from the Tree
    {
        if (root->data == data)
        {
            if ((root->left == NULL) && (root->right == NULL))
            {
                delete root;
                root = NULL;
            }
            else
            {
                if (root->right != NULL)
                {
                    Node* leftmost = find_left_for_remove(root->right);
                    Node* prev = search_prev_for_remove(leftmost->data, root);
                    root->data = leftmost->data;
                    if ((prev->left) == (leftmost))
                    {
                        if (leftmost->right == NULL)
                        {
                            prev->left = NULL;
                        }
                        else
                        {
                            prev->left = leftmost->right;
                        }
                        delete leftmost;
                    }
                    else
                    {
                        if (leftmost->right == NULL)
                        {
                            prev->right = NULL;
                        }
                        else
                        {
                            prev->right = leftmost->right;
                        }
                        delete leftmost;
                    }
                }
                else
                {
                    Node* tmp=root;
                    root = root->left;
                    delete tmp;
                }
            }
        }
        else
        {Node* removable = search_for_remove(data, root);
        if (removable != NULL)
        {
            if ((removable->left == NULL) && (removable->right == NULL))
            {
                Node* prev = search_prev_for_remove(data, root);
                if (prev->left == removable)
                {
                    prev->left = NULL;
                    delete removable;
                }
                else
                {
                    prev->right = NULL;
                    delete removable;
                }
            }
            else
            {
                if (removable->right != NULL)
                {
                    Node* leftmost = find_left_for_remove(removable->right);
                    Node* prev = search_prev_for_remove(leftmost->data, root);
                    removable->data = leftmost->data;
                    if ((prev->left) == (leftmost))
                    {
                        if (leftmost->right == NULL)
                        {
                            prev->left = NULL;
                        }
                        else
                        {
                            prev->left = leftmost->right;
                        }
                        delete leftmost;
                    }
                    else
                    {
                        if (leftmost->right == NULL)
                        {
                            prev->right = NULL;
                        }
                        else
                        {
                            prev->right = leftmost->right;
                        }
                        delete leftmost;
                    }
                }
                else
                {
                    Node* prev = search_prev_for_remove(removable->data, root);
                    if (prev->left == removable)
                    {
                        prev->left = removable->left;
                        delete removable;
                    }
                    else
                    {
                        prev->right = removable->left;
                        delete removable;
                    }
                }
            }
        }
        else
        {
            throw invalid_argument("Not found element with this data\n");
        }
        }
    }
    Iterator* create_dft_iterator(); //creates iterator for depth-first traverse
    Iterator* create_bft_iterator(); //creates iterator for breadth-first traverse
    class dft_iterator : public Iterator
    {
    public:
        dft_iterator(Node* start);
        bool has_next() override;
        int next() override;
    private:
        Node* cur; //current
        Stack* stack;
    };
    class bft_iterator : public Iterator
    {
    public:
        bft_iterator(Node* start);
        bool has_next() override;
        int next() override;
    private:
        Node* cur; //current
        Queue* queue;
    };
};

Iterator* Tree::create_dft_iterator()
{
    return new dft_iterator(root);
}

Tree::dft_iterator::dft_iterator(Node* start)
{
    cur = start;
    stack = new Stack();
}

int Tree::dft_iterator::next()
{
    if (!has_next())
    {
        throw out_of_range("No more elements");
    }
    int tmp = cur->data;
    if (cur->right != NULL)
    {
        stack->push(cur->right);
    }
    if (cur->left != NULL)
    {
        cur = cur->left;
    }
    else
    {
        try
        {
            cur = stack->top();
            stack->pop();
        }
        catch(out_of_range)
        {
            cur = NULL;
        }
    }
    return tmp;
}

bool Tree::dft_iterator::has_next()
{
    return cur != NULL;
}


Iterator* Tree::create_bft_iterator()
{
    return new bft_iterator(root);
}

Tree::bft_iterator::bft_iterator(Node* start)
{
    cur = start;
    queue = new Queue();
}

int Tree::bft_iterator::next()
{
    if (!has_next())
    {
        throw out_of_range("No more elements");
    }
    int tmp = cur->data;
    if (cur->left != NULL)
    {
        queue->push(cur->left);
    }
    if (cur->right != NULL)
    {
        queue->push(cur->right);
    }
    try
    {
        cur=queue->top();
        queue->pop();
    }
    catch (out_of_range)
    {
        cur = NULL;
    }
    return tmp;
}

bool Tree::bft_iterator::has_next()
{
    return cur != NULL;
}

int main()
{
    Tree head;
    cout << "inserted values: 8, 3, 6, 2, 10, 1, 14, 7\n\n";
    head.insert(8);
    head.insert(3);
    head.insert(6);
    head.insert(2);
    head.insert(10);
    head.insert(1);
    head.insert(14);
    head.insert(7);
    Iterator* dft;
    Iterator* bft;
    dft = head.create_dft_iterator();
    bft = head.create_bft_iterator();
    cout << "Depth-first traverse:" << endl;
    while (dft->has_next())
    {
        cout << dft->next() << " ";
    }
    cout << "\n\nBreadth-first traverse:" << endl;
    while (bft->has_next())
    {
        {
            cout << bft->next() << " ";
        }
    }
    cout << "\n\nDeleted values:3, 14\n\n";
    head.remove(3);
    head.remove(14);
    dft = head.create_dft_iterator();
    bft = head.create_bft_iterator();
    cout << "Depth-first traverse:" << endl;
    while (dft->has_next())
    {
        cout << dft->next() << " ";
    }
    cout << "\n\nBreadth-first traverse:" << endl;
    while (bft->has_next())
    {
        {
            cout << bft->next() << " ";
        }
    }
    cout << "\n\nIs there element 9 in the Tree?\n";
    if (head.search(9))
    {
        cout << "yes" << endl;
    }
    else
        cout << "no" << endl;
    cout << "\n\nIs there element 6 in the Tree?\n";
    if (head.search(6))
    {
        cout << "yes" << endl;
    }
    else
        cout << "no" << endl;
}