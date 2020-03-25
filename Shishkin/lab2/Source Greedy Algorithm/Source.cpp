#include <iostream>
#include <vector>

using namespace std;

void findMinWay(string a, string b, vector <double> c, char tmp, double& currWeight, string& resStr, char start, char finish, int size);  //функция поиска минимального пути

int main() {
	setlocale(LC_ALL, "RUS");
	char start;       //начальная вершина
	char finish;      //конечная вершина
	double currWeight = 0;   //текущее расстояния
	string resStr = "";     //результирующая строка

	string a;         //вершины, из которых идут ребра
	string b;         //вершины, в которые идут ребра
	vector <double> c;    //веса ребер
	int size = 0;         //количество ребер
	char tmpa = NULL;
	char tmpb = NULL;
	double tmpc = 0;

	cin >> start >> finish;
	while (cin >> tmpa >> tmpb >> tmpc) {      //считывание
		a += tmpa;
		b += tmpb;
		c.push_back(tmpc);
		size++;
	}

	findMinWay(a, b, c, start, currWeight, resStr, start, finish, size);

	cout << "Ответ:" << endl;

	if (size == 1) cout << a[0] << endl;
	else cout << resStr << endl;
	return 0;
}

void findMinWay(string a, string b, vector <double> c, char tmp, double& currWeight, string& resStr, char start, char finish, int size) {
	int next = 0;			//индекс вершины, в которую будет произведен переход
	vector <int> first;     //для хранения индексов, куда идти дальше

	int prev = 0;			//индекс предыдущей вершины
	while (true) {		//поиск минимального пути
		prev = next;
		int tempW = currWeight;

		if (tmp == finish) break;
		if (first.size() > 0) first.clear();

		for (int i = 0; i < size; i++) {
			if (a[i] == tmp) {
				first.push_back(i);
			}
		}

		cout << "Из вершины " << tmp << " можно попасть в следующие вершины: ";
		for (int i = 0; i < first.size(); i++) {
			cout << b[first[i]] << " ";
		}
		cout << endl;

		while (true) {		//поиск минимального пути из вершины tmp в следующую
			int index = 0;
			if (first.size() > 1) {
				for (int i = 0; i < first.size() - 1; i++) {
					bool less = true;
					for (int j = i + 1; j < first.size(); j++) {
						if (c[first[i]] > c[first[j]]) {
							less = false;
							break;
						}
					}

					if (less) {
						index = i;
						next = first[i];
					}
				}
			}
			else if (first.size() == 1) {
				next = first[0];
			}
			else break;

			cout << "Наименьшим путем оказался путь в вершину " << b[next] << endl;

			if (resStr.find(b[next]) == -1) {
				tmp = b[next];
				if (currWeight == 0) {
					resStr += a[next];
					resStr += b[next];
				}
				else resStr += b[next];
				currWeight += c[next];
				cout << "Промежуточный минимальный путь: " << resStr << endl;
				break;
			}
			else {
				first.erase(first.begin() + index);
				cout << "Так как вершина " << b[next] << " уже была посещена, то производится поиск другой вершины" << endl;
			}
		}

		if (tempW == currWeight) {		//если не был произведен переход
			a[prev] = NULL;
			b[prev] = NULL;
			resStr.erase(resStr.end() - 1);
			tmp = resStr[resStr.size() - 1];
			currWeight -= c[prev];
			c[prev] = 1000000;
			cout << "Некуда идти. Откат назад" << endl;
		}
		cout << "-------------------------------------------------------------" << endl;
	}
}
