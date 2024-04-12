#include <iostream>
#include <queue>

class Priority_Queue_Inclusion {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

public:
    // ������� �������� � �����������
    void enqueue(int value) {
        pq.push(value);
    }

    // ���������� �������� � ��������� �����������
    int dequeue() {
        if (pq.empty()) {
            std::cerr << "������� �����!" << std::endl;
            return -1; // ����� ������� ������ �������� �� ���������
        }
        int front = pq.top();
        pq.pop();
        return front;
    }

    // ��������, ����� �� �������
    bool is_empty() const {
        return pq.empty();
    }
};

class Priority_Queue_Exclusion {
private:
    std::priority_queue<int> pq;

public:
    // ������� �������� � �����������
    void enqueue(int value) {
        pq.push(value);
    }

    // ���������� �������� � ��������� �����������
    int dequeue() {
        if (pq.empty()) {
            std::cerr << "������� �����!" << std::endl;
            return -1; // ����� ������� ������ �������� �� ���������
        }
        int front = pq.top();
        pq.pop();
        return front;
    }

    // ��������, ����� �� �������
    bool is_empty() const {
        return pq.empty();
    }
};

int main() {
    Priority_Queue_Inclusion pq_inclusion;
    Priority_Queue_Exclusion pq_exclusion;

    // ������� ��������� � �����������
    pq_inclusion.enqueue(5);
    pq_inclusion.enqueue(3);
    pq_inclusion.enqueue(8);

    pq_exclusion.enqueue(10);
    pq_exclusion.enqueue(2);
    pq_exclusion.enqueue(7);

    // ���������� ��������� � �����������
    std::cout << "���������� ��������� �� ������� � ������������ ����������:" << std::endl;
    while (!pq_inclusion.is_empty()) {
        std::cout << pq_inclusion.dequeue() << " ";
    }
    std::cout << std::endl;

    std::cout << "���������� ��������� �� ������� � ������������ �����������:" << std::endl;
    while (!pq_exclusion.is_empty()) {
        std::cout << pq_exclusion.dequeue() << " ";
    }
    std::cout << std::endl;

    return 0;
}