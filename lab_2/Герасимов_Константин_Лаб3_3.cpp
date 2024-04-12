#include <iostream>
#include <vector>
#include <chrono>

void sieve_of_eratosthenes_array(int n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    // Вывод простых чисел
    std::cout << "Простые числа до " << n << " (решето на массивах): ";
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

void sieve_of_eratosthenes_linked_list(int n) {
    Node* head = new Node(2);
    Node* current = head;
    for (int i = 3; i <= n; ++i) {
        current->next = new Node(i);
        current = current->next;
    }

    Node* prime = head;
    while (prime != nullptr) {
        Node* next_prime = prime->next;
        Node* prev = prime;
        while (prev->next != nullptr) {
            if (prev->next->data % prime->data == 0) {
                Node* temp = prev->next;
                prev->next = prev->next->next;
                delete temp;
            }
            else {
                prev = prev->next;
            }
        }
        prime = next_prime;
    }

    // Вывод простых чисел
    std::cout << "Простые числа до " << n << " (решето на связанных списках): ";
    current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // Освобождаем память
    current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

int main() {
    int n = 100000; // Поиск простых чисел до n

    auto start_time_array = std::chrono::steady_clock::now();
    sieve_of_eratosthenes_array(n);
    auto end_time_array = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time_array = end_time_array - start_time_array;

    auto start_time_linked_list = std::chrono::steady_clock::now();
    sieve_of_eratosthenes_linked_list(n);
    auto end_time_linked_list = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time_linked_list = end_time_linked_list - start_time_linked_list;

    std::cout << "Время выполнения на массивах: " << elapsed_time_array.count() << " секунд" << std::endl;
    std::cout << "Время выполнения на связанных списках: " << elapsed_time_linked_list.count() << " секунд" << std::endl;

    return 0;
}