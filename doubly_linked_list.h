//!  Copyright [2017] <Copyright relldaXY>"

#include <cstdint>
#include <stdexcept>



namespace structures {

template<typename T>
//! Class DoublyLinkedList
/*!
 *  this is a list doubly linked by reference. It has functions like push, pop,  
 *  and some like that. 
*/
class DoublyLinkedList {
 public:
    DoublyLinkedList() {
        head = NULL;
        size_ = -1;
    }
    ~DoublyLinkedList() {
        clear();
    }
    //! method clear.
    /*!
        clean data by data using the method "pop front"
    */
    void clear() {
        while (!empty()) {
            pop_front();
        }
        size_ = -1;
    }
    //! method push back.
    /*!
        push data to last position of double linked list.
    */
    void push_back(const T& data) {
        Node* aux;
        Node* newNode = new Node(data);
        if (empty()) {
            head = newNode;
            size_ = 0;
        } else {
            aux = head;
            for (int i = 1; i <= size_; i++) {
                aux = aux->next();
            }
        aux->next(newNode);
        newNode->prev(aux);
        newNode->next(NULL);
        size_++;
        }
    }
    //! method push front.
    /*!
        push data to first position of double linked list.
    */
    void push_front(const T& data) {
        Node *newNode = new Node(data);
        if (empty()) {
            head = newNode;
            size_++;
        } else {
            Node* aux;
            aux = head;
            head = newNode;
            newNode->next(aux);
            aux->prev(newNode);
            size_++;
        }
    }
    //! method "insert".
    /*!
        to insert in position according by index.
    */
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > (size_ + 1)) {
            throw std::out_of_range("Invalid index");
        } else if (index == 0) {
            push_front(data);
        } else if (index == (size_+1)) {
            push_back(data);
        } else {
            Node *betweenNode = new Node(data);
            Node *previousIndexNode, *indexNode;
            indexNode = head;
            for (int i = 1; i <= index ; i++) {
                indexNode = indexNode->next();
            }
            previousIndexNode = indexNode->prev();
            betweenNode->next(indexNode);
            betweenNode->prev(previousIndexNode);
            previousIndexNode->next(betweenNode);
            indexNode->prev(betweenNode);
            size_++;
        }
    }
    //! method "insert_sorted".
    /*!
        to sort the element before insert
    */
    void insert_sorted(const T& data) {
        Node *current;
        int pos = 0;
        if (empty()) {
            push_front(data);
        } else {
            current = head;
            while (current->next() != NULL && data > current->data()) {
                current = current->next();
                pos++;
            }
            if (data > current->data()) {
                insert(data, (size_+1) );
            } else {
                insert(data, pos);
            }
        }
    }
     //! method "pop".
    /*!
        remove data by index.
    */
    T pop(std::size_t index) {
        T data;
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (index < 0 || index > size_) {
            throw std::out_of_range("Invalid Index");
        } else if (index == 0) {
            return pop_front();
        } else if (index == size_) {
            return pop_back();
        } else {
            Node *indexNode, *auxPrevious, *auxNext;
            indexNode = head;
            for (int i = 1; i <= index; i++) {
                    indexNode = indexNode->next();
                }
            auxPrevious = indexNode->prev();
            auxNext = indexNode->next();
            auxPrevious->next(auxNext);
            auxNext->prev(auxPrevious);
            data = indexNode->data();
            delete indexNode;
            size_--;
            return data;
        }
    }
    //! method "pop back".
    /*!
        remove data from the last position of list.
    */
    T pop_back() {
        T data;
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (size() == 1) {
            size_ = -1;
            data = head->data();
            delete head;
            return data;
        } else {
            Node *aux, *newLast;
            aux = head;
            for (int i = 1; i <= size_; i++) {
                aux = aux->next();
            }
            newLast = aux->prev();
            newLast->next(NULL);
            data = aux->data();
            delete aux;
            size_--;
            return data;
        }
    }
    //! method "pop front".
    /*!
        remove the data from the first position of list.
    */
    T pop_front() {
        T data;
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (size() == 1) {
            size_ = -1;
            data = head->data();
            delete head;
            return data;
        } else {
            Node *aux, *newHead;
            aux = head;
            data = aux->data();
            newHead = aux->next();
            newHead->prev(NULL);
            head = newHead;
            delete aux;
            size_--;
            return data;
        }
    }
    //! method "remove".
    /*!
        remove the reference from list by data .
    */
    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Empty List");
        } else if (size() == 1) {
            if (head->data() == data) {
                pop_front();
            } else {
                return;
            }
        } else {
            if (head->data() == data) {
                pop_front();
                return;
            } else {
                Node *dataNode, *auxPrevious, *auxNext, *aux;
                dataNode = head;
                for (int i = 0; i <= size_; i++) {
                    if (dataNode->data() == data) {
                        aux = dataNode;
                        auxPrevious = dataNode->prev();
                        auxNext = dataNode->next();
                        auxPrevious->next(auxNext);
                        auxNext->prev(auxPrevious);
                        delete aux;
                        size_--;
                        return;
                    }
                dataNode = dataNode->next();
                }
                return;
            }
        }
    }
    //! method empty.
    /*!
        verify if the list is empty.
    */
    bool empty() const {
        return size_ == -1;
    }
    //! method contains.
    /*!
        verify is a specific data is on list.
    */
    bool contains(const T& data) const {
        Node *current;
        if (empty()) {
            throw std::out_of_range("Empty list");
        } else {
            current = head;
            while (current->next() != NULL) {
                if (current->data() == data) {
                    return true;
                } else {
                    current = current->next();
                }
            }
            return false;
        }
    }
    //! method at.
    /*!
        to get reference by index.
    */
    T& at(std::size_t index) {
        if (index < 0 || index > size_) {
            throw std::out_of_range("Invalid index");
        } else if (index == 0) {
            return head->data();
        } else {
            Node* indexNode = head;
            for (int i = 1; i <= index; i++) {
                indexNode = indexNode->next();
            }
            return indexNode->data();
        }
    }
    //! method const at.
    /*!
        to get reference by index.
    */
    const T& at(std::size_t index) const {
        if (index < 0 || index > size_) {
            throw std::out_of_range("Invalid index");
        } else if (index == 0) {
            return head->data();
        } else {
            Node* indexNode = head;
            for (int i = 1; i <= index; i++) {
                indexNode = indexNode->next();
            }
            return indexNode->data();
        }
    }
    //! method find.
    /*!
        to find index by data.
    */
    std::size_t find(const T& data) const {
        Node* dataNode;
        if (empty()) {
            throw std::out_of_range("Empty list");
        } else {
            dataNode = head;
            for (int i = 0; i <= size_ ; i++) {
                if (dataNode->data() == data) {
                    return i;
                } else {
                    dataNode = dataNode->next();
                }
            }
        }
        return size();
    }
    //! method size.
    /*!
        to find out the size of list.
    */
    std::size_t size() const {
        return (size_ + 1);
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    std::size_t size_;
};

}  // namespace structures

