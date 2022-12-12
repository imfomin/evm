#include <iostream>
#include <fstream>
#include "workerbase.hpp"

using namespace std;

//int main()
//{
//    setlocale(LC_CTYPE, "ru");
// 
//    const int n = 10;
//
//    Worker workers[n];
//
//    FILE* f; fopen_s(&f, "workers.txt", "r");
//
//    if (!f) return 1;
//
//    for (int i = 0; i < 10; i++) {
//        workers[i].scan(f);
//    }
//    fclose(f);
//
//    printf("Все сотрудники:\n");
//    for (int i = 0; i < 10; i++) {
//        workers[i].print();
//    }
//    printf("\n");
//
//    char date[11];
//
//    printf("Сегодняшняя дата:\n");
//    scanf_s("%s", date, 11);
//    printf("\n");
//
//    printf("Сотрудники с опытом работы более 25 лет:\n");
//    char** OldWorkers = FindWorkersWithXp(workers, 10, date, 25);
//    PrintStrArray(OldWorkers, 10);
//
//    for (int i = 0; i < 10; i++) {
//        delete[] OldWorkers[i];
//    }
//    delete[] OldWorkers;
//
//    return 0;
//}

int main() {
    setlocale(LC_CTYPE, "ru");

    WorkerBase b("workers.txt", 5);
    b.print();

    printf("1. Добавить сотрудника\n");
    printf("2. Удалить сотрудника\n");
    printf("3. Поменять фамилию сотрудника\n");
    printf("4. Поменять зарплату сотрудника\n");
    printf("5. Напечатать базу\n");
    printf("default. Выйти\n");

    Worker w;
    char name1[60];
    char name2[60];
    float p;

    bool looping = true;
    int operation;
    char fix;
    while (looping) {
        scanf_s("%d", &operation); scanf_s("%c", &fix, 1);

        try {
            switch (operation) {
            case 1:
                printf("Данные нового сотрудника:\n");
                w.scan();
                b.add_worker(w);

                break;
            case 2:
                printf("Кого удалить?\n");
                gets_s(name1, 60);
                b.delete_worker(name1);

                break;
            case 3:
                printf("Кому поменять?\n"); gets_s(name1, 60);
                printf("Новое имя:\n"); gets_s(name2, 60);
                b.change_fio(name1, name2);

                break;
            case 4:
                printf("Кому поменять?\n"); gets_s(name1, 60);
                printf("Новая зарплата:\n"); scanf_s("%f", &p); scanf_s("%c", &fix, 1);
                b.change_salary(name1, p);

                break;
            case 5:
                b.print();

                break;
            default:
                looping = false;
            }
        }
        catch (...) {  
        }
    }

    return 0;
}