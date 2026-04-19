#include "Menu.hpp"
#include "../Set.hpp"
#include "../../ArraySequence.hpp"

Set<int, ArraySequence>* g_set = nullptr;

void SetMenu() {
    g_set = new Set<int, ArraySequence>();
    
    for (int i = 1; i <= 5; i++) {
        g_set->Add(i);
    }
    
    const char* items[] = {
        "Показать множество",
        "Добавить элемент",
        "Удалить элемент",
        "Проверить наличие",
        "Map (квадрат)",
        "Where (чётные)",
        "Объединение",
        "Пересечение",
        "Разность",
        "Очистить",
        "← Назад"
    };
    int item_count = 11;
    
    while (true) {
        int choice = RunMenu("МНОЖЕСТВО", items, item_count);
        
        if (choice == -1 || choice == item_count - 1) {
            delete g_set;
            break;
        }
        
        try {
            switch (choice) {
                case 0: {
                    string content;
                    for (unsigned int i = 0; i < g_set->GetSize(); i++) {
                        if (i > 0) content += ", ";
                        content += to_string(g_set->GetData(i));
                    }
                    DisplaySequence("Множество", g_set->GetSize(), content);
                    break;
                }
                case 1: {
                    int val = InputNumber("Введите число");
                    g_set->Add(val);
                    ShowMessage("Добавлено: " + to_string(val));
                    break;
                }
                case 2: {
                    int val = InputNumber("Введите число для удаления");
                    g_set->RemoveByValue(val);
                    ShowMessage("Удалено: " + to_string(val));
                    break;
                }
                case 3: {
                    int val = InputNumber("Введите число");
                    ShowMessage(g_set->Contains(val) ? "Есть в множестве" : "Нет в множестве");
                    break;
                }
                case 4: {
                    auto new_set = g_set->Map<int>([](const int& x) { return x * x; });
                    *g_set = new_set;
                    ShowMessage("Map (x²) выполнен");
                    break;
                }
                case 5: {
                    auto new_set = g_set->Where([](const int& x) { return x % 2 == 0; });
                    *g_set = new_set;
                    ShowMessage("Where (чётные) выполнен");
                    break;
                }
                case 6: {
                    delete g_set;
                    g_set = new Set<int, ArraySequence>();
                    ShowMessage("Множество очищено");
                    break;
                }
            }
        } catch (const Exception& e) {
            ShowMessage(string("Ошибка: ") + e.what(), true);
        }
    }
}