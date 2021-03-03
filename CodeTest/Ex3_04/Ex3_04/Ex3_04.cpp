#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;


void show(const deque<string>& words, size_t count = 5) {
    if (words.empty()) return;
    auto max_len = std::max_element(begin(words), end(words), 
        [](const string& s1, const string& s2) {return s1.size() < s2.size(); }) ->size();
    size_t n{ count };
    for (const auto& word : words)
    {
        cout << setw(max_len + 1) << word << " ";
        if (--n) continue;
        cout << endl;
        n = count;
    }
    cout << endl;
}

int main()
{
    deque<string> words;
    string word;
    cout << "Enter words seperated by space, enter Ctrl+Z on a aseperate line to end:" << endl;
    while (true)
    {
        if ((cin >> word).eof())
        {
            cin.clear();
            break;
        }
        words.push_back(word);
    }
    cout << "The words in the list are: " << endl;
    show(words);
    make_heap(begin(words), end(words));
    cout << "\nAfter making a heap, the words in the list are:" << endl;
    show(words);
    cout << "You entered " << words.size() << " words. Enter some more:" << endl;
    while (true)
    {
        if ((cin >> word).eof())
        {
            cin.clear();
            break;
        }
        words.push_back(word);
        push_heap(begin(words), end(words));
    }
    cout << "\nThe words in the list are now:" << endl;
    show(words);
}

