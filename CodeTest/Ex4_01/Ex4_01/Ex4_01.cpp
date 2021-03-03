#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <utility>
#include <cctype>
#include "Name.h"

using std::string;
using Entry = std::pair<const Name, size_t>;
using std::make_pair;
using std::map;
using namespace std;

Entry get_entry()
{
    cout << "Enter first and second names followed by th eage: ";
    Name name{};
    size_t age{};
    cin >> name >> age;
    return make_pair(name, age);
}

void list_entries(const map<Name, size_t>& people)
{  
    for (auto& entry : people) {
        cout << left << setw(30) << entry.first
            << right << setw(4) << entry.second << endl;
    }
}

int main()
{
    map<Name, size_t> people{ {{"Ann", "Dante"}, 25},{{"Bill", "Hook"}, 46}, {{"Jim", "Jams"}, 32}, {{"Mark", "Time"}, 32} };
    cout << "\nThe initial contents of the map is:\n";
    list_entries(people);
    char answer{ 'Y' };
    cout << "\nEnter a Name and age entry.\n";
    while (toupper(answer) == 'Y')
    {
        Entry entry{ get_entry() };
        auto pr = people.insert(entry);
        if (!pr.second)
        {
            cout << "Key \"" << pr.first->first
                << "\" already present. Do you want to update the age (Y or N)?";
            cin >> answer;
            if (toupper(answer) == 'Y')
                pr.first->second = entry.second;
        }
        cout << "\nThe map now contains the following entries:\n";
        list_entries(people);
    }
}