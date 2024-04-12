#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Bank {
private:
    int M; // Количество очередей
    std::vector<std::vector<int>> queues; // Очереди обслуживания

public:
    Bank(int num_queues) : M(num_queues) {
        queues.resize(M);
    }

    // Добавление клиента в случайную очередь
    void add_client(int client_number) {
        int random_queue = rand() % M; // Случайный выбор очереди
        queues[random_queue].push_back(client_number); // Добавление клиента в очередь
        std::cout << "Клиент " << client_number << " добавлен в очередь " << random_queue << std::endl;
    }

    // Обслуживание клиента из случайной очереди
    void serve_client() {
        if (all_queues_empty()) {
            std::cout << "Все очереди пусты" << std::endl;
            return;
        }

        int random_queue = rand() % M; // Случайный выбор очереди
        if (!queues[random_queue].empty()) {
            int served_client = queues[random_queue].front(); // Получение номера обслуженного клиента
            queues[random_queue].erase(queues[random_queue].begin()); // Удаление клиента из очереди
            std::cout << "Клиент " << served_client << " обслужен из очереди " << random_queue << std::endl;
        }
        else {
            std::cout << "Очередь " << random_queue << " пуста" << std::endl;
        }
    }

    // Проверка, все ли очереди пусты
    bool all_queues_empty() const {
        for (const auto& queue : queues) {
            if (!queue.empty()) {
                return false;
            }
        }
        return true;
    }

    // Вывод состояния очередей
    void print_queues() const {
        std::cout << "Состояние очередей:" << std::endl;
        for (int i = 0; i < M; ++i) {
            std::cout << "Очередь " << i << ": ";
            if (queues[i].empty()) {
                std::cout << "пуста";
            }
            else {
                for (int client : queues[i]) {
                    std::cout << client << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    int M = 3; // Количество очередей
    int N = 10; // Количество клиентов

    Bank bank(M);

    // Добавление клиентов
    for (int i = 1; i <= N; ++i) {
        bank.add_client(i);
    }

    // Обслуживание клиентов
    for (int i = 0; i < N; ++i) {
        bank.serve_client();
        bank.print_queues();
        std::cout << std::endl;
    }

    return 0;
}
