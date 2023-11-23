#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <locale>
#include <codecvt>

// Функция для удаления знаков препинания и приведения слова к нижнему регистру
std::string formatWord(const std::string& word) {
    std::string formattedWord = word;
    formattedWord.erase(std::remove_if(formattedWord.begin(), formattedWord.end(), ispunct), formattedWord.end());
    std::transform(formattedWord.begin(), formattedWord.end(), formattedWord.begin(), tolower);
    return formattedWord;
}

// Функция для загрузки словаря стоп-слов из файла
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
        std::cout << "Не удалось открыть файл со словарем стоп-слов." << std::endl;
    }

    return stopWords;
}

int main() {
      setlocale(LC_ALL, "Russian");
    std::map<std::string, int> wordFrequency;
    std::set<std::string> stopWords = loadStopWords("stop_words.txt");
    std::ifstream file("inf_4lab_2ex.txt");

    if (!file) {
        std::cout << "Не удалось открыть файл с текстом." << std::endl;
        return 0;
    }

    std::string word;
    while (file >> word) {
        word = formatWord(word);

        // Проверяем, что слово не является стоп-словом и не начинается с приставки 'при' и не заканчивается на согласную букву.
        if (stopWords.count(word) == 0 && !word.empty() && word.substr(0, 3) != "при" && std::isalpha(word.back()) && std::isalpha(word.front())) {
            // Увеличиваем частоту встречаемости слова
            wordFrequency[word]++;
        }
    }

    file.close();

    // Создаем multimap для сортировки слов по частоте встречаемости
    std::multimap<int, std::string, std::greater<int>> sortedWords;
    for (const auto& pair : wordFrequency) {
        sortedWords.insert(std::make_pair(pair.second, pair.first));
    }

    // Выводим 50 самых встречаемых слов
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
        std::cout << "Введите ключ (для выхода введите 'exit'): ";
        std::cin >> key;

        if (key == "exit") {
            break;
        }

        // Проверяем, есть ли введенный ключ в контейнере
        if (wordFrequency.count(key) != 0) {
            std::string action;
            std::cout << "Действия: " << std::endl;
            std::cout << "1 - Вывести значение" << std::endl;
            std::cout << "2 - Удалить слово" << std::endl;
            std::cout << "3 - Добавить/заменить значение" << std::endl;

            std::cout << "Введите номер действия: ";
            std::cin >> action;

            int actionNumber;
            try {
                actionNumber = std::stoi(action);

                if (actionNumber == 1) {
                    std::cout << key << " - " << wordFrequency[key] << std::endl;
                } else if (actionNumber == 2) {
                    wordFrequency.erase(key);
                    std::cout << "Слово '" << key << "' удалено." << std::endl;
                } else if (actionNumber == 3) {
                    int newValue;
                    std::cout << "Введите новое значение: ";
                    std::cin >> newValue;
                    wordFrequency[key] = newValue;
                    std::cout << "Значение слова '" << key << "' изменено на " << newValue << "." << std::endl;
                } else {
                    std::cout << "Неверный номер действия." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cout << "Неверный номер действия." << std::endl;
            }
        } else {
            std::cout << "Слово '" << key << "' не найдено." << std::endl;
        }
    }
    return 0;
}
