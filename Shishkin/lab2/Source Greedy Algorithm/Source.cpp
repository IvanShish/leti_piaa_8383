#include <iostream>
#include <vector>

using namespace std;

void findMinWay(string a, string b, vector <double> c, char tmp, double& currWeight, string& resStr, char start, char finish, int size);  //������� ������ ������������ ����

int main() {
	setlocale(LC_ALL, "RUS");
	char start;       //��������� �������
	char finish;      //�������� �������
	double currWeight = 0;   //������� ����������
	string resStr = "";     //�������������� ������

	string a;         //�������, �� ������� ���� �����
	string b;         //�������, � ������� ���� �����
	vector <double> c;    //���� �����
	int size = 0;         //���������� �����
	char tmpa = NULL;
	char tmpb = NULL;
	double tmpc = 0;

	cin >> start >> finish;
	while (cin >> tmpa >> tmpb >> tmpc) {      //����������
		a += tmpa;
		b += tmpb;
		c.push_back(tmpc);
		size++;
	}

	findMinWay(a, b, c, start, currWeight, resStr, start, finish, size);

	cout << "�����:" << endl;

	if (size == 1) cout << a[0] << endl;
	else cout << resStr << endl;
	return 0;
}

void findMinWay(string a, string b, vector <double> c, char tmp, double& currWeight, string& resStr, char start, char finish, int size) {
	int next = 0;			//������ �������, � ������� ����� ���������� �������
	vector <int> first;     //��� �������� ��������, ���� ���� ������

	int prev = 0;			//������ ���������� �������
	while (true) {		//����� ������������ ����
		prev = next;
		int tempW = currWeight;

		if (tmp == finish) break;
		if (first.size() > 0) first.clear();

		for (int i = 0; i < size; i++) {
			if (a[i] == tmp) {
				first.push_back(i);
			}
		}

		cout << "�� ������� " << tmp << " ����� ������� � ��������� �������: ";
		for (int i = 0; i < first.size(); i++) {
			cout << b[first[i]] << " ";
		}
		cout << endl;

		while (true) {		//����� ������������ ���� �� ������� tmp � ���������
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

			cout << "���������� ����� �������� ���� � ������� " << b[next] << endl;

			if (resStr.find(b[next]) == -1) {
				tmp = b[next];
				if (currWeight == 0) {
					resStr += a[next];
					resStr += b[next];
				}
				else resStr += b[next];
				currWeight += c[next];
				cout << "������������� ����������� ����: " << resStr << endl;
				break;
			}
			else {
				first.erase(first.begin() + index);
				cout << "��� ��� ������� " << b[next] << " ��� ���� ��������, �� ������������ ����� ������ �������" << endl;
			}
		}

		if (tempW == currWeight) {		//���� �� ��� ���������� �������
			a[prev] = NULL;
			b[prev] = NULL;
			resStr.erase(resStr.end() - 1);
			tmp = resStr[resStr.size() - 1];
			currWeight -= c[prev];
			c[prev] = 1000000;
			cout << "������ ����. ����� �����" << endl;
		}
		cout << "-------------------------------------------------------------" << endl;
	}
}
