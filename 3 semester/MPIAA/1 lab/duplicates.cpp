#include "duplicates.h"
#include <set>
bool has_duplicates(const std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (data[i] == data[j]) {
                // ≈сли найдены два равных элемента, возвращаем true
                return true;
            }
        }
    }
    // ≈сли не найдено дубликатов, возвращаем false
    return false;
}

std::vector<int> get_duplicates(const std::vector<int>& data) {
    std::vector<int> duplicates;
    std::set<int> uniqueDuplicates; // ћножество дл€ хранени€ уникальных дубликатов

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (data[i] == data[j]) {
                // ≈сли найден дубликат, добавл€ем его в uniqueDuplicates
                uniqueDuplicates.insert(data[i]);
                break; // ¬ыходим из внутреннего цикла, если найден дубликат
            }
        }
    }

    //  опируем уникальные дубликаты из множества в вектор
    for (int duplicate : uniqueDuplicates) {
        duplicates.push_back(duplicate);
    }

    return duplicates;
}
