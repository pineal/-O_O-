#include <vector>
#include <queue>
#include <set>
#include <iostream>
using namespace std;

bool check(const string & s1, const string & s2) {
	int m1 = 0, m2 = 0;
	for (int i = 0; i < s1.size(); i++) {
		m1 |= (1<<(s1[i] - 'a'));
	}
	for (int i = 0; i < s2.size(); i++) {
		m2 |= (1<<(s2[i] - 'a'));
	}
	return !(m1 & m2);
}

int largestProduct(vector<string> dict) {
	auto Length_Cmp = [](const string & s1, const string & s2) {
		return s1.size() > s2.size();
	};
	sort(dict.begin(), dict.end(), Length_Cmp);
	auto Cmp = [dict](const pair<int, int> & p1, const pair<int, int> & p2) {
		int i1 = p1.first, j1 = p1.second, i2 = p2.first, j2 = p2.second;
		return dict[i1].size() * dict[j1].size() < dict[i2].size() * dict[j2].size();
	};
	int rst = 0;
	priority_queue <pair<int, int>, vector<pair<int, int>>, decltype(Cmp)> max_heap(Cmp);
	set<pair<int, int>> visited;
	max_heap.emplace(make_pair(0, 1));
	visited.emplace(make_pair(0, 1));
	while (!max_heap.empty()) {
		int i = max_heap.top().first;
		int j = max_heap.top().second;
		if (check(dict[i], dict[j])) {
			return static_cast<int>(dict[i].size() * dict[j].size());
		}
		max_heap.pop();
		if (i + 1 < dict.size() && !visited.count(make_pair(i + 1, j))) {
			max_heap.emplace(make_pair(i + 1, j));
			visited.emplace(make_pair(i + 1, j));
		}
		if (j + 1 < dict.size()&& !visited.count(make_pair(i, j + 1))) {
			max_heap.emplace(make_pair(i, j + 1));
			visited.emplace(make_pair(i, j + 1));
		}
	}
	return rst;
}

int main() {
	vector<string> test_01 = {"a","b","c","deuf","fhiop","lmhdnu","xpyzewu","rsptu"};
	vector<string> test_02 = {"abc", "def"};
	vector<string> test_03 = {"aa","bb","ccc","abcfgh","ehi"};
	vector<string> test_04 = {"ac", "ba"};
	cout<<largestProduct(test_01)<<endl;
	cout<<largestProduct(test_02)<<endl;
	cout<<largestProduct(test_03)<<endl;
	cout<<largestProduct(test_04)<<endl;
	return 0;
}
