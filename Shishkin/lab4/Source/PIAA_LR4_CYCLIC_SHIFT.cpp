#include <iostream>
#include <vector>

using namespace std;

int KMPSearch(string& pat, string& text);    //КМП
void prefixFunc(string pat, int M, vector<int>& pi); // Префикс функция

int main() {
    setlocale(LC_ALL, "RUS");
    string pattern;    //шаблон (строка B)
    string text;       //текст  (строка A)
    cin >> text;
    cin >> pattern;

    int answer = KMPSearch(pattern, text);

    cout << "-----------------------------------------------" << endl;
    cout << "Индекс сдвига = " << answer << endl;
    return 0;
}


int KMPSearch(string& pat, string& text) {
    cout << "Определение, является ли строка \"" << text << "\" циклическим сдвигом строки \"" << pat << "\"" << endl;
    int M = pat.length();    //длина шаблона
    int N = text.length();   //длина текста

    if (M != N) {   //если длина текста и шаблона не равны, то возвращается -1
        cout << "Длина текста и шаблона не равны" << endl;
        return -1;
    }
    else if (pat == text) {
        cout << "Строки идентичны" << endl;
        return 0;
    }

    text += text;
    N = text.length(); //новое значение длины текста
    vector <int> pi(M, 0);   //длина максимального префикса строки, совпадающего с его суффиксом

    int i = 0; //индекс для перемещения по строке text
    int j = 0; //индекс для перемещения по строке pattern

    prefixFunc(pat, M, pi);   //вычисление массива pi для строки pat

    cout << "Выполнение алгоритма Кнута-Морриса-Пратта..." << endl;
    while (i < N) {
        cout << "Индекс i - " << i << ", индекс j - " << j << endl;

        if (pat[j] == text[i]) {  //если j-ый символ шаблона равен i-му символу текста 
            cout << "i-ый символ текста совпадает с j-ым символом шаблона, поэтому увеличиваем i и j на 1" << endl;
            j++;     //j увеличивается только когда находится сходство
            i++;
            cout << endl << "Символ текста '" << text[i] << "': " << endl;
        }

        if (j == M) {    //если j равен длине шаблона, то найдено вхождение шаблона в текст
            cout << "Индекс i - " << i << ", индекс j - " << j << endl;
            cout << "!!!Найдено вхождение шаблона в текст" << endl;
            return i - j;
        }

        else if (i < N && pat[j] != text[i]) {  //если j-ый символ шаблона не равен символу текста
            cout << "i-ый символ текста не совпадает с j-ым символом шаблона";

            if (j != 0) {
                cout << ". Теперь j принимает значение " << pi[j - 1] << endl;
                j = pi[j - 1];
            }

            else {
                cout << ", j = 0, следовательно, производится увеличение i на 1" << endl;
                i++;
                cout << endl << "Символ текста '" << text[i] << "': " << endl;
            }
        }
    }

    cout << "Строка не является циклическим сдвигом" << endl;
    return -1;
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
