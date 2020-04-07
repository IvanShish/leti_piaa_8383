#include <iostream>
#include <vector>

using namespace std;

int KMPSearch(string& pat, string& text);    //���
void prefixFunc(string pat, int M, vector<int>& pi); // ������� �������

int main() {
    setlocale(LC_ALL, "RUS");
    string pattern;    //������ (������ B)
    string text;       //�����  (������ A)
    cin >> text;
    cin >> pattern;

    int answer = KMPSearch(pattern, text);

    cout << "-----------------------------------------------" << endl;
    cout << "������ ������ = " << answer << endl;
    return 0;
}


int KMPSearch(string& pat, string& text) {
    cout << "�����������, �������� �� ������ \"" << text << "\" ����������� ������� ������ \"" << pat << "\"" << endl;
    int M = pat.length();    //����� �������
    int N = text.length();   //����� ������

    if (M != N) {   //���� ����� ������ � ������� �� �����, �� ������������ -1
        cout << "����� ������ � ������� �� �����" << endl;
        return -1;
    }
    else if (pat == text) {
        cout << "������ ���������" << endl;
        return 0;
    }

    text += text;
    N = text.length(); //����� �������� ����� ������
    vector <int> pi(M, 0);   //����� ������������� �������� ������, ������������ � ��� ���������

    int i = 0; //������ ��� ����������� �� ������ text
    int j = 0; //������ ��� ����������� �� ������ pattern

    prefixFunc(pat, M, pi);   //���������� ������� pi ��� ������ pat

    cout << "���������� ��������� �����-�������-������..." << endl;
    while (i < N) {
        cout << "������ i - " << i << ", ������ j - " << j << endl;

        if (pat[j] == text[i]) {  //���� j-�� ������ ������� ����� i-�� ������� ������ 
            cout << "i-�� ������ ������ ��������� � j-�� �������� �������, ������� ����������� i � j �� 1" << endl;
            j++;     //j ������������� ������ ����� ��������� ��������
            i++;
            cout << endl << "������ ������ '" << text[i] << "': " << endl;
        }

        if (j == M) {    //���� j ����� ����� �������, �� ������� ��������� ������� � �����
            cout << "������ i - " << i << ", ������ j - " << j << endl;
            cout << "!!!������� ��������� ������� � �����" << endl;
            return i - j;
        }

        else if (i < N && pat[j] != text[i]) {  //���� j-�� ������ ������� �� ����� ������� ������
            cout << "i-�� ������ ������ �� ��������� � j-�� �������� �������";

            if (j != 0) {
                cout << ". ������ j ��������� �������� " << pi[j - 1] << endl;
                j = pi[j - 1];
            }

            else {
                cout << ", j = 0, �������������, ������������ ���������� i �� 1" << endl;
                i++;
                cout << endl << "������ ������ '" << text[i] << "': " << endl;
            }
        }
    }

    cout << "������ �� �������� ����������� �������" << endl;
    return -1;
}

void prefixFunc(string pat, int M, vector<int>& pi) {
    cout << "���������� ������� pi..." << endl;
    for (int i = 1; i < M; i++) {   //���������� ������� �� �� i := 1 �� i := M-1
        int j = pi[i - 1];  //��� �������� �������� �������� pi[i] ��������� ���������� j, ������������ ����� �������� ���������������� �������

        while (j > 0 && pat[i] != pat[j]) {   //��������� �������� pat[i] � pat[j]
            cout << "��������� �������� '" << pat[i] << "' � '" << pat[j] << "'..." << endl;
            j = pi[j - 1];
        }

        if (pat[i] == pat[j]) {  //���� ������� pat[i] � pat[j] ���������, �� pi[i] = j + 1
            cout << "������� '" << pat[i] << "' � ������� " << pat[j] << "' �����, pi[" << i << "] ������������� �� 1" << endl;
            ++j;
        }

        cout << "pi[" << i << "] = " << j << endl;
        pi[i] = j;
    }

    cout << "�������� �������-�������:" << endl << "{ ";
    for (int i = 0; i < pi.size(); i++) {
        if (i == 0) cout << pi[i];
        else cout << ", " << pi[i];
    }
    cout << " }" << endl;
    cout << "-----------------------------------------------" << endl;
}
