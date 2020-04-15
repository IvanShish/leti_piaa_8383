#include <iostream>
#include <vector>

int KMPSearch(const std::string& pat, std::string& text);    //КМП
void prefixFunc(const std::string& pat, int lenOfPat, std::vector<int>& pi); // Префикс-функция

int main() {
    setlocale(LC_ALL, "RUS");
    std::string pattern;    //шаблон (строка B)
    std::string text;       //текст  (строка A)
    std::cin >> text;
    std::cin >> pattern;

    int answer = KMPSearch(pattern, text);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Индекс сдвига = " << answer << std::endl;
    system("pause");
    return 0;
}


int KMPSearch(const std::string& pat, std::string& text) {
    std::cout << "Определение, является ли строка \"" << text << "\" циклическим сдвигом строки \"" << pat << "\"" << std::endl;
    int lenOfPat = pat.length();    //длина шаблона
    int lenOfText = text.length();   //длина текста

    if (lenOfPat != lenOfText) {   //если длина текста и шаблона не равны, то возвращается -1
        std::cout << "Длина текста и шаблона не равны" << std::endl;
        return -1;
    }
    else if (pat == text) {
        std::cout << "Строки идентичны" << std::endl;
        return 0;
    }

    text += text;
    lenOfText = text.length(); //новое значение длины текста
    std::vector <int> pi(lenOfPat, 0);   //длина максимального префикса строки, совпадающего с его суффиксом

    int i = 0; //индекс для перемещения по строке text
    int j = 0; //индекс для перемещения по строке pattern

    prefixFunc(pat, lenOfPat, pi);   //вычисление массива pi для строки pat

    std::cout << "Выполнение алгоритма Кнута-Морриса-Пратта..." << std::endl;
    while (i < lenOfText) {
        std::cout << "Индекс i - " << i << ", индекс j - " << j << std::endl;

        if (pat[j] == text[i]) {  //если j-ый символ шаблона равен i-му символу текста 
            std::cout << "i-ый символ текста совпадает с j-ым символом шаблона, поэтому увеличиваем i и j на 1" << std::endl;
            j++;     //j увеличивается только когда находится сходство
            i++;
            std::cout << std::endl << "Символ текста '" << text[i] << "': " << std::endl;
        }

        if (j == lenOfPat) {    //если j равен длине шаблона, то найдено вхождение шаблона в текст
            std::cout << "Индекс i - " << i << ", индекс j - " << j << std::endl;
            std::cout << "!!!Найдено вхождение шаблона в текст" << std::endl;
            return i - j;
        }

        else if (i < lenOfText && pat[j] != text[i]) {  //если j-ый символ шаблона не равен символу текста
            std::cout << "i-ый символ текста не совпадает с j-ым символом шаблона";

            if (j != 0) {
                std::cout << ". Теперь j принимает значение " << pi[j - 1] << std::endl;
                j = pi[j - 1];
            }

            else {
                std::cout << ", j = 0, следовательно, производится увеличение i на 1" << std::endl;
                i++;
                std::cout << std::endl << "Символ текста '" << text[i] << "': " << std::endl;
            }
        }
    }

    std::cout << "Строка не является циклическим сдвигом" << std::endl;
    return -1;
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
