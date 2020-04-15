#include <iostream>
#include <vector>

void KMPSearch(const std::string& pat, std::vector <int>& answer); // Выводит индексы вхождения строки pat в текст, который посимвольно вводится в этой функции
void prefixFunc(const std::string& pat, int lenOfPat, std::vector<int>& pi); // Префикс-функция

int main() {
    setlocale(LC_ALL, "RUS");
    std::string pattern;    //шаблон
    std::cin >> pattern;
    getchar();   //считывание символа '\n'

    std::vector <int> answer;
    KMPSearch(pattern, answer);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Индексы начал вхождений шаблона в текст:" << std::endl;
    if (answer.size() == 0) {
        std::cout << "Вхождений не было найдено, ответ: -1" << std::endl;
    }
    else {
        for (int i = 0; i < answer.size(); i++) {
            if (i == 0) std::cout << answer[i];
            else std::cout << "," << answer[i];
        }
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}


void KMPSearch(const std::string& pat, std::vector <int>& answer) {
    char sym = NULL;  //для посимвольного считывания текста
    int lenOfPat = pat.length();    //длина шаблона

    std::vector <int> pi(lenOfPat, 0);   //длина максимального префикса строки, совпадающего с его суффиксом

    int i = 0; //индекс для перемещения по тексту
    int j = 0; //индекс для перемещения по строке pattern

    sym = std::cin.get();  //считывание первого символа

    prefixFunc(pat, lenOfPat, pi);   //вычисление массива pi для строки pat

    std::cout << "Выполнение алгоритма Кнута-Морриса-Пратта..." << std::endl;
    if (sym != '\n' && sym != EOF) std::cout << "Символ текста '" << sym << "': " << std::endl;
    while (sym != '\n' && sym != EOF) {
        std::cout << "Индекс i - " << i << ", индекс j - " << j << std::endl;

        if (pat[j] == sym) {  //если j-ый символ шаблона равен i-му символу текста 
            std::cout << "Символ текста совпадает с j-ым символом шаблона, поэтому увеличиваем i и j на 1" << std::endl;
            j++;     //j увеличивается только когда находится сходство
            i++;
            sym = std::cin.get();
            if (sym != '\n' && sym != EOF) std::cout << std::endl << "Символ текста '" << sym << "': " << std::endl;
        }

        if (j == lenOfPat) {    //если j равен длине шаблона, то найдено вхождение шаблона в текст
            std::cout << "Индекс i - " << i << ", индекс j - " << j << std::endl;
            std::cout << "!!!Найдено вхождение шаблона в текст. Индекс вхождения - " << i - j << std::endl;
            answer.push_back(i - j);
            std::cout << "Сброс j до значения " << pi[j - 1] << std::endl << std::endl;
            j = pi[j - 1];
        }

        else if (pat[j] != sym) {  //если j-ый символ шаблона не равен символу текста
            std::cout << "Символ текста не совпадает с j-ым символом шаблона";

            if (j != 0) {
                std::cout << ". Теперь j принимает значение " << pi[j - 1] << std::endl;
                j = pi[j - 1];
            }

            else {
                std::cout << ", j = 0, следовательно, производится увеличение i на 1" << std::endl;
                i = i + 1;
                sym = std::cin.get();
                if (sym != '\n' && sym != EOF) std::cout << std::endl << "Символ текста '" << sym << "': " << std::endl;
            }
        }
    }

}

void prefixFunc(const std::string& pat, int lenOfPat, std::vector<int>& pi) {
    std::cout << "Заполнение массива pi..." << std::endl;
    for (int i = 1; i < lenOfPat; i++) {   //вычисление массива пи от i := 1 до i := M-1
        int j = pi[i - 1];  //для подсчёта текущего значения pi[i] заводится переменная j, обозначающая длину текущего рассматриваемого образца

        while (j > 0 && pat[i] != pat[j]) {   //сравнение символов pat[i] и pat[j]
            std::cout << "Обработка символов '" << pat[i] << "' и '" << pat[j] << "'..." << std::endl;
            j = pi[j - 1];
        }

        if (pat[i] == pat[j]) {  //если символы pat[i] и pat[j] совпадают, то pi[i] = j + 1
            std::cout << "Суффикс '" << pat[i] << "' и префикс " << pat[j] << "' равны, pi[" << i << "] увеличивается на 1" << std::endl;
            ++j;
        }

        std::cout << "pi[" << i << "] = " << j << std::endl;
        pi[i] = j;
    }

    std::cout << "Итоговая префикс-функция:" << std::endl << "{ ";
    for (int i = 0; i < pi.size(); i++) {
        if (i == 0) std::cout << pi[i];
        else std::cout << ", " << pi[i];
    }
    std::cout << " }" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}
