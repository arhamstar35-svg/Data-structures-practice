#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int data[100];
    int priority[100];
    int size;

public:
    PriorityQueue() {
        size = 0;
    }

    // Insert an element
    void push(int value, int p) {
        if (size == 100) {
            cout << "Priority Queue is full." << endl;
            return;
        }

        int i = size;

        data[i] = value;
        priority[i] = p;

        size++;

        // Heapify Up
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (priority[parent] < priority[i]) {

                // Swap data
                int temp = data[parent];
                data[parent] = data[i];
                data[i] = temp;

                // Swap priorities
                temp = priority[parent];
                priority[parent] = priority[i];
                priority[i] = temp;

                i = parent;
            }
            else {
                break;
            }
        }
    }

    // Remove highest priority element
    void pop() {
        if (size == 0) {
            cout << "Priority Queue is empty." << endl;
            return;
        }

        // Replace root with last element
        data[0] = data[size - 1];
        priority[0] = priority[size - 1];

        size--;

        // Heapify Down
        int i = 0;

        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            int largest = i;

            if (left < size &&
                priority[left] > priority[largest]) {
                largest = left;
            }

            if (right < size &&
                priority[right] > priority[largest]) {
                largest = right;
            }

            if (largest != i) {

                // Swap data
                int temp = data[i];
                data[i] = data[largest];
                data[largest] = temp;

                // Swap priorities
                temp = priority[i];
                priority[i] = priority[largest];
                priority[largest] = temp;

                i = largest;
            }
            else {
                break;
            }
        }
    }

    // Return highest priority element
    int peek() {
        if (size == 0) {
            cout << "Priority Queue is empty." << endl;
            return -1;
        }

        return data[0];
    }

    // Display heap elements
    void display() {
        if (size == 0) {
            cout << "Priority Queue is empty." << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << "Data: " << data[i]
                 << ", Priority: " << priority[i] << endl;
        }
    }
};

int main() {

    PriorityQueue pq;

    pq.push(10, 2);
    pq.push(20, 5);
    pq.push(30, 3);
    pq.push(40, 8);
    pq.push(50, 4);

    cout << "Priority Queue:" << endl;
    pq.display();

    cout << "\nHighest Priority Element: "
         << pq.peek() << endl;

    pq.pop();

    cout << "\nAfter Removing Highest Priority:" << endl;
    pq.display();

    return 0;
}

