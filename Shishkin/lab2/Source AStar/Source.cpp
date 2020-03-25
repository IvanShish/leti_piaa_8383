#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Edge {              //��������� ��� �������� ����� �����
	char connectedNode;    //������� ����
	int heruisticNum;      //������������� �����
	double weight;         //��� �����
};

struct Graph {             //��������� ��� �������� �����
	char name;             //�������� ����
	vector <Edge> edge;    //������ ������� �����
};

struct AStar {             //��������� ��� ������ �*
	char node;             //������� ����
	char prev;             //���������� ����
	double f;              //��������� ���� ������������ �� �������� f = g + heruisticNum
	double g;              //�������� g, ����������� ��� ���������� �������� f
	double h;
	bool checked = false;  //��������� �� �������
};

int heuristicFunc(char from, char to);     //������������� �������
bool cmpEdge(Edge i, Edge j);			   //���������� ��� ���������� ����� �� �������������� ��������
void aStar(char start, char finish, vector <Graph> gr, string nodeNames); //����� A*

int main() {
	//{ 'a', 'b', 'c', 'a', 'd' };
	//{ 'b', 'c', 'd', 'd', 'e' };
	//{ 3, 1, 1, 5, 1 };
	setlocale(LC_ALL, "RUS");
	char start;       //��������� �������
	char finish;      //�������� �������
	double currWeight = 0;
	string resStr = "";

	vector <Graph> gr;
	vector <char> a;
	vector <char> b;
	vector <double> c;
	int size = 0;
	char tmpa;     //��� ������ � ������ a
	char tmpb;     //��� ������ � ������ b
	double tmpc;   //��� ������ � ������ c

	cin >> start >> finish;
	string nodeNames;    //��� �������� �������� ���� �����
	nodeNames += start;
	while (cin >> tmpa >> tmpb >> tmpc) {
		a.push_back(tmpa);
		b.push_back(tmpb);
		c.push_back(tmpc);
		size++;

		Edge e;
		Graph g;
		e.connectedNode = tmpb;
		e.weight = tmpc;
		g.name = tmpa;
		g.edge.push_back(e);
		gr.push_back(g);

		if (nodeNames.length() == 0) nodeNames += tmpb;
		else if (nodeNames.find(tmpb) == string::npos) nodeNames += tmpb;
	}

	for (int i = 0; i < gr.size(); i++) {
		for (int j = 0; j < gr[i].edge.size(); j++) {   //���������� ������� ������ �� �������������� �����
			gr[i].edge[j].heruisticNum = heuristicFunc(gr[i].edge[j].connectedNode, finish);
		}

		sort(gr[i].edge.begin(), gr[i].edge.end(), cmpEdge);
	}

	cout << "-------------------------------------------------------------------------" << endl;
	cout << "�������� ������:" << endl;
	cout << "��������� �������: " << start << ", �������� �������: " << finish << endl;
	for (int i = 0; i < size; i++) cout << a[i] << " ";
	cout << endl;
	for (int i = 0; i < size; i++) cout << b[i] << " ";
	cout << endl;
	for (int i = 0; i < size; i++) cout << c[i] << " ";
	cout << endl;
	cout << "-------------------------------------------------------------------------" << endl;

	cout << "����� ����� ���������� �� �������������� �����:" << endl;
	for (int i = 0; i < gr.size(); i++) {
		for (int j = 0; j < gr[i].edge.size(); j++) {
			cout << "����� ";
			cout << "�� " << gr[i].name << " � " << gr[i].edge[j].connectedNode << "; ������������� �����: " << gr[i].edge[j].heruisticNum << ", ���: " << gr[i].edge[j].weight << endl;
		}
	}
	cout << "-------------------------------------------------------------------------" << endl;

	aStar(start, finish, gr, nodeNames);

	return 0;
}

int heuristicFunc(char from, char to) {   // ������������� �������
	return abs(to - from);   //���������� �������� ��������, ������������ ������� �����, � ������� ASCII
}

bool cmpEdge(Edge i, Edge j) {
	if (i.heruisticNum + i.weight < j.heruisticNum + j.weight) return i.connectedNode > j.connectedNode;
	return i.heruisticNum + i.weight < j.heruisticNum + j.weight;
}

void aStar(char start, char finish, vector <Graph> gr, string nodeNames) {
	vector <AStar> nodes;
	string resStr;   //�������������� ������

	AStar first;      //������ ������ ������� � �������
	first.node = start;
	first.prev = NULL;
	first.g = 0;
	first.f = 0;
	first.h = finish - start;
	nodes.push_back(first);

	for (int k = 0; k < nodeNames.length(); k++) {
		AStar tmp;

		int tmpi = 0;
		int tmpj = 0;

		if (nodeNames[k] == start) {
			continue;
		}
		else {
			for (int i = 0; i < gr.size(); i++) {
				for (int j = 0; j < gr[i].edge.size(); j++) {
					if (gr[i].edge[j].connectedNode == nodeNames[k]) {
						tmpi = i;
						tmpj = j;
						break;
					}
				}
			}
		}

		tmp.f = 10000;
		tmp.node = gr[tmpi].edge[tmpj].connectedNode;
		tmp.g = 10000;
		tmp.h = gr[tmpi].edge[tmpj].heruisticNum;
		nodes.push_back(tmp);
	}

	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
			cout << "����: " << nodes[j].node << ", ����������: " << nodes[j].prev << ", f: ";
			if (nodes[j].f == 10000) cout << "INF";
			else cout << std::setw(3) << nodes[j].f;
			cout << ", g: ";
			if (nodes[j].g == 10000) cout << "INF";
			else cout << std::setw(3) << nodes[j].g;
			cout << ", checked: " << nodes[j].checked << endl;
		}
		cout << endl << endl;

		int index = -1;
		double minH = 1000000;
		double minF = 1000000;
		for (int i = 0; i < nodes.size(); i++) {
			if (nodes[i].checked == false) {
				if (nodes[i].f < minF) {
					minF = nodes[i].f;
					index = i;
					minH = nodes[i].h;
				}
				else if (nodes[i].f == minF && nodes[i].h < minH) {
					index = i;
					minH = nodes[i].h;
				}
			}
		}

		if (index >= 0) {
			if (nodes[index].node == finish) break;
			//cout << "\tmin: " << nodes[index].node << ", index: " << index;
			nodes[index].checked = true;

			for (int i = 0; i < gr.size(); i++) {
				if (gr[i].name == nodes[index].node) {
					
					int tmp;
					for (int j = 0; j < nodes.size(); j++) {
						if (nodes[j].node == gr[i].edge[0].connectedNode) {
							tmp = j;
							break;
						}
					}

					nodes[tmp].prev = nodes[index].node;
					int tmpG = nodes[index].g + gr[i].edge[0].weight;
					if (tmpG < nodes[tmp].g) nodes[tmp].g = tmpG;
					nodes[tmp].f = nodes[tmp].g + nodes[tmp].h;
				}
			}
			//cout << endl;
		}
	}

	cout << "-------------------------------------------------------------------------" << endl;
	cout << "���������:" << endl;
	double minH = 1000000;
	double minF = 1000000;
	int index = 0;
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].checked == false) {
			if (nodes[i].f < minF) {
				minF = nodes[i].f;
				index = i;
				minH = nodes[i].h;
			}
			else if (nodes[i].f == minF && nodes[i].h < minH) {
				index = i;
				minH = nodes[i].h;
			}
		}
	}

	for (int i = 0; i < nodes.size(); i++) {
		resStr = nodes[index].node + resStr;
		if (nodes[index].node == start)
			break;

		for (int j = 0; j < nodes.size(); j++) {
			if (nodes[j].node == nodes[index].prev) {
				index = j;
				break;
			}
		}
	}

	cout << resStr << endl;

}
