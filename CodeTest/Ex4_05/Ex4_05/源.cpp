#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;
using Pet_type = string;
using Pet_name = string;

int main()
{
	multimap<Pet_type, Pet_name> pets;
	Pet_type type{};
	Pet_name name{};
	char more{ 'Y' };
	while (toupper(more) == 'Y')
	{
		cout << "Enter the type of your pet and its name: ";
		cin >> ws >> type >> name;
		auto iter = pets.lower_bound(type);
		if (iter != end(pets)) {
			pets.emplace_hint(iter, type, name);
		}
		else {
			pets.emplace(type, name);
		}
		cout << "Do you want to enter another(Y or N): ";
		cin >> more;
	}

	cout << "\nPet list by yype:\n";
	auto iter = begin(pets);
	while (iter != end(pets))
	{
		auto pr = pets.equal_range(iter->first);
		cout << "\nPets of type " << iter->first << " are:\n";
		for (auto p = pr.first; p != pr.second; ++p)
			cout << " " << p->second;
		cout << endl;
		iter = pr.second;
	}
}