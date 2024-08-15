#include <iostream>

std::unordered_map<char, int> badMatchTable (std::string toSearchText) {
    std::unordered_map<char, int> table;
    int length = toSearchText.length();
    int i = 0;

    while (i < length - 1) {
        if (table.count(toSearchText[i]) == 0) {
            // This means that the char is not there in the map
            // Add the char and set its cont to 1
            table[toSearchText[i]] = std::max(1, length - i - 1);
        }
        i++;
    }
    // We need to check if the last char is already in the table or not. If not, then its value is the length of the string else update its value
    int bla = table.count(toSearchText[length - 1]);
    if (table.count(toSearchText[length - 1]) == 0) {
        // This means its not there so add it and give the value the length
        table[toSearchText[length - 1]] = length;
    } else {
        // Update its value
        table[toSearchText[length - 1]] = std::max(1, length - i - 1);
    }
    return table;
}

bool boyerMoore(std::string text, std::string toSearch) {
    std::unordered_map<char, int> matchingTable = badMatchTable(toSearch);

    bool found = false;

    int textLength = text.length();
    int toSearchLength = toSearch.length();

    int i = 0;
    while (i <= textLength - toSearchLength) {
        int j = toSearchLength - 1;

        while (j >= 0 && toSearch[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            found = true;
            return found;
        } else {
            int skip = (matchingTable.find(text[i + j]) != matchingTable.end()) ? matchingTable[text[i + j]] : toSearchLength;
            i += skip;
        }
    }

    return found;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::unordered_map<char, int> table = badMatchTable("TOOTH");
    for (auto i : table) {
        std::cout << "Test the table : " << i.first << " : " << i.second << std::endl;
    }
    bool found = boyerMoore("TRUSTHARDTOOTHBRUSHES", "TOOTH");
    std::cout << "Searching for string : " << "TOOTH : " << "found : " << (found ? "yes" : "no") << std::endl;
    return 0;
}
