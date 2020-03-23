#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

struct info {
	int x;
	int y;
	int size;

	info() {
		x = 0;
		y = 0;
		size = 0;
	}
};

int minn = 1601;

inline void drawingaSquare(int x, int y, int cycle, int counter, int** a);         //рисует квадрат
void backTr(int N, int counter, int** a, int** res, int cycle, int area, info* coordRes, info* tmp);     //основная рекурсивная функция
bool check(int** a, int& N, int& cycle, int& x, int& y);       //проверяет, можно ли в координаты x и y вписать квадрат размером cycle

int main() {
	setlocale(0, "");
	int N;                 //размер столешницы
	info coordRes[70];      //результат координат и размеров
	info tmp[70];
	int K = 1;        //счетчик количества квадратов

	cin >> N;
	if (cin.fail()) {
		system("pause");
		return 0;
	}
	while (N < 2 || N > 40) {        //проверка на то, что 2 <= N <= 40
		cout << "N должно быть 2 <= N <= 40!\n";
		cin >> N;
	}

	//столешница
	int** a = new int* [N];
	int** res = new int* [N];
	for (int i = 0; i < N; i++) {
		a[i] = new int[N];
		res[i] = new int[N];

		for (int j = 0; j < N; j++) {    //обнуление
			a[i][j] = 0;
			res[i][j] = 0;
		}
	}

	if (N % 2 == 0) {             //если размер столешницы четный
		cout << "4\n";
		int half = N / 2;

		cout << "1 1 " << half << endl;
		cout << half + 1 << " 1 " << half << endl;
		cout << "1 " << half + 1 << " " << half << endl;
		cout << half + 1 << " " << half + 1 << " " << half << endl;
	}

	else if (N % 3 == 0) {       //если размер столешницы кратен 3
		cout << "6\n";
		int bigSq = (N * 2) / 3;
		int smallSq = N - bigSq;

		cout << "1 1 " << bigSq << endl;
		cout << bigSq + 1 << " 1 " << smallSq << endl;
		cout << bigSq + 1 << " " << smallSq + 1 << " " << smallSq << endl;
		cout << "1 " << bigSq + 1 << " " << smallSq << endl;
		cout << smallSq + 1 << " " << bigSq + 1 << " " << smallSq << endl;
		cout << bigSq + 1 << " " << 2 * smallSq + 1 << " " << smallSq << endl;
	}

	else if (N % 5 == 0) {       //если размер столешницы кратен 5
		int a = N / 5;

		cout << "8" << endl;
		cout << "1 1 " << 2 * a << endl;
		cout << 2 * a + 1 << " 1 " << a << endl;
		cout << 3 * a + 1 << " 1 " << 2 * a << endl;
		cout << 2 * a + 1 << " " << a + 1 << " " << a << endl;
		cout << "1 " << 2 * a + 1 << " " << a << endl;
		cout << a + 1 << " " << 2 * a + 1 << " " << a << endl;
		cout << 2 * a + 1 << " " << 2 * a + 1 << " " << 3 * a << endl;
		cout << "1 " << 3 * a + 1 << " " << 2 * a << endl;
	}

	else {                   //если размер столешницы - простое число
		long long start = 0;
		long long end = 0;
		start = clock();
		int area = pow(N / 2 + 1, 2) - 1;
		drawingaSquare(N / 2, N / 2, N / 2 + 1, K, a);
		tmp[1].x = N / 2;
		tmp[1].y = N / 2;
		tmp[1].size = N / 2 + 1;
		K++;

		drawingaSquare(N / 2 + 1, 0, N / 2, K, a);
		tmp[2].x = N / 2 + 1;
		tmp[2].y = 0;
		tmp[2].size = N / 2;
		K++;

		drawingaSquare(0, N / 2 + 1, N / 2, K, a);
		tmp[3].x = 0;
		tmp[3].y = N / 2 + 1;
		tmp[3].size = N / 2;
		K++;

		backTr(N, K, a, res, N / 2, area, coordRes, tmp);

		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Ответ:" << endl;
		cout << minn << endl;
		for (int i = 1; i < minn + 1; i++) {
			cout << coordRes[i].y + 1 << " " << coordRes[i].x + 1 << " " << coordRes[i].size << endl;
		}
		end = clock();
		cout << endl << "Время выполнения в сек.: " << (end - start) / CLOCKS_PER_SEC << endl;
		cout << "---------------------------------------------------------------------------" << endl;

		cout << "Итоговое заполнение столешницы квадратами:\n\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (res[i][j] >= 10) cout << res[i][j] << " ";
				else cout << res[i][j] << "  ";
			}
			cout << endl << endl;
		}
	}

	for (int i = 0; i < N; i++) {
		delete[] a[i];
		delete[] res[i];
	}
	delete[] a;
	delete[] res;
	return 0;
}

inline void drawingaSquare(int x, int y, int cycle, int counter, int** a) {
	for (int i = x; i < x + cycle; i++) {
		for (int j = y; j < y + cycle; j++) {
			a[i][j] = counter;
		}
	}
}

void backTr(int N, int counter, int** a, int** res, int cycle, int area, info * coordRes, info * tmp) {
	if (cycle <= 0) return;


	int areaTmp = area - 1;
	int counterTmp = counter;
	
	for (int i = cycle; i > 0; i--) {    //оптимизация: минимальный расчет квадратов, которые еще можно поставить
		if (i * i <= areaTmp) {
			int k = areaTmp / (i * i);
			counterTmp += k;
			areaTmp -= k * i * i;
		}
	}

	if (minn <= areaTmp + counterTmp) {
		cout << "Минимальный расчет квадратов, которые еще можно поставить в столешницу показал, что" << endl;
		cout << "это значение будет больше или равно минимальному, следовательно рассчет прекращается" << endl << endl;
		return;
	}

	cout << "Текущее количество квадратов: " << counter << endl;

	if (cycle != 1) {                //если размер проверяемого квадрата не равен 1
		int x = 0;
		int y = 0;
		if (check(a, N, cycle, x, y) && cycle * cycle < area) {
			for (int i = cycle; i > 0; i--) {
				drawingaSquare(x, y, i, counter, a);

				tmp[counter].x = x;
				tmp[counter].y = y;
				tmp[counter].size = i;

				if (counter == 4) {
					cout << "Вызывается рекурсия для квадрата размером " << N / 2 + 1 - i << endl;
					backTr(N, counter + 1, a, res, N / 2 + 1 - i, area - i * i, coordRes, tmp);
				}
				else {
					cout << "Вызывается рекурсия для квадрата размером " << cycle << endl;
					backTr(N, counter + 1, a, res, cycle, area - i * i, coordRes, tmp);
				}

				tmp[counter].x = 0;       //обнуление
				tmp[counter].y = 0;
				tmp[counter].size = 0;

				drawingaSquare(x, y, i, 0, a);
				cout << "\tЗаканчивается рекурсия для квадрата размером " << i << endl;
			}
		}
		else backTr(N, counter, a, res, cycle - 1, area, coordRes, tmp);
	}
	else {
		cout << "В столешницу можно вставить только единичные квадраты " << endl << "Проверка: будет ли минимальным число с учетом квадратов 1х1" << endl;
		if (minn > counter + area - 1) {
			for (int i = 0; i < N / 2 + 1; i++) {
				for (int j = 0; j < N / 2 + 1; j++) {
					if (a[i][j] == 0) {
						counter++;
						tmp[counter - 1].x = i;
						tmp[counter - 1].y = j;
						tmp[counter - 1].size = 1;
					}
				}
			}
			counter--;
			minn = counter;

			cout << "Промежуточное минимальное число квадратов (с учетом кв. 1х1) = " << minn << endl;

			for (int i = 1; i < counter + 1; i++) {
				coordRes[i].x = tmp[i].x;
				coordRes[i].y = tmp[i].y;
				coordRes[i].size = tmp[i].size;
			}
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					res[i][j] = a[i][j];

			cout << "---------------------------------------------------------------------------" << endl;
			cout << "Промежуточный минимальный вариант заполнения столешницы:" << endl;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (res[i][j] >= 10) cout << res[i][j] << " ";
					else cout << res[i][j] << "  ";
				}
				cout << endl << endl;
			}
			cout << "---------------------------------------------------------------------------" << endl;
		}
		else cout << "С учетом квадратов 1х1, количество квадратов в столешнице не будет минимальным" << endl << endl;
	}
}

bool check(int** a, int& N, int& cycle, int& x, int& y) {
	bool checker = true;

	for (int i = 0; i < N - (N / 2) - cycle + 1; i++) {
		for (int j = 0; j < N - (N / 2) - cycle + 1; j++) {
			if (a[i][j] == 0) {          //если нашелся пустой элемент, то проверяем, можно ли в это место вписать квадрат размером cycle
				checker = true;
				for (int k = 0; k < cycle; k++) {
					if (a[i + k][j] || a[i][j + k] || a[i + cycle - 1 - k][j + cycle - 1] || a[i + cycle - 1][j + cycle - 1 - k]) {
						checker = false;
						break;
					}
				}

				if (checker) {
					y = j;
					x = i;
					return true;
				}
			}
		}
	}
	return false;
}