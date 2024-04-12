#include <iostream>
#include <chrono>
#include <vector>
// ���������� �� ��������
int josephus_array(int n, int k) {
    std::vector<int> people(n);
    for (int i = 0; i < n; ++i) {
        people[i] = i + 1; // ����������� ������� �������� ��� ����� � �����
    }

    int index = 0;
    while (people.size() > 1) {
        index = (index + k - 1) % people.size(); // ��������� ������ ���������� ��������
        people.erase(people.begin() + index); // ������� �������� �� �������
    }

    return people[0]; // ���������� ����� ���������� ����������� ��������
}
// ���������� ������� �������
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

int josephus_linked_list(int n, int k) {
    Node* head = new Node(1); // ������� ������� ��������
    Node* prev = head;
    for (int i = 2; i <= n; ++i) {
        prev->next = new Node(i); // ������� ��������� ����� � �����
        prev = prev->next;
    }
    prev->next = head; // ��������� ���������� �������� � ������, ����� �������� ��������� ������

    Node* current = head;
    while (current->next != current) {
        // ������������ �� k-1 ����� ������
        for (int i = 1; i < k - 1; ++i) {
            current = current->next;
        }
        // ������� ��������� ����
        Node* next_node = current->next;
        current->next = next_node->next;
        delete next_node;
        // ������������ �� ���������� ����
        current = current->next;
    }

    int winner = current->data;
    delete current; // ����������� ������, ���������� ��� ��������� ����
    return winner;
}


int main() {
    int n = 10000; // ���������� ����� � �����
    int k = 3;     // ������ ������ ������� ���������

    // �������� ����� ���������� ���������� �� ��������
    auto start_time_array = std::chrono::steady_clock::now();
    int josephus_winner_array = josephus_array(n, k);
    auto end_time_array = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time_array = end_time_array - start_time_array;
    std::cout << "����� ���������� �� ��������: " << elapsed_time_array.count() << " ������" << std::endl;

    // �������� ����� ���������� ���������� �� ��������� �������
    auto start_time_linked_list = std::chrono::steady_clock::now();
    int josephus_winner_linked_list = josephus_linked_list(n, k);
    auto end_time_linked_list = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time_linked_list = end_time_linked_list - start_time_linked_list;
    std::cout << "����� ���������� �� ��������� �������: " << elapsed_time_linked_list.count() << " ������" << std::endl;

    return 0;
}