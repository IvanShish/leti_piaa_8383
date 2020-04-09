#include <iostream>
#include <vector>

void KMPSearch(const std::string& pat, std::vector <int>& answer); // ������� ������� ��������� ������ pat � �����, ������� ����������� �������� � ���� �������
void prefixFunc(const std::string& pat, int lenOfPat, std::vector<int>& pi); // �������-�������

int main() {
    setlocale(LC_ALL, "RUS");
    std::string pattern;    //������
    std::cin >> pattern;
    getchar();   //���������� ������� '\n'

    std::vector <int> answer;
    KMPSearch(pattern, answer);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "������� ����� ��������� ������� � �����:" << std::endl;
    if (answer.size() == 0) {
        std::cout << "��������� �� ���� �������, �����: -1" << std::endl;
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
    char sym = NULL;  //��� ������������� ���������� ������
    int lenOfPat = pat.length();    //����� �������

    std::vector <int> pi(lenOfPat, 0);   //����� ������������� �������� ������, ������������ � ��� ���������

    int i = 0; //������ ��� ����������� �� ������
    int j = 0; //������ ��� ����������� �� ������ pattern

    sym = std::cin.get();  //���������� ������� �������

    prefixFunc(pat, lenOfPat, pi);   //���������� ������� pi ��� ������ pat

    std::cout << "���������� ��������� �����-�������-������..." << std::endl;
    if (sym != '\n' && sym != EOF) std::cout << "������ ������ '" << sym << "': " << std::endl;
    while (sym != '\n' && sym != EOF) {
        std::cout << "������ i - " << i << ", ������ j - " << j << std::endl;

        if (pat[j] == sym) {  //���� j-�� ������ ������� ����� i-�� ������� ������ 
            std::cout << "������ ������ ��������� � j-�� �������� �������, ������� ����������� i � j �� 1" << std::endl;
            j++;     //j ������������� ������ ����� ��������� ��������
            i++;
            sym = std::cin.get();
            if (sym != '\n' && sym != EOF) std::cout << std::endl << "������ ������ '" << sym << "': " << std::endl;
        }

        if (j == lenOfPat) {    //���� j ����� ����� �������, �� ������� ��������� ������� � �����
            std::cout << "������ i - " << i << ", ������ j - " << j << std::endl;
            std::cout << "!!!������� ��������� ������� � �����. ������ ��������� - " << i - j << std::endl;
            answer.push_back(i - j);
            std::cout << "����� j �� �������� " << pi[j - 1] << std::endl << std::endl;
            j = pi[j - 1];
        }

        else if (pat[j] != sym) {  //���� j-�� ������ ������� �� ����� ������� ������
            std::cout << "������ ������ �� ��������� � j-�� �������� �������";

            if (j != 0) {
                std::cout << ". ������ j ��������� �������� " << pi[j - 1] << std::endl;
                j = pi[j - 1];
            }

            else {
                std::cout << ", j = 0, �������������, ������������ ���������� i �� 1" << std::endl;
                i = i + 1;
                sym = std::cin.get();
                if (sym != '\n' && sym != EOF) std::cout << std::endl << "������ ������ '" << sym << "': " << std::endl;
            }
        }
    }

}

void prefixFunc(const std::string& pat, int lenOfPat, std::vector<int>& pi) {
    std::cout << "���������� ������� pi..." << std::endl;
    for (int i = 1; i < lenOfPat; i++) {   //���������� ������� �� �� i := 1 �� i := M-1
        int j = pi[i - 1];  //��� �������� �������� �������� pi[i] ��������� ���������� j, ������������ ����� �������� ���������������� �������

        while (j > 0 && pat[i] != pat[j]) {   //��������� �������� pat[i] � pat[j]
            std::cout << "��������� �������� '" << pat[i] << "' � '" << pat[j] << "'..." << std::endl;
            j = pi[j - 1];
        }

        if (pat[i] == pat[j]) {  //���� ������� pat[i] � pat[j] ���������, �� pi[i] = j + 1
            std::cout << "������� '" << pat[i] << "' � ������� " << pat[j] << "' �����, pi[" << i << "] ������������� �� 1" << std::endl;
            ++j;
        }

        std::cout << "pi[" << i << "] = " << j << std::endl;
        pi[i] = j;
    }

    std::cout << "�������� �������-�������:" << std::endl << "{ ";
    for (int i = 0; i < pi.size(); i++) {
        if (i == 0) std::cout << pi[i];
        else std::cout << ", " << pi[i];
    }
    std::cout << " }" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}
