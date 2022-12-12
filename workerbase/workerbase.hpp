#include <iostream>
#include <string.h>

#ifndef WORKERBASE_HPP
#define WORKERBASE_HPP

class Worker {
private:
    char* fio;
    char yearBorn[5];
    float salary;
    char admissionDate[11];
public:
    Worker(int fioSize = 30);
    Worker(const Worker& _worker);
    ~Worker();

    Worker& operator =(const Worker& _worker);

    void set_fio(char* _fio);
    void set_yearBorn(char* _year);
    void set_salary(float _salary);
    void set_admissionDate(char* _date);

    char* get_fio();
    char* get_yearBorn();
    float get_salary();
    char* get_admissionDate();

    void print();
    int scan(FILE* stream = stdin);

    int get_years_working(const char* today);
};

class WorkerBase {
private:
    Worker* workers;
    int realSize;
    int maxSize;
public:
    WorkerBase(int _maxSize = 100);
    WorkerBase(const char* fileName, int maxSize = 100);
    WorkerBase(const WorkerBase& _base);
    ~WorkerBase();

    WorkerBase& operator =(const WorkerBase& _base);

    void add_worker(const Worker& _worker);
    void delete_worker(char* workerFio);
    void change_fio(char* oldWorkerFio, char* newWorkerFio);
    void change_salary(char* workerFio, float newSalary);

    void print();
};

char** FindWorkersWithXp(Worker* workers, int n, const char* today, int yearsWorking);
void PrintStrArray(char** _array, int n);

#endif // WORKERBASE_HPP