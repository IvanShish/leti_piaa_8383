#include <iostream>
#include <vector>

using namespace std;

void KMPSearch(string pat, vector <int>& answer); // Выводит индексы вхождения строки pat в текст, который посимвольно вводится в этой функции
void prefixFunc(string pat, int M, vector<int>& pi); // Префикс функция

int main() {
    setlocale(LC_ALL, "RUS");
    string pattern;    //шаблон
    cin >> pattern;
    getchar();   //считывание символа '\n'

    vector <int> answer;
    KMPSearch(pattern, answer);

    cout << "-----------------------------------------------" << endl;
    cout << "Индексы начал вхождений шаблона в текст:" << endl;
    if (answer.size() == 0) {
        cout << "Вхождений не было найдено, ответ: -1" << endl;
    }
    else {
        for (int i = 0; i < answer.size(); i++) {
            if (i == 0) cout << answer[i];
            else cout << "," << answer[i];
        }
    }
    cout << endl;
    return 0;
}


void KMPSearch(string pat, vector <int>& answer) {
    char sym = NULL;  //для посимвольного считывания текста
    int M = pat.length();    //длина шаблона

    vector <int> pi(M, 0);   //длина максимального префикса строки, совпадающего с его суффиксом

    int i = 0; //индекс для перемещения по тексту
    int j = 0; //индекс для перемещения по строке pattern

    sym = cin.get();  //считывание первого символа

    prefixFunc(pat, M, pi);   //вычисление массива pi для строки pat

    cout << "Выполнение алгоритма Кнута-Морриса-Пратта..." << endl;
    if (sym != '\n' && sym != EOF) cout << "Символ текста '" << sym << "': " << endl;
    while (sym != '\n' && sym != EOF) {
        cout << "Индекс i - " << i << ", индекс j - " << j << endl;

        if (pat[j] == sym) {  //если j-ый символ шаблона равен i-му символу текста 
            cout << "Символ текста совпадает с j-ым символом шаблона, поэтому увеличиваем i и j на 1" << endl;
            j++;     //j увеличивается только когда находится сходство
            i++;
            sym = cin.get();
            if (sym != '\n' && sym != EOF) cout << endl << "Символ текста '" << sym << "': " << endl;
        }

        if (j == M) {    //если j равен длине шаблона, то найдено вхождение шаблона в текст
            cout << "Индекс i - " << i << ", индекс j - " << j << endl;
            cout << "!!!Найдено вхождение шаблона в текст. Индекс вхождения - " << i - j << endl;
            answer.push_back(i - j);
            cout << "Сброс j до значения " << pi[j - 1] << endl << endl;
            j = pi[j - 1];
        }

        else if (pat[j] != sym) {  //если j-ый символ шаблона не равен символу текста
            cout << "Символ текста не совпадает с j-ым символом шаблона";

            if (j != 0) {
                cout << ". Теперь j принимает значение " << pi[j - 1] << endl;
                j = pi[j - 1];
            }

            else {
                cout << ", j = 0, следовательно, производится увеличение i на 1" << endl;
                i = i + 1;
                sym = cin.get();
                if (sym != '\n' && sym != EOF) cout << endl << "Символ текста '" << sym << "': " << endl;
            }
        }
    }

}

void prefixFunc(string pat, int M, vector<int>& pi) {
    cout << "Заполнение массива pi..." << endl;
    for (int i = 1; i < M; i++) {   //вычисление массива пи от i := 1 до i := M-1
        int j = pi[i - 1];  //для подсчёта текущего значения pi[i] заводится переменная j, обозначающая длину текущего рассматриваемого образца

        while (j > 0 && pat[i] != pat[j]) {   //сравнение символов pat[i] и pat[j]
            cout << "Обработка символов '" << pat[i] << "' и '" << pat[j] << "'..." << endl;
            j = pi[j - 1];
        }

        if (pat[i] == pat[j]) {  //если символы pat[i] и pat[j] совпадают, то pi[i] = j + 1
            cout << "Суффикс '" << pat[i] << "' и префикс " << pat[j] << "' равны, pi[" << i << "] увеличивается на 1" << endl;
            ++j;
        }

        cout << "pi[" << i << "] = " << j << endl;
        pi[i] = j;
    }

    cout << "Итоговая префикс-функция:" << endl << "{ ";
    for (int i = 0; i < pi.size(); i++) {
        if (i == 0) cout << pi[i];
        else cout << ", " << pi[i];
    }
    cout << " }" << endl;
    cout << "-----------------------------------------------" << endl;
}
