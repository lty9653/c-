#ifndef NAME_H
#define NAME_H
#include <string>
#include <ostream>
#include <istream>

using std::string;
class Name
{
private:
	string first{};
	string second{};
public:
	Name(const string& name1, const string& name2) :
		first(name1), second(name2) {}
	Name() = default;
	bool operator<(const Name& name) const
	{
		return second < name.second || (second == name.second && first < name.first);
	}
	friend std::istream& operator>>(std::istream& in, Name& name);
	friend std::ostream& operator<<(std::ostream& out, const Name& name);
};


inline std::istream& operator>>(std::istream& in, Name& name)
{
	in >> name.first >> name.second;
	return in;
}

inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
	out << name.first + " " + name.second;
	return out;
}
#endif