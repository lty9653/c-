#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
using std::unordered_map;

void list_bucket_counts(const vector<size_t>& counts)
{
	for (size_t i{}; i < counts.size(); ++i)
	{
		cout << "bucket[" << setw(2) << i << "] = " << counts[i] << " ";
		if ((i + 1) % 6 == 0) cout << "\n";
	}
	cout << endl;
}

int main()
{
	unordered_map<string, size_t> people;
	float mlf{ people.max_load_factor() };
	size_t n_buckets{ people.bucket_count() };
	vector<size_t> bucket_counts(n_buckets);

	string name{ "Name" };
	size_t value{};
	size_t max_count{ 8192 };
	auto lf = people.load_factor();
	bool rehash{ false };
	while (mlf <= 1.5f)
	{
		cout << "\n\n*************New Container************"
			<< "\nNumber of buckets: " << n_buckets
			<< " Maximum load factor: " << mlf << endl;
		for (size_t n_elements{}; n_elements < max_count; ++n_elements) {
			lf = people.load_factor();
			people.emplace("name" + to_string(++value), value);
			auto new_count = people.bucket_count();
			if (new_count > n_buckets)
			{
				cout << "\nBucket count increased to " << new_count
					<< ". Load factor was " << lf << " and is now"
					<< people.load_factor()
					<< "\nMaximum elements in a bucket was "
					<< *max_element(begin(bucket_counts), end(bucket_counts))
					<< endl;
				if (n_buckets <= 64)
				{
					cout << "Bucket counts before increase were: " << endl;
					list_bucket_counts(bucket_counts);
				}

				n_buckets = new_count;
				bucket_counts = vector<size_t>(n_buckets);
				rehash = true;
			}
			for (size_t i{}; i < n_buckets; ++i)
				bucket_counts[i] = people.bucket_size(i);

			if (rehash)
			{
				rehash = false;

				cout << "\nRehashed container. Bucket count is " << n_buckets
					<< ". Element count is " << people.size()
					<< "\nMaximum element count in a bucket is now "
					<< *max_element(begin(bucket_counts), end(bucket_counts))
					<< endl;
				if (n_buckets <= 64)
				{
					cout << "\nBucket counts after rehash are:\n";
					list_bucket_counts(bucket_counts);
				}
			}
		}
		cout << "Final state for this container is:\n"
			<< "Bucket count: " << people.bucket_count()
			<< "Element count: " << people.size()
			<< " Maximum element count in a bucket: "
			<< *max_element(begin(bucket_counts), end(bucket_counts))
			<< endl;
		value = 1;
		people = unordered_map<string, size_t>();
		n_buckets = people.bucket_count();
		bucket_counts = vector<size_t>(n_buckets);

		mlf += 0.25f;
		people.max_load_factor(mlf);
	}
}