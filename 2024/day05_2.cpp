#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <execution>
#include <concepts>
#include <cstdint>

using namespace std;

template<totally_ordered T>
bool is_overlap(const set<T>& a, vector<T> b)
{
	vector<T> isect;
	ranges::sort(b);
	set_intersection(execution::par_unseq, a.cbegin(), a.cend(), b.cbegin(), b.cend(), back_inserter(isect));
	return !isect.empty();
}

int main(void)
{
	unordered_map<uint32_t, set<uint32_t>> rules;
	vector<uint32_t> pages;
	string s;
	istringstream iss;
	uint32_t mid_sum = 0;

	while (getline(cin, s)) {
		if (s.empty())
			break;
		uint32_t X, Y;

		iss.str(s);
		iss >> X;
		iss.ignore(1);
		iss >> Y;
		rules[X].insert(Y);

		iss.clear();
	}

	while (getline(cin, s)) {
		uint32_t page;
		bool valid = true;

		iss.str(s);
		while (iss >> page) {
			if (valid && is_overlap(rules[page], pages))
				valid = false;
			pages.push_back(page);
			iss.ignore(1);
		}
		if (!valid) {
			ranges::sort(pages, [&rules](const auto& a, const auto& b)
			{
				return !rules[b].contains(a);
			});
			mid_sum += pages[pages.size() >> 1];
		}

		iss.clear();
		pages.clear();
	}

	cout << mid_sum << '\n';
	return 0;
}

