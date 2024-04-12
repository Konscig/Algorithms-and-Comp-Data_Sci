#include <iostream>
#include <stdexcept>

// Герасимов Константин П-22.02 Вариант 4 Задания 1-6

struct Node {
    int value;
    Node* next;
};

struct List {
    Node* first;
};

class ListStuff {
public:
    static void add_first(List* list, int value) {
        Node* node = new Node();
        node->next = list->first;
        node->value = value;
        list->first = node;
    }

    static void delete_first(List* list) {
        if (list->first == nullptr) {
            throw std::runtime_error("нельзя удалить первый элемент из пустого списка");
        }
        list->first = list->first->next;
    }

    static void print(List* list) {
        bool first = true;
        for (Node* node = list->first; node != nullptr; node = node->next) {
            if (!first) {
                std::cout << " ";
            }
            first = false;
            std::cout << node->value;
        }
        std::cout << std::endl;
    }

    static void dummy_delete_after(List* list, Node* node) {
        // Необходима реализация для удаления элемента после указанного узла
    }

    static void Debug() {
        List* list = new List();
        print(list); // пустая строка
        add_first(list, 3);
        add_first(list, 2);
        add_first(list, 1);
        print(list); // 1 2 3

        // пример использования метода с параметром типа Node
        // dummy_delete_after(list, list->first->next->next);

        delete_first(list);
        print(list); // 2 3

        delete_first(list);
        delete_first(list);
        // сейчас list пустой
        // попробуем удалить первый элемент из пустого списка
        try {
            delete_first(list);
        }
        catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl; // нельзя удалить первый элемент из пустого списка
        }

        // тут вы проверяете работоспособность написанного кода
        delete list;
    }

    static void print_reverse(Node* node) {
        if (node == nullptr) {
            return;
        }
        print_reverse(node->next);
        std::cout << node->value << " ";
    }

    static void print_reversed(List* list) {
        print_reverse(list->first);
        std::cout << std::endl;
    }

    static void add_last(List* list, int value) {
        Node* new_node = new Node();
        new_node->value = value;
        new_node->next = nullptr; // Новый узел будет последним, поэтому следующий узел - nullptr

        // Если список пуст, новый узел становится первым узлом списка
        if (list->first == nullptr) {
            list->first = new_node;
            return;
        }

        // Находим последний узел списка
        Node* last_node = list->first;
        while (last_node->next != nullptr) {
            last_node = last_node->next;
        }

        // Присоединяем новый узел к последнему узлу
        last_node->next = new_node;
    }

    static void delete_last(List* list) {
        if (list->first == nullptr) {
            // Список пуст, ничего удалять
            return;
        }

        if (list->first->next == nullptr) {
            // Список содержит только один элемент
            delete list->first;
            list->first = nullptr;
            return;
        }

        // Находим предпоследний узел списка
        Node* second_last_node = list->first;
        while (second_last_node->next->next != nullptr) {
            second_last_node = second_last_node->next;
        }

        // Удаляем последний узел
        delete second_last_node->next;
        second_last_node->next = nullptr; // Устанавливаем указатель на следующий узел предпоследнего узла в nullptr
    }

    static List* copy(List* original) {
        List* copied_list = new List();
        if (original->first == nullptr) {
            // Если оригинальный список пуст, возвращаем пустую копию
            return copied_list;
        }

        // Создаем копию первого элемента оригинального списка
        Node* original_node = original->first;
        Node* copied_node = new Node();
        copied_node->value = original_node->value;
        copied_node->next = nullptr;
        copied_list->first = copied_node;

        // Продолжаем копировать остальные элементы списка
        while (original_node->next != nullptr) {
            original_node = original_node->next;
            copied_node->next = new Node();
            copied_node = copied_node->next;
            copied_node->value = original_node->value;
            copied_node->next = nullptr;
        }

        return copied_list;
    }

    static void delete_before(List* list, Node* target_node) {
        // Если список пуст или если целевой узел является первым узлом, то нечего удалять
        if (list->first == nullptr || target_node == list->first) {
            return;
        }

        // Если целевой узел является вторым узлом списка
        if (list->first->next == target_node) {
            Node* node_to_delete = list->first;
            list->first = list->first->next;
            delete node_to_delete;
            return;
        }

        // Иначе находим узел перед целевым узлом
        Node* previous_node = list->first;
        while (previous_node->next != nullptr && previous_node->next != target_node) {
            previous_node = previous_node->next;
        }

        // Если целевой узел не найден, или если он является последним узлом списка
        if (previous_node->next == nullptr) {
            return;
        }

        // Удаляем узел перед целевым узлом
        Node* node_to_delete = previous_node->next;
        previous_node->next = target_node;
        delete node_to_delete;
    }

    static void delete_after(List* list, Node* target_node) {
        // Если список пуст или если целевой узел равен nullptr, то нечего удалять
        if (list->first == nullptr || target_node == nullptr || target_node->next == nullptr) {
            return;
        }

        // Находим узел, который следует за целевым узлом
        Node* node_to_delete = target_node->next;

        // Устанавливаем указатель на следующий узел целевого узла на узел после узла, который удаляем
        target_node->next = node_to_delete->next;

        // Удаляем узел
        delete node_to_delete;
    }
};

int main() {
    // 1 Задание

    // Создаем список
    List* list = new List();

    // Добавляем элементы в список
    ListStuff::add_first(list, 3);
    ListStuff::add_first(list, 2);
    ListStuff::add_first(list, 1);

    // Выводим элементы списка в обычном порядке
    std::cout << "Элементы списка в обычном порядке: ";
    ListStuff::print(list); // 1 2 3
    std::cout << std::endl;

    // 2 Задание

    // Выводим элементы списка в обратном порядке
    std::cout << "Элементы списка в обратном порядке: ";
    ListStuff::print_reversed(list); // 3 2 1
    std::cout << std::endl;

    // Добавляем новый элемент в конец списка
    ListStuff::add_last(list, 4);

    // Выводим элементы списка снова, чтобы убедиться, что элемент добавлен в конец
    std::cout << "Элементы списка после добавления нового элемента в конец: ";
    ListStuff::print(list); // 1 2 3 4
    std::cout << std::endl;

    // 3 Задание

    // Удаляем последний элемент списка
    ListStuff::delete_last(list);

    // Выводим элементы списка снова, чтобы убедиться, что последний элемент удален
    std::cout << "Элементы списка после удаления последнего элемента: ";
    ListStuff::print(list); // 1 2
    std::cout << std::endl;
    
    // 4 Задание

    // Создаем копию списка
    List* copied_list = ListStuff::copy(list);

    // Выводим элементы копии списка
    std::cout << "Копия списка: ";
    ListStuff::print(copied_list); // 1 2 3
    std::cout << std::endl;

    // 5 Задание

    // Удаляем элемент перед целевым узлом (удаление узла "2")
    ListStuff::delete_before(list, list->first->next);

    // Выводим элементы списка после удаления
    std::cout << "Список после удаления элемента перед целевым узлом: ";
    ListStuff::print(list); // 1 3
    std::cout << std::endl;

    // 6 Задание

    // Удаляем элемент после целевого узла (удаление узла "2")
    ListStuff::delete_after(copied_list, copied_list->first);

    // Выводим элементы списка после удаления
    std::cout << "Список после удаления элемента после целевого узла: ";
    ListStuff::print(copied_list); // 1 3
    std::cout << std::endl;

    // Освобождаем память, выделенную для списка
    delete list;
    delete copied_list;
    return 0;
}