#include <iostream>
#include <vector>
#include <algorithm>

struct Vertex {
	std::vector <int> nextVrtx;  //nextVrtx[i] — номер вершины, в которую мы придем по символу с номером i в алфавите
	bool flag;       //бит, указывающий на то, является ли наша вершина исходной строкой
	int suffLink; //суффиксная ссылка
	std::vector <int> autoMove; //запоминание перехода автомата
	int par;    //вершина-отец в дереве
	char symb; //символ на ребре от par к этой вершине 
	int patternNumber; //номер шаблона
	int deep;   //глубина
};

struct ResForStepik {
	int position;
	int number;
};

Vertex makeBohr(int par, char c);	//функция инициализации бора
void addStringsToBohr(std::vector <Vertex>& bohr, int n);   //добавление строк к бору
int getSuffLink(int v, std::vector <Vertex>& bohr);		//получение суффиксной ссылки
int getAutoMove(int v, int ch, std::vector <Vertex>& bohr);		//получение перехода автомата
void findAllPos(const std::string& text, std::vector <Vertex>& bohr, std::vector <ResForStepik>& result);	//поиск вхождений
bool cmpForRes(ResForStepik res1, ResForStepik res2);	//компаратор для результата
void printAuto(std::vector <Vertex>& bohr);    //печать состояний автомата

int main() {
	setlocale(LC_ALL, "RUS");
	std::string text;
	int n;
	std::vector <Vertex> bohr;    //бор
	std::vector <ResForStepik> result;

	std::cin >> text;
	std::cin >> n;

	if (n <= 0) {
		std::cout << "Вхождения не найдены\n";
		system("pause");
		return 0;
	}

	bohr.push_back(makeBohr(0, NULL));

	addStringsToBohr(bohr, n);
	std::cout << "-----------------------------------------------------------------" << std::endl;

	findAllPos(text, bohr, result);

	std::sort(result.begin(), result.end(), cmpForRes);

	printAuto(bohr);
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "Ответ:" << std::endl;

	if (result.size() == 0) {
		std::cout << "Вхождения не найдены\n";
	}

	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i].position << " " << result[i].number << std::endl;
	}

	system("pause");
	return 0;
}

Vertex makeBohr(int par, char c) {
	Vertex b;
	for (int i = 0; i < 26; i++) {   //инициализация бора (до 26, т.к. в ASCII table заглавные латинские буквы идут от 65 до 90)
		b.nextVrtx.push_back(-1);
		b.autoMove.push_back(-1);
	}
	b.suffLink = -1;
	b.flag = false;
	b.par = par;
	b.symb = c;
	b.patternNumber = -1;
	return b;
}

void addStringsToBohr(std::vector <Vertex>& bohr, int n) {
	for (int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;

		std::cout << "Добавление в бор шаблона \"" << s << "\"..." << std::endl;

		int num = 0; //начинаем с корня   
		for (size_t j = 0; j < s.length(); j++) {
			std::cout << "Добавление символа '" << s[i] << "'..." << std::endl;
			int ch = s[j] - 'A';

			if (bohr[num].nextVrtx[ch] == -1) { //-1 - признак отсутствия ребра
				std::cout << "Ребра нет. Создается новая вершина" << std::endl;
				bohr.push_back(makeBohr(num, ch));
				bohr[num].nextVrtx[ch] = bohr.size() - 1;
			}

			num = bohr[num].nextVrtx[ch];
			std::cout << "Переход по символу '" << s[i] << "'" << std::endl;
		}

		std::cout << "Текущая вершина - лист" << std::endl << std::endl;
		bohr[num].flag = true;
		bohr[num].deep = s.length();
		bohr[num].patternNumber = i + 1;
	}
}

int getSuffLink(int v, std::vector <Vertex>& bohr) {
	std::cout << "Вызывается функция getSuffLink..." << std::endl;

	if (bohr[v].suffLink == -1) {    //если еще не считали
		std::cout << "Суффикс ссылка еще не была посчитана" << std::endl;

		if (v == 0 || bohr[v].par == 0) {    //если v - корень или предок v - корень
			std::cout << "Суффиксная ссылка из вершины = 0" << std::endl;
			bohr[v].suffLink = 0;
		}

		else {
			std::cout << "Поиск суффиксной ссылки путем попытки перехода по символу из вершины предка\n";
			bohr[v].suffLink = getAutoMove(getSuffLink(bohr[v].par, bohr), bohr[v].symb, bohr);
		}
	}

	std::cout << "Завершается функция getSuffLink" << std::endl << std::endl;
	return bohr[v].suffLink;
}

int getAutoMove(int v, int ch, std::vector <Vertex>& bohr) {
	std::cout << "Вызывается функция getAutoMove..." << std::endl;

	if (bohr[v].autoMove[ch] == -1) {   // если в словаре переход нет текущего символа
		std::cout << "В словаре переходов еще нет перехода по символу '" << (char)(ch + 'A') << "'" << std::endl;

		if (bohr[v].nextVrtx[ch] != -1) {
			std::cout << "Существует ребро бора с этим символом. Этот переход добавляется в словарь переходов" << std::endl;
			bohr[v].autoMove[ch] = bohr[v].nextVrtx[ch];
		}

		else {
			std::cout << "Не существует ребра бора с этим символом. Попытка совершения перехода из вершины, доступной по суффиксной ссылке" << std::endl;

			if (v == 0)
				bohr[v].autoMove[ch] = 0;
			else
				bohr[v].autoMove[ch] = getAutoMove(getSuffLink(v, bohr), ch, bohr);
		}
	}

	std::cout << "Завершается функция getAutoMove" << std::endl << std::endl;
	return bohr[v].autoMove[ch];
}

void findAllPos(const std::string& text, std::vector <Vertex>& bohr, std::vector <ResForStepik>& result) {
	std::cout << "Производится поиск шаблона в тексте" << std::endl;
	int curr = 0;

	for (int i = 0; i < text.length(); i++) {
		std::cout << "Переход по символу '" << text[i] << "':" << std::endl;

		curr = getAutoMove(curr, text[i] - 'A', bohr);     //Переход из текущей вершины по текущему символу
		for (int tmp = curr; tmp != 0; tmp = getSuffLink(tmp, bohr)) {		// Обход автомата по суффикс ссылкам 
			if (bohr[tmp].flag) {		//Если при обходе встретился flag = 1
				std::cout << "Проверяемая вершина - лист. Найдено вхождение шаблона в текст" << std::endl;
				ResForStepik res;
				res.number = bohr[tmp].patternNumber;
				res.position = i + 2 - bohr[tmp].deep;
				result.push_back(res);
			}
		}
	}
}

bool cmpForRes(ResForStepik res1, ResForStepik res2) {
	if (res1.position != res2.position) {
		return res1.position < res2.position;
	}
	return res1.number < res2.number;
}

void printAuto(std::vector <Vertex>& bohr) {
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "Построенный автомат:" << std::endl;

	for (int i = 0; i < bohr.size(); i++) {
		Vertex curr = bohr[i];
		std::cout << "Номер вершины " << i << ":\n";

		if (curr.flag) {
			std::cout << "Вершина - лист по шаблону номер " << curr.patternNumber << std::endl;
		}

		if (curr.par != -1) {
			std::cout << "Номер вершины предка " << curr.par << ", символ предка " << (char)(curr.symb + 'A') << std::endl;
		}

		if (curr.suffLink != -1) {
			std::cout << "Суффиксная ссылка " << curr.suffLink << std::endl;
		}

		if (!curr.flag) {
			std::cout << "Ребра бора, доступные из вершины: ";
			for (int j = 0; j < curr.nextVrtx.size(); j++) {
				if (curr.nextVrtx[j] != -1) std::cout << curr.nextVrtx[j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << "Переходы, доступные из вершины: ";
		for (int j = 0; j < curr.autoMove.size(); j++) {
			if (curr.autoMove[j] != -1) std::cout << curr.autoMove[j] << " ";
		}
		std::cout << std::endl;

	}
}
