//tupls and pairs

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;
using Name = pair<string, string>;
using DOB = tuple<size_t, size_t, size_t>;
using Details = tuple<DOB, size_t, string>;
using Element_type = map<Name, Details>::value_type;
using People = map<Name, Details>;

//map输入过程
void get_people(People& people)
{
	string first{}, second{};
	size_t month{}, day{}, year{};
	size_t height{};
	string occupation{};
	char answer{ 'Y' };
	
	while (toupper(answer) == 'Y')
	{
		cout << "Enter a first and secong name: ";
		cin >> ws >> first >> second;
		cout << "Enter data of birth as month day year(integers): ";
		cin >> month >> day >> year;
		DOB dob{ month,day,year };
		
		cout << "Enter height in inches: ";
		cin >> height;

		cout << "Enter occupation: ";
		getline(cin >> ws, occupation, '\n');

		people.emplace(make_pair(Name{ first, second }, make_tuple(dob, height, occupation)));
		cout << "Do you want to enter another(Y or N): ";
		cin >> answer;
	}
}

//输出人物信息
void list_DOB_Job(const People& people)
{
	DOB dob;
	string occupation{};
	cout << endl;
	for (auto iter = begin(people); iter != end(people); ++iter)
	{
		tie(dob, ignore, occupation) = iter->second;
		cout << setw(20) << left << (iter->first.first + " " + iter->first.second)
			<< "DOB: " << right
			<< setw(2) << get<0>(dob) << "-"
			<< setw(2) << setfill('0') << get<1>(dob) << "-"
			<< setw(4) << get<2>(dob) << setfill(' ')
			<< " occupation" << occupation << endl;
	}
}

//排序输出
template<typename Compare>
void list_sorted_people(const People& people, Compare comp)
{
	vector<Element_type*> folks;
	for (const auto& pr : people)
		folks.push_back(&pr);
	auto ptr_comp =
		[&comp](const Element_type* pr1, const Element_type* pr2)->bool {return comp(*pr1, *pr2); };
	sort(begin(folks), end(folks), ptr_comp);
	DOB dob{};
	size_t height{};
	string occupation{};
	cout << endl;
	for (const auto& p : folks) {
		tie(dob, height, occupation) = p->second;
		cout << setw(20) << left << (p->first.first + " " + p->first.second)
			<< "DOB: " << right << setw(2) << get<0>(dob) << "-"
			<< setw(2) << get<1>(dob) << "-"
			<< setw(4) << get<2>(dob) << setfill(' ')
			<< " Height: " << height
			<< " Occupation： " << occupation << endl;
	}
}

int main()
{
	map<Name, Details> people;
	get_people(people);
	cout << "\nThe DOB & jobs are: \n";
	list_DOB_Job(people);
	auto comp = [](const Element_type& pr1, const Element_type& pr2)
	{
		return get<1>(pr1.second) < get<1>(pr2.second);
	};

	cout << "\nThe people in height order are: \n";
	list_sorted_people(people, comp);
}
