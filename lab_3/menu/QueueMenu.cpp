#include "Menu.hpp"
#include "../Quete.hpp"
#include "../../ArraySequence.hpp"

Quate<int, ArraySequence>* g_queue = nullptr;

void QueueMenu() {
    g_queue = new Quate<int, ArraySequence>();
    
    for (int i = 1; i <= 5; i++) {
        g_queue->Enqueue(i);
    }
    
    const char* items[] = {
        "Показать очередь",
        "Enqueue (добавить)",
        "Dequeue (удалить)",
        "Peek (посмотреть первый)",
        "Map (возвести в квадрат)",
        "Where (оставить чётные)",
        "Reduce (сумма)",
        "Очистить",
        "← Назад"
    };
    int item_count = 9;
    while (true) {
        int choice = RunMenu("ОЧЕРЕДЬ", items, item_count);
        
        if (choice == -1 || choice == item_count - 1) {
            delete g_queue;
            break;
        }
        
        try {
            switch (choice) {
                case 0: { 
                    string content;
                    for (int i = 0; i < g_queue->GetSize(); i++) {
                        if (i > 0) content += ", ";
                        content += to_string(g_queue->GetData(i));
                    }
                    DisplaySequence("Очередь", g_queue->GetSize(), content);
                    break;
                }
                case 1: {
                    int val = InputNumber("Введите число");
                    g_queue->Enqueue(val);
                    ShowMessage("Добавлено: " + to_string(val));
                    break;
                }
                case 2: {
                    if (g_queue->IsEmpty()) {
                        ShowMessage("Очередь пуста!", true);
                    } else {
                        int val = g_queue->Peek();
                        g_queue->Dequeue();
                        ShowMessage("Удалено: " + to_string(val));
                    }
                    break;
                }
                case 3: {
                    if (g_queue->IsEmpty()) {
                        ShowMessage("Очередь пуста!", true);
                    } else {
                        ShowMessage("Первый элемент: " + to_string(g_queue->Peek()));
                    }
                    break;
                }
                case 4: {
                    auto new_queue = g_queue->Map<int>([](const int& x) { return x * x; });
                    *g_queue = new_queue;
                    ShowMessage("Map (x²) выполнен");
                    break;
                }
                case 5: {
                    auto new_queue = g_queue->Where([](const int& x) { return x % 2 == 0; });
                    *g_queue = new_queue;
                    ShowMessage("Where (чётные) выполнен");
                    break;
                }
                case 6: {
                    int sum = g_queue->Reduce([](const int& a, const int& b) { return a + b; });
                    ShowMessage("Сумма элементов: " + to_string(sum));
                    break;
                }
                case 7: {
                    delete g_queue;
                    g_queue = new Quate<int, ArraySequence>();
                    ShowMessage("Очередь очищена");
                    break;
                }
            }
        } catch (const Exception& e) {
            ShowMessage(string("Ошибка: ") + e.what(), true);
        }
    }
}