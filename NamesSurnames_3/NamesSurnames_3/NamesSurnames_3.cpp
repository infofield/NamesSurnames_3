#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Person {
public:
	struct FullName {
		string first_Name;
		string last_Name;
	};

	Person(const string& first_name, const string& last_name, int year) {
		year_birth = year;
		m[year] = { first_name, last_name };
		for (auto& i : m) {
			if (i.first < year) {
				m.erase(i.first);
			}
		}
	};

	void ChangeFirstName(int year, const string& first_name) {
		// добавить факт изменения имени на first_name в год year
		for (auto& i : m) {
			if (year > i.first) {
				if (m.count(year) == 0) m[year].last_Name = "";
				m[year].first_Name = first_name;
			}
			break;
		}
	}

	void ChangeLastName(int year, const string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
		for (auto& i : m) {
			if (year > i.first) {
				if (m.count(year) == 0) m[year].first_Name = "";
				m[year].last_Name = last_name;
			}
			break;
		}
	}
	string  GetFullName(int year) const {
		if (year_birth != 0 && year < year_birth) {
			return "No person";
		}
		// получить имя и фамилию по состоянию на конец года year
		int i = 0;
		string first = "";
		string last = "";
		for (const auto& y : m) {

			if (y.first > year && i < 1) {
				return "Incognito";
			}

			if (y.first <= year && y.second.first_Name != "") {
				first = y.second.first_Name;
			}
			if (y.first <= year && y.second.last_Name != "") {
				last = y.second.last_Name;
			}

			i++;
		}

		if (first == "") {
			return last + " " + "with unknown first name";
		}
		else if (last == "") {
			return first + " " + "with unknown last name";
		}
		else {
			return first + " " + last;
		}
	}
	string  GetFullNameWithHistory(int year) const {
		// получить имя и фамилию по состоянию на конец года year
		if (year_birth != 0 && year < year_birth) return "No person";
		int i = 0;
		string first = "";
		string last = "";
		vector<int> v;
		vector<string> fhv;
		vector<string> lhv;
		for (const auto& y : m) {
			v.push_back(y.first);
			if (y.first > year && i < 1) {
				return "Incognito";
			}
			i++;
		}
		reverse(begin(v), end(v));
		int fp = 0;
		int lp = 0;

		for (const auto& y : v) {
			for (const auto& mm : m) {
				if (y <= year && y == mm.first && mm.second.first_Name != "") {
					if (first == "") {
						first = mm.second.first_Name;
					}
					else if (first != mm.second.first_Name || fp > 0) {
						fhv.push_back(mm.second.first_Name);
						fp++;
					}
				}
				if (y <= year && y == mm.first && mm.second.last_Name != "") {
					if (last == "") {
						last = mm.second.last_Name;
					}
					else if (last != mm.second.last_Name || lp > 0) {
						lhv.push_back(mm.second.last_Name);
						lp++;
					}
				}
			}


		}

		if (first == "") {
			if (!lhv.empty()) {
				int ii = 0;
				for (const auto& r : lhv) {
					if (ii > 0) {
						last += ", ";
						last += r;
					}
					else {
						last += " (";
						last += r;
					}
					ii++;
				}
				return last + ") " + "with unknown first name";
			}
			return last + " " + "with unknown first name";
		}
		else if (last == "") {
			if (!fhv.empty()) {
				int ii = 0;
				for (const auto& r : fhv) {
					if (ii > 0) {
						first += ", ";
						first += r;
					}
					else {
						first += " (";
						first += r;
					}
					ii++;
				}
				return first + ") " + "with unknown last name";
			}
			return first + " " + "with unknown last name";
		}
		else {
			if (!fhv.empty()) {
				int ii = 0;
				for (const auto& r : fhv) {
					if (ii > 0) {
						first += ", ";
						first += r;
					}
					else {
						first += " (";
						first += r;
					}
					ii++;
				}
				first += ")";
			}
			if (!lhv.empty()) {
				int ii = 0;
				for (const auto& r : lhv) {
					if (ii > 0) {
						last += ", ";
						last += r;
					}
					else {
						last += " (";
						last += r;
					}
					ii++;
				}
				last += ")";
			}
			return first + " " + last;
		}
	}

private:
	int year_birth = 0;
	map<int, FullName> m;
};

int main() {

	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}