#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

set<char> createCharacterSet(const string& sentence) {
    set<char> characters;
    for (char c : sentence) {
        if (isalpha(c)) {
            characters.insert(tolower(c));
        }
    }
    return characters;
}

void printSet(const set<char>& characters) {
    for (char c : characters) {
        cout << c << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream file("inf_4lab_1ex.txt");
    string sentence1, sentence2;

    if (file.is_open()) {
        getline(file, sentence1);
        getline(file, sentence2);
        file.close();

        set<char> set1 = createCharacterSet(sentence1);
        set<char> set2 = createCharacterSet(sentence2);

        cout << "Set 1: ";
        printSet(set1);

        cout << "Set 2: ";
        printSet(set2);

        // Объединение
        set<char> unionSet;
        set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(unionSet, unionSet.begin()));
        cout << "Union: ";
        printSet(unionSet);

        // Пересечение
        set<char> intersectionSet;
        set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersectionSet, intersectionSet.begin()));
        cout << "Intersection: ";
        printSet(intersectionSet);

        // Разность
        set<char> differenceSet;
        set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(differenceSet, differenceSet.begin()));
        cout << "Difference: ";
        printSet(differenceSet);
    } else {
        cout << "Unable to open file." << endl;
    }

    return 0;
}
