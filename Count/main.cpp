#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

string cleanWord(const string& word) {
    string result;
    for (char c : word) {
        if (isLetter(c)) {
            result += toLower(c);
        }
    }
    return result;
}

int main() {
    ifstream file("text.txt");
    if (!file) {
        cout << "Cannot open file." << endl;
        return 1;
    }

    map<string, int> wordCount;
    string currentWord;
    char c;

    while (file.get(c)) {
        if (isLetter(c)) {
            currentWord += toLower(c);
        }
        else {
            if (!currentWord.empty()) {
                wordCount[currentWord]++;
                currentWord.clear();
            }
        }
    }

    if (!currentWord.empty()) {
        wordCount[currentWord]++;
    }

    file.close();

    cout << "how many times each word is repeated:" << endl;
    for (const auto& pair : wordCount) {
        cout << pair.first << " : " << pair.second << endl;
    }

    return 0;
}