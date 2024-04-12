#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Bank {
private:
    int M; // ���������� ��������
    std::vector<std::vector<int>> queues; // ������� ������������

public:
    Bank(int num_queues) : M(num_queues) {
        queues.resize(M);
    }

    // ���������� ������� � ��������� �������
    void add_client(int client_number) {
        int random_queue = rand() % M; // ��������� ����� �������
        queues[random_queue].push_back(client_number); // ���������� ������� � �������
        std::cout << "������ " << client_number << " �������� � ������� " << random_queue << std::endl;
    }

    // ������������ ������� �� ��������� �������
    void serve_client() {
        if (all_queues_empty()) {
            std::cout << "��� ������� �����" << std::endl;
            return;
        }

        int random_queue = rand() % M; // ��������� ����� �������
        if (!queues[random_queue].empty()) {
            int served_client = queues[random_queue].front(); // ��������� ������ ������������ �������
            queues[random_queue].erase(queues[random_queue].begin()); // �������� ������� �� �������
            std::cout << "������ " << served_client << " �������� �� ������� " << random_queue << std::endl;
        }
        else {
            std::cout << "������� " << random_queue << " �����" << std::endl;
        }
    }

    // ��������, ��� �� ������� �����
    bool all_queues_empty() const {
        for (const auto& queue : queues) {
            if (!queue.empty()) {
                return false;
            }
        }
        return true;
    }

    // ����� ��������� ��������
    void print_queues() const {
        std::cout << "��������� ��������:" << std::endl;
        for (int i = 0; i < M; ++i) {
            std::cout << "������� " << i << ": ";
            if (queues[i].empty()) {
                std::cout << "�����";
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
    srand(time(0)); // ������������� ���������� ��������� �����

    int M = 3; // ���������� ��������
    int N = 10; // ���������� ��������

    Bank bank(M);

    // ���������� ��������
    for (int i = 1; i <= N; ++i) {
        bank.add_client(i);
    }

    // ������������ ��������
    for (int i = 0; i < N; ++i) {
        bank.serve_client();
        bank.print_queues();
        std::cout << std::endl;
    }

    return 0;
}
