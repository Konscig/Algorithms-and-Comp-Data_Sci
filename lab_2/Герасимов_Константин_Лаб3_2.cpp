#include <iostream>
#include <chrono>
#include <vector>
// Реализация на массивах
int josephus_array(int n, int k) {
    std::vector<int> people(n);
    for (int i = 0; i < n; ++i) {
        people[i] = i + 1; // Присваиваем каждому человеку его номер в кругу
    }

    int index = 0;
    while (people.size() > 1) {
        index = (index + k - 1) % people.size(); // Вычисляем индекс убираемого человека
        people.erase(people.begin() + index); // Удаляем человека из массива
    }

    return people[0]; // Возвращаем номер последнего оставшегося человека
}
// Реализация связных списках
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

int josephus_linked_list(int n, int k) {
    Node* head = new Node(1); // Создаем первого человека
    Node* prev = head;
    for (int i = 2; i <= n; ++i) {
        prev->next = new Node(i); // Создаем остальных людей в круге
        prev = prev->next;
    }
    prev->next = head; // Связываем последнего человека с первым, чтобы получить кольцевой список

    Node* current = head;
    while (current->next != current) {
        // Перемещаемся на k-1 узлов вперед
        for (int i = 1; i < k - 1; ++i) {
            current = current->next;
        }
        // Удаляем следующий узел
        Node* next_node = current->next;
        current->next = next_node->next;
        delete next_node;
        // Перемещаемся на следующего узла
        current = current->next;
    }

    int winner = current->data;
    delete current; // Освобождаем память, выделенную под последний узел
    return winner;
}


int main() {
    int n = 10000; // Количество людей в круге
    int k = 3;     // Каждый третий человек убирается

    // Измеряем время выполнения реализации на массивах
    auto start_time_array = std::chrono::steady_clock::now();
    int josephus_winner_array = josephus_array(n, k);
    auto end_time_array = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time_array = end_time_array - start_time_array;
    std::cout << "Время выполнения на массивах: " << elapsed_time_array.count() << " секунд" << std::endl;

    // Измеряем время выполнения реализации на связанных списках
    auto start_time_linked_list = std::chrono::steady_clock::now();
    int josephus_winner_linked_list = josephus_linked_list(n, k);
    auto end_time_linked_list = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time_linked_list = end_time_linked_list - start_time_linked_list;
    std::cout << "Время выполнения на связанных списках: " << elapsed_time_linked_list.count() << " секунд" << std::endl;

    return 0;
}