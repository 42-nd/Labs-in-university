#include "duplicates.h"
#include <set>
bool has_duplicates(const std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (data[i] == data[j]) {
                // ���� ������� ��� ������ ��������, ���������� true
                return true;
            }
        }
    }
    // ���� �� ������� ����������, ���������� false
    return false;
}

std::vector<int> get_duplicates(const std::vector<int>& data) {
    std::vector<int> duplicates;
    std::set<int> uniqueDuplicates; // ��������� ��� �������� ���������� ����������

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (data[i] == data[j]) {
                // ���� ������ ��������, ��������� ��� � uniqueDuplicates
                uniqueDuplicates.insert(data[i]);
                break; // ������� �� ����������� �����, ���� ������ ��������
            }
        }
    }

    // �������� ���������� ��������� �� ��������� � ������
    for (int duplicate : uniqueDuplicates) {
        duplicates.push_back(duplicate);
    }

    return duplicates;
}
