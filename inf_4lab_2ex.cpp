#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <locale>
#include <codecvt>

// ������� ��� �������� ������ ���������� � ���������� ����� � ������� ��������
std::string formatWord(const std::string& word) {
    std::string formattedWord = word;
    formattedWord.erase(std::remove_if(formattedWord.begin(), formattedWord.end(), ispunct), formattedWord.end());
    std::transform(formattedWord.begin(), formattedWord.end(), formattedWord.begin(), tolower);
    return formattedWord;
}

// ������� ��� �������� ������� ����-���� �� �����
std::set<std::string> loadStopWords(const std::string& filename) {
    std::set<std::string> stopWords;
    std::ifstream file(filename);

    if (file) {
        std::string word;
        while (file >> word) {
            stopWords.insert(formatWord(word));
        }
        file.close();
    } else {
        std::cout << "�� ������� ������� ���� �� �������� ����-����." << std::endl;
    }

    return stopWords;
}

int main() {
      setlocale(LC_ALL, "Russian");
    std::map<std::string, int> wordFrequency;
    std::set<std::string> stopWords = loadStopWords("stop_words.txt");
    std::ifstream file("inf_4lab_2ex.txt");

    if (!file) {
        std::cout << "�� ������� ������� ���� � �������." << std::endl;
        return 0;
    }

    std::string word;
    while (file >> word) {
        word = formatWord(word);

        // ���������, ��� ����� �� �������� ����-������ � �� ���������� � ��������� '���' � �� ������������� �� ��������� �����.
        if (stopWords.count(word) == 0 && !word.empty() && word.substr(0, 3) != "���" && std::isalpha(word.back()) && std::isalpha(word.front())) {
            // ����������� ������� ������������� �����
            wordFrequency[word]++;
        }
    }

    file.close();

    // ������� multimap ��� ���������� ���� �� ������� �������������
    std::multimap<int, std::string, std::greater<int>> sortedWords;
    for (const auto& pair : wordFrequency) {
        sortedWords.insert(std::make_pair(pair.second, pair.first));
    }

    // ������� 50 ����� ����������� ����
    int count = 0;
    for (const auto& pair : sortedWords) {
        if (count == 50) {
            break;
        }
        std::cout << pair.second << " - " << pair.first << std::endl;
        count++;
    }

     std::string key;

    while (true) {
        std::cout << std::endl;
        std::cout << "������� ���� (��� ������ ������� 'exit'): ";
        std::cin >> key;

        if (key == "exit") {
            break;
        }

        // ���������, ���� �� ��������� ���� � ����������
        if (wordFrequency.count(key) != 0) {
            std::string action;
            std::cout << "��������: " << std::endl;
            std::cout << "1 - ������� ��������" << std::endl;
            std::cout << "2 - ������� �����" << std::endl;
            std::cout << "3 - ��������/�������� ��������" << std::endl;

            std::cout << "������� ����� ��������: ";
            std::cin >> action;

            int actionNumber;
            try {
                actionNumber = std::stoi(action);

                if (actionNumber == 1) {
                    std::cout << key << " - " << wordFrequency[key] << std::endl;
                } else if (actionNumber == 2) {
                    wordFrequency.erase(key);
                    std::cout << "����� '" << key << "' �������." << std::endl;
                } else if (actionNumber == 3) {
                    int newValue;
                    std::cout << "������� ����� ��������: ";
                    std::cin >> newValue;
                    wordFrequency[key] = newValue;
                    std::cout << "�������� ����� '" << key << "' �������� �� " << newValue << "." << std::endl;
                } else {
                    std::cout << "�������� ����� ��������." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "�������� ����� ��������." << std::endl;
            }
        } else {
            std::cout << "����� '" << key << "' �� �������." << std::endl;
        }
    }
    return 0;
}
