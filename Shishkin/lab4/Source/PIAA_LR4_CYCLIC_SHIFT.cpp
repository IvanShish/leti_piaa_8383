#include <iostream>
#include <vector>

int KMPSearch(const std::string& pat, std::string& text);    //���
void prefixFunc(const std::string& pat, int lenOfPat, std::vector<int>& pi); // �������-�������

int main() {
    setlocale(LC_ALL, "RUS");
    std::string pattern;    //������ (������ B)
    std::string text;       //�����  (������ A)
    std::cin >> text;
    std::cin >> pattern;

    int answer = KMPSearch(pattern, text);

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "������ ������ = " << answer << std::endl;
    system("pause");
    return 0;
}


int KMPSearch(const std::string& pat, std::string& text) {
    std::cout << "�����������, �������� �� ������ \"" << text << "\" ����������� ������� ������ \"" << pat << "\"" << std::endl;
    int lenOfPat = pat.length();    //����� �������
    int lenOfText = text.length();   //����� ������

    if (lenOfPat != lenOfText) {   //���� ����� ������ � ������� �� �����, �� ������������ -1
        std::cout << "����� ������ � ������� �� �����" << std::endl;
        return -1;
    }
    else if (pat == text) {
        std::cout << "������ ���������" << std::endl;
        return 0;
    }

    text += text;
    lenOfText = text.length(); //����� �������� ����� ������
    std::vector <int> pi(lenOfPat, 0);   //����� ������������� �������� ������, ������������ � ��� ���������

    int i = 0; //������ ��� ����������� �� ������ text
    int j = 0; //������ ��� ����������� �� ������ pattern

    prefixFunc(pat, lenOfPat, pi);   //���������� ������� pi ��� ������ pat

    std::cout << "���������� ��������� �����-�������-������..." << std::endl;
    while (i < lenOfText) {
        std::cout << "������ i - " << i << ", ������ j - " << j << std::endl;

        if (pat[j] == text[i]) {  //���� j-�� ������ ������� ����� i-�� ������� ������ 
            std::cout << "i-�� ������ ������ ��������� � j-�� �������� �������, ������� ����������� i � j �� 1" << std::endl;
            j++;     //j ������������� ������ ����� ��������� ��������
            i++;
            std::cout << std::endl << "������ ������ '" << text[i] << "': " << std::endl;
        }

        if (j == lenOfPat) {    //���� j ����� ����� �������, �� ������� ��������� ������� � �����
            std::cout << "������ i - " << i << ", ������ j - " << j << std::endl;
            std::cout << "!!!������� ��������� ������� � �����" << std::endl;
            return i - j;
        }

        else if (i < lenOfText && pat[j] != text[i]) {  //���� j-�� ������ ������� �� ����� ������� ������
            std::cout << "i-�� ������ ������ �� ��������� � j-�� �������� �������";

            if (j != 0) {
                std::cout << ". ������ j ��������� �������� " << pi[j - 1] << std::endl;
                j = pi[j - 1];
            }

            else {
                std::cout << ", j = 0, �������������, ������������ ���������� i �� 1" << std::endl;
                i++;
                std::cout << std::endl << "������ ������ '" << text[i] << "': " << std::endl;
            }
        }
    }

    std::cout << "������ �� �������� ����������� �������" << std::endl;
    return -1;
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
