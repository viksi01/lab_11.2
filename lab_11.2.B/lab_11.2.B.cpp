#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum Spec { KN, IT, MATH, PHYSIC, WORK };
string specStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student
{
    char prizv[99];
    Spec spec;
    int kurs;
    int physic;
    int math;
    int IT;
    int nummet;
    int pedagogy;

};


void enter_save(char* fname)
{
    ofstream f(fname, ios::binary);
    if (!f)
    {
        return;
    }

    Student p;

    int spec;
    char ch;
    int i = 0;
    do
    {
        cout << "Студент №" << i + 1 << ":" << endl;
        i++;
        cin.sync();
        cout << "Прізвище: "; cin >> p.prizv;
        cout << "Курс: "; cin >> p.kurs;
        cout << " Спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        p.spec = (Spec)spec;
        cout << "Оцінка з фізики: "; cin >> p.physic;
        cout << "Оцінка з математики: "; cin >> p.math;
        switch (p.spec)
        {
        case KN:
            cout << " Оцінка з програмування : "; cin >> p.IT;
            break;
        case IT:
            cout << " Оцінка з чисельних методів : "; cin >> p.nummet;
            break;
        case MATH:
        case PHYSIC:
        case WORK:
            cout << " Оцінка з педагогіки : "; cin >> p.pedagogy;
            break;
        }
        cout << endl;

        if (!f.write((char*)&p, sizeof(Student)))
        {
            cerr << "Помилка відкриття файлу" << endl;
        }
        cout << "Продовжити введення? (y/n) "; cin >> ch;
        i++;
    } while (ch == 'Y' || ch == 'y');
}

void load_print(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        return;
    }

    Student p;
    int i = 0;

    cout << "======================================================================================================================================================================="
        << endl;
    cout << "| № | Прізвище | Курс |       Cпеціальність      | Оцінка з фізики | Оцінка з математики | Оцінка з програмування |  Оцінка з чисельних методів | Оцінка з педагогіки |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------"
        << endl;

    while (f.read((char*)&p, sizeof(Student)))
    {
        cout << "| " << setw(2) << i + 1;
        cout << "| " << setw(9) << p.prizv;
        cout << "| " << setw(5) << p.kurs;
        cout << "| " << setw(25) << specStr[p.spec];
        cout << "| " << setw(16) << p.physic;
        cout << "| " << setw(20) << p.math;
        switch (p.spec)
        {
        case KN:
            cout << "| " << setw(23) << p.IT << "|" << setw(29) << "|" << setw(22) << "|";
            break;
        case IT:
            cout << "| " << setw(24) << "|" << setw(28) << p.nummet << "|" << setw(22) << "|";
            break;
        case MATH:
        case PHYSIC:
        case WORK:
            cout << "| " << setw(24) << "|" << setw(29) << "|" << setw(21) << p.pedagogy << "|" << endl;
            break;
        }
        cout << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
        cout << endl;
        ++i;
    }
}


void MaxAverage(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        return;
    }

    Student p;
    
    double maxAverage = 0.0;
    while (f.read((char*)&p, sizeof(Student)))
    {
        double average = (p.physic + p.math + p.IT) / 3.;
        maxAverage = average;
        switch (p.spec)
        {
        case KN:
            average = (p.physic + p.math + p.IT) / 3.;
            break;
        case IT:
            average = (p.physic + p.math + p.nummet) / 3.;
        default:
            average = (p.physic + p.math + p.pedagogy) / 3.;
        }
        if (maxAverage < average)
            maxAverage = average;

    }
    cout << p.prizv;
}



double percentofS(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        return 0;
    }
    Student p;
    int k = 0, n = 0;
    while (f.read((char*)&p, sizeof(Student)))
    {
        n++;
        if (p.physic == 5 && p.math == 5 && (p.IT == 5 || p.pedagogy == 5 || p.nummet == 5))
            k++;
    }
    return 100. * k / n;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[100];
    char ch;
    do
    {
        cout << "1. Заповнити дані" << endl
            << "2. Вивести на екран дані" << endl
            << "3. Вивести на екран прізвище, у кого найбільший середній бал" << endl
            << "4. Процент студентів, які вчаться на «відмінно»:" << endl
            << "0. Завершити роботу програми" << endl;

        cout << "Виберіть дію:"; cin >> ch; cout << endl;
        switch (ch)
        {
        case '0':
            break;
        case '1':
            cin.get();
            cin.sync();
            cout << "Введіть ім'я файлу: "; cin.getline(fname, 100);
            enter_save(fname);
            cout << endl;
            break;
        case '2':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу для зчитування даних: "; cin.getline(fname, 100);
            load_print(fname);
            cout << endl;
            break;
        case '3':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу для зчитування даних: "; cin.getline(fname, 100);
            MaxAverage(fname);
            cout << endl;
            break;
        case '4':
            cin.get();
            cin.sync();
            cout << "Введіть назву файлу для зчитування даних: "; cin.getline(fname, 100);
            cout << percentofS(fname); cout << "%";
            cout << endl;
            break;
        default:
            cout << "Нерозпізнана команда" << endl;;
        }
    } while (ch != '0');

    system("pause");
    return 0;
}