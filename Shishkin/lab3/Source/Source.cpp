#include <iostream> 
#include <limits.h> 
#include <vector>
#include <stack> 
#include <iomanip>
#include <algorithm>

using namespace std;

struct answer {
	char ansFrom;  //вершина, из которой выходит ребро
	char ansTo;    //вершина, в которую входит ребро
	int ansW;      //вес ребра
};

bool dfs(vector<vector<int> > rGraph, int s, int t, vector <int>& parent, int V, string nodeNames);  //возвращает true, если существует путь от истока s к стоку t в графе rGraph, также заполняет массив parent
int fordFulkerson(vector<vector<int> >& graph, vector<vector<int> >& rGraph, int s, int t, int V, string nodeNames); //возвращает максимальный поток от истока s к стоку t
void printGraph(vector<vector<int> > graph, int V, string nodeNames);   //для печати графа
bool cmpForStepik(answer a, answer b);   //компаратор для сортировки вершин

int main() {
	setlocale(LC_ALL, "RUS");
	int N = 0;        //количество ориентированных рёбер графа
	char start;   //исток
	char finish;  //сток

	string nodeNames;  //названия узлов
	string from;
	string to;
	vector <int> w;

	cin >> N;
	cin >> start;
	cin >> finish;

	if (start == finish) {
		cout << "Сток и исток не могут быть одной вершиной" << endl;
		return 0;
	}

	char tmpFrom;
	char tmpTo;
	int tmpW;
	nodeNames += start;
	for (int i = 0; i < N; i++) {
		cin >> tmpFrom >> tmpTo >> tmpW;
		from += tmpFrom;
		to += tmpTo;
		w.push_back(tmpW);
		if (nodeNames.length() == 0) nodeNames += tmpTo;
		else if (nodeNames.find(tmpTo) == string::npos) nodeNames += tmpTo;
	}

	sort(nodeNames.begin(), nodeNames.end());

	int V = nodeNames.length();

	vector<vector<int> > graph(V, vector<int>(V, 0));
	string findInNodeNames;

	for (int k = 0; k < nodeNames.length(); k++) {
		vector <int> tmp;
		for (int j = 0; j < N; j++) {         //поиск всех ребер, ведущих из вершины nodeNames[k]
			if (from[j] == nodeNames[k]) {
				tmp.push_back(j);
			}
		}

		vector <int> nodeTmp;
		for (int i = 0; i < tmp.size(); i++) {    //поиск в строке nodeNames[k] вершины, в которую ведут ребра из вектора tmp
			for (int j = 0; j < nodeNames.length(); j++) {
				if (nodeNames[j] == to[tmp[i]])
					nodeTmp.push_back(j);
			}
		}

		for (int i = 0; i < tmp.size(); i++) {
			graph[k][nodeTmp[i]] = w[tmp[i]];
		}
	}

	int startIndex = 0;
	int finishIndex = 0;
	for (int i = 0; i < V; i++) {
		if (nodeNames[i] == start) startIndex = i;
		else if (nodeNames[i] == finish) finishIndex = i;
	}

	vector<vector<int> > rGraph(V, vector<int>(V, 0));
	int maxFlow = fordFulkerson(graph, rGraph, startIndex, finishIndex, V, nodeNames);

	vector <answer> forStepik;

	for (int i = 0; i < V; i++) {
		vector <int> indices;  //индексы
		for (int j = 0; j < N; j++) {
			if (nodeNames[i] == from[j]) indices.push_back(j);
		}

		for (int j = 0; j < indices.size(); j++) {
			answer ans;
			ans.ansFrom = from[indices[j]];
			ans.ansTo = to[indices[j]];
			
			int tmpF = 0;
			int tmpT = 0;
			for (int k = 0; k < V; k++) {
				if (nodeNames[k] == from[indices[j]]) tmpF = k;
				else if (nodeNames[k] == to[indices[j]]) tmpT = k;
			}

			if (graph[tmpT][tmpF] >= 0) ans.ansW = 0;
			else ans.ansW = abs(graph[tmpT][tmpF]);
			forStepik.push_back(ans);
		}
	}

	sort(forStepik.begin(), forStepik.end(), cmpForStepik);

	cout << "Ответ для степика:" << endl;
	cout << maxFlow << endl;
	for (int i = 0; i < forStepik.size(); i++) cout << forStepik[i].ansFrom << " " << forStepik[i].ansTo << " " << forStepik[i].ansW << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "Максимальный поток в сети = " << maxFlow << endl;

	return 0;
}

bool dfs(vector<vector<int> > rGraph, int s, int t, vector <int>& parent, int V, string nodeNames) { //функция поиска пути в глубину
	vector <bool> visited(V, 0);    //вектор посещенных вершин (если 0, то не посещена)

	stack <int> st;   //создается стек, в который кладется исток, и начальная вершина помечается как посещенная
	st.push(s);
	visited[s] = true;
	parent[s] = -1;

	cout << "Поиск пути..." << endl;
	while (!st.empty()) {       //обработка, пока стек не пуст
		int i = st.top();    //обработка первой вершины
		st.pop();

		cout << "Вершина " << nodeNames[i] << ":" << endl;

		for (int j = 0; j < V; j++) {  //если смежная вершина не обработана и имеет ребро с обрабатываемой вершиной
			if (visited[j] == false && rGraph[i][j] > 0) {
				st.push(j);
				parent[j] = i;
				visited[j] = true;
				cout << "\tДобавление смежной вершины " << nodeNames[j] << " в стек" << endl;
			}
		}

		cout << "Завершение вычислений для вершины " << nodeNames[i] << endl;
	}

	cout << endl;
	if (visited[t] == true) {
		cout << "Найден путь ";

		string str;
		for (int i = t; i != s; i = parent[i])
			str += nodeNames[i];
	
		str += nodeNames[s];

		for (int i = str.length() - 1; i >= 0; i--)
			cout << str[i];

		cout << endl;
	}
	else cout << "Путь не был найден" << endl;

	return (visited[t] == true);   //если был достигнут сток, то возвращается true, иначе - false
}

int fordFulkerson(vector<vector<int> >& graph, vector<vector<int> >& rGraph, int s, int t, int V, string nodeNames) {
	int u, v;

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++) {
			rGraph[u][v] = graph[u][v];
			graph[u][v] = 0;
		}
	
	vector <int> parent(V, 0);  //этот массив заполняется функцией BFS и создан для хранения пути

	int max_flow = 0;  //изначально поток = 0

	while (dfs(rGraph, s, t, parent, V, nodeNames)) {  //увеличивается поток, пока есть путь от истока к стоку

		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		cout << "Поток на пути: " << path_flow << endl;
		cout << "---------------------------------------------------------" << endl;

		for (v = t; v != s; v = parent[v]) {		//обновление пропускной способности каждого ребра
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;

			graph[u][v] += path_flow;
			graph[v][u] -= path_flow;
		}

		max_flow += path_flow;

	}

	cout << "Завершение алгоритма..." << endl;
	cout << "---------------------------------------------------------" << endl;
	return max_flow;
}

void printGraph(vector<vector<int> > graph, int V, string nodeNames) {
	cout << " ";
	for (int i = 0; i < V; i++) {
		cout << setw(3) << nodeNames[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < V; i++) {
		cout << nodeNames[i];
		for (int j = 0; j < V; j++) cout << setw(3) << graph[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

bool cmpForStepik(answer a, answer b) {
	if (a.ansFrom < b.ansFrom) return true;
	else if (a.ansFrom == b.ansFrom) {
		if (a.ansTo < b.ansTo) return true;
	}

	return false;
}
