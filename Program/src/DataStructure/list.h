#ifndef LIST_H
#define LIST_H


template <typename T>
class List 
{
private:
    // Node structure for the linked list
    struct Node
    {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    unsigned int elements;

public:
    List() : head(nullptr), tail(nullptr), elements(0) {}
    
    ~List() {
        clear();
    }
    
    // Insert a new element at the start of the list
    void insertStart(const T& value) 
    {
        Node* newNode = new Node(value);
        if (isEmpty()) { // set the head and tail how the first element
            head = newNode; 
            tail = newNode;
        } else { 
            newNode->next = head;
            head = newNode;
        }
        elements++;
    }

    // Insert a new element at the end of the list
    void insertEnd(const T& value) 
    {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
        } else {
            tail->next = newNode; 
        }
        tail = newNode; 
        elements++;
    }

    // delete an element by their position.
    // Return true if success, retrun false if the position is invalid
    bool deleteByPosition(unsigned int position)
    {
        // Check if the list is empty or the position is invalid
        if (isEmpty() || position >= elements) {
            return false;
        }

        // Delete the head node for not having to traverse the list
        if(position == 0) 
        {
            Node* temp = head;
            head = head->next;
            
            if (head == nullptr) {
                tail = nullptr; // List is now empty
            }

            delete temp;
            elements--;
            return true;
        } 

        // Search for the node to delete
        Node* current = head;
        for (unsigned int i = 0; i < position - 1; ++i) 
        {
            current = current->next;
        }

        Node* temp = current->next;
        current->next = temp->next;

        // If the deleted node was the tail, update the tail pointer
        if (temp == tail) 
        {
            tail = current;
        }

        delete temp;
        elements--;
        return true;
    }

    // get the object by their position
    T* get(unsigned int position) {
        if (position >= elements) {
            return nullptr;
        }
        
        Node* current = head;
        for (unsigned int i = 0; i < position; i++) {
            current = current->next;
        }
        
        return &(current->data);
    }

    // Check if the list is empty
    bool isEmpty() const 
    {
        return elements == 0;
    }

    // Get the number of elements in the list
    unsigned int size() const {
        return elements;
    }

    // delete all elements in the list
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
        head = nullptr;
        tail = nullptr;
        elements = 0;
    }


};


#endif // LIST_H
