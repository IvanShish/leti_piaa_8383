#include <iostream>
#include <vector>

using namespace std;

void KMPSearch(string pat, vector <int>& answer); // ������� ������� ��������� ������ pat � �����, ������� ����������� �������� � ���� �������
void prefixFunc(string pat, int M, vector<int>& pi); // ������� �������

int main() {
    setlocale(LC_ALL, "RUS");
    string pattern;    //������
    cin >> pattern;
    getchar();   //���������� ������� '\n'

    vector <int> answer;
    KMPSearch(pattern, answer);

    cout << "-----------------------------------------------" << endl;
    cout << "������� ����� ��������� ������� � �����:" << endl;
    if (answer.size() == 0) {
        cout << "��������� �� ���� �������, �����: -1" << endl;
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
    char sym = NULL;  //��� ������������� ���������� ������
    int M = pat.length();    //����� �������

    vector <int> pi(M, 0);   //����� ������������� �������� ������, ������������ � ��� ���������

    int i = 0; //������ ��� ����������� �� ������
    int j = 0; //������ ��� ����������� �� ������ pattern

    sym = cin.get();  //���������� ������� �������

    prefixFunc(pat, M, pi);   //���������� ������� pi ��� ������ pat

    cout << "���������� ��������� �����-�������-������..." << endl;
    if (sym != '\n' && sym != EOF) cout << "������ ������ '" << sym << "': " << endl;
    while (sym != '\n' && sym != EOF) {
        cout << "������ i - " << i << ", ������ j - " << j << endl;

        if (pat[j] == sym) {  //���� j-�� ������ ������� ����� i-�� ������� ������ 
            cout << "������ ������ ��������� � j-�� �������� �������, ������� ����������� i � j �� 1" << endl;
            j++;     //j ������������� ������ ����� ��������� ��������
            i++;
            sym = cin.get();
            if (sym != '\n' && sym != EOF) cout << endl << "������ ������ '" << sym << "': " << endl;
        }

        if (j == M) {    //���� j ����� ����� �������, �� ������� ��������� ������� � �����
            cout << "������ i - " << i << ", ������ j - " << j << endl;
            cout << "!!!������� ��������� ������� � �����. ������ ��������� - " << i - j << endl;
            answer.push_back(i - j);
            cout << "����� j �� �������� " << pi[j - 1] << endl << endl;
            j = pi[j - 1];
        }

        else if (pat[j] != sym) {  //���� j-�� ������ ������� �� ����� ������� ������
            cout << "������ ������ �� ��������� � j-�� �������� �������";

            if (j != 0) {
                cout << ". ������ j ��������� �������� " << pi[j - 1] << endl;
                j = pi[j - 1];
            }

            else {
                cout << ", j = 0, �������������, ������������ ���������� i �� 1" << endl;
                i = i + 1;
                sym = cin.get();
                if (sym != '\n' && sym != EOF) cout << endl << "������ ������ '" << sym << "': " << endl;
            }
        }
    }

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
