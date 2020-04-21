#include <iostream>
#include <vector>

struct Vertex {
	std::vector <int> nextVrtx;  //nextVrtx[i] — номер вершины, в которую мы придем по символу с номером i в алфавите
	bool flag;       //бит, указывающий на то, является ли наша вершина исходной строкой
	int suffLink; //суффиксная ссылка
	std::vector <int> autoMove; //запоминание перехода автомата
	int par;    //вершина-отец в дереве
	char symb; //символ на ребре от par к этой вершине 
	int deep;   //глубина
	bool isNextWC;   //является ли следующий элемент джокером
};

Vertex makeBohr(int par, char c);	//функция инициализации бора
void addStringToBohr(std::vector <Vertex>& bohr, const std::string& pat, char wildCard);   //добавление паттерна к бору
int getSuffLink(int v, std::vector <Vertex>& bohr, char wildCard, char bannedWC);		//получение суффиксной ссылки
int getAutoMove(int v, int ch, std::vector <Vertex>& bohr, char wildCard, char bannedWC);		//получение перехода автомата
void findAllPos(const std::string& text, std::vector <Vertex>& bohr, std::vector <int>& answer, char wildCard, char bannedWC);	//поиск вхождений
void printAuto(std::vector <Vertex>& bohr);    //печать состояний автомата

int main() {
	setlocale(LC_ALL, "RUS");
	std::string text;	//текст
	std::string pattern;	// шаблон
	std::vector <Vertex> bohr;    //бор
	char wildCard;		//джокер
	char bannedWC;     // запрещенный джокер
	std::vector <int> answer;   //ответ

	std::cin >> text;
	std::cin >> pattern;
	std::cin >> wildCard;
	std::cin >> bannedWC;

	addStringToBohr(bohr, pattern, wildCard);

	findAllPos(text, bohr, answer, wildCard, bannedWC);

	std::cout << std::endl << "Ответ:" << std::endl;
	if (answer.size() == 0) std::cout << "Вхождений нет" << std::endl;
	for (int i = 0; i < answer.size(); i++) {
		if (i == 0) std::cout << answer[i];
		else std::cout << ", " << answer[i];
	}
	std::cout << std::endl;

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
	b.isNextWC = false;
	return b;
}

void addStringToBohr(std::vector <Vertex>& bohr, const std::string& pat, char wildCard) {
	std::cout << "Добавление в бор шаблона \"" << pat << "\"..." << std::endl;
	bohr.push_back(makeBohr(0, NULL));
	int num = 0; //начинаем с корня   

	for (size_t j = 0; j < pat.length(); j++) {
		std::cout << "Добавление символа '" << pat[j] << "'..." << std::endl;

		int ch = 0;
		if (pat[j] == wildCard) ch = 'J' - 'A';
		else ch = pat[j] - 'A';

		if (bohr[num].nextVrtx[ch] == -1) { //-1 - признак отсутствия ребра
			std::cout << "Ребра нет. Создается новая вершина" << std::endl;
			bohr.push_back(makeBohr(num, ch));
			bohr[num].nextVrtx[ch] = bohr.size() - 1;

			if (pat[j] == wildCard) {
				std::cout << "Текущий символ - джокер, поэтому переменная isNextWC = true" << std::endl;
				bohr[num].isNextWC = true;
			}
		}

		num = bohr[num].nextVrtx[ch];
		std::cout << "Переход по символу '" << pat[j] << "'" << std::endl;
	}

	bohr[num].flag = true;
	bohr[num].deep = pat.length();
	std::cout << "Конец добавления шаблона в бор" << std::endl << std::endl;
}

int getSuffLink(int v, std::vector <Vertex>& bohr, char wildCard, char bannedWC) {
	std::cout << "Вызывается функция getSuffLink..." << std::endl;

	if (bohr[v].suffLink == -1) {   //если еще не считали
		std::cout << "Суффикс ссылка еще не была посчитана" << std::endl;

		if (v == 0 || bohr[v].par == 0) {   //если v - корень или предок v - корень
			std::cout << "Суффиксная ссылка из вершины = 0" << std::endl;
			bohr[v].suffLink = 0;
		}

		else {
			std::cout << "Поиск суффиксной ссылки путем попытки перехода по символу из вершины предка" << std::endl;
			bohr[v].suffLink = getAutoMove(getSuffLink(bohr[v].par, bohr, wildCard, bannedWC), bohr[v].symb, bohr, wildCard, bannedWC);
		}
	}

	std::cout << "Завершается функция getSuffLink" << std::endl << std::endl;
	return bohr[v].suffLink;
}

int getAutoMove(int v, int ch, std::vector <Vertex>& bohr, char wildCard, char bannedWC) {
	std::cout << "Вызывается функция getAutoMove..." << std::endl;

	if (bohr[v].autoMove[ch] == -1) {
		std::cout << "В словаре переходов еще нет перехода по символу '" << (char)(ch + 'A') << "'" << std::endl;
		if (bohr[v].isNextWC) {
			std::cout << "Из вершины существует переход по символу джокеру" << std::endl;
			if (ch != bannedWC - 'A') {
				std::cout << "Данный символ может быть джокером. Завершается функция getAutoMove" << std::endl << std::endl;
				return bohr[v].nextVrtx['J' - 'A'];
			}

			std::cout << "Данный символ не может быть символом джокера" << std::endl;
		}
	}
	if (bohr[v].nextVrtx[ch] != -1) {
		std::cout << "Существует ребро бора с этим символом. Этот переход добавляется в словарь переходов" << std::endl;
		bohr[v].autoMove[ch] = bohr[v].nextVrtx[ch];
	}
	else {
		std::cout << "Не существует ребра бора с этим символом. Попытка совершения перехода из вершины, доступной по суффиксной ссылке" << std::endl;
		if (v == 0)
			bohr[v].autoMove[ch] = 0;
		else
			bohr[v].autoMove[ch] = getAutoMove(getSuffLink(v, bohr, wildCard, bannedWC), ch, bohr, wildCard, bannedWC);
	}
	return bohr[v].autoMove[ch];
}

void findAllPos(const std::string& text, std::vector <Vertex>& bohr, std::vector <int>& answer, char wildCard, char bannedWC) {
	std::cout << "Производится поиск шаблона в тексте" << std::endl;
	int curr = 0;

	for (int i = 0; i < text.length(); i++) {
		std::cout << "Переход по символу '" << text[i] << "':" << std::endl;
		int sym = text[i] - 'A';

		curr = getAutoMove(curr, sym, bohr, wildCard, bannedWC);     //Переход из текущей вершины по текущему символу
		for (int tmp = curr; tmp != 0; tmp = getSuffLink(tmp, bohr, wildCard, bannedWC)) {	// Обход автомата по суффикс ссылкам 
			if (bohr[tmp].flag) {		//Если при обходе встретился flag = 1
				std::cout << std::endl << "!!!Проверяемая вершина - лист. Найдено вхождение шаблона в текст: ";
				std::cout << i + 2 - bohr[curr].deep << std::endl;
				answer.push_back(i + 2 - bohr[tmp].deep);
			}
		}
	}
}

void printAuto(std::vector <Vertex>& bohr) {
	std::cout << "-----------------------------------------------------------------" << std::endl;
	std::cout << "Построенный автомат:" << std::endl;

	for (int i = 0; i < bohr.size(); i++) {
		Vertex curr = bohr[i];
		std::cout << "Номер вершины " << i << ":\n";

		if (curr.flag) {
			std::cout << "Вершина - лист" << std::endl;
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
