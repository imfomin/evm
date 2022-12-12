#include <iostream>
#include <string.h>
#include "workerbase.hpp"

#pragma warning(disable : 4996)

Worker::Worker(int fioSize) {
    fio = new char[fioSize]; fio[0] = '\0';
    yearBorn[0] = '\0';
    salary = 0;
    admissionDate[0] = '\0';
}
Worker::Worker(const Worker& _worker) {
    fio = new char[strlen(_worker.fio) + 1];
    strcpy(fio, _worker.fio);

    strcpy(yearBorn, _worker.yearBorn);
    salary = _worker.salary;
    strcpy(admissionDate, _worker.admissionDate);
}
Worker::~Worker() {
    delete[] fio;
}

Worker& Worker::operator =(const Worker& _worker) {
    if (this == &_worker) return *this;

    strcpy(fio, _worker.fio);
    strcpy(yearBorn, _worker.yearBorn);
    salary = _worker.salary;
    strcpy(admissionDate, _worker.admissionDate);

    return *this;
}

void Worker::set_fio(char* _fio) {
    strcpy(fio, _fio);
}
void Worker::set_yearBorn(char* _year) {
    strcpy(yearBorn, _year);
}
void Worker::set_salary(float _salary) {
    salary = _salary;
}
void Worker::set_admissionDate(char* _date) {
    strcpy(admissionDate, _date);
}

char* Worker::get_fio() {
    return fio;
}
char* Worker::get_yearBorn() {
    return yearBorn;
}
float Worker::get_salary() {
    return salary;
}
char* Worker::get_admissionDate() {
    return admissionDate;
}

void Worker::print() {
    printf("%50s %6s %10.2f %12s\n", fio, yearBorn, salary, admissionDate);
}
int Worker::scan(FILE* stream) {
    char initials[5] = "\0";
    int readSuccess = fscanf_s(stream, "%s%s%s%f%s", fio, 30, initials, 5, yearBorn, 5, &salary, admissionDate, 11);

    if (readSuccess < 5) return readSuccess;

    strcat(fio, " "); strcat(fio, initials);

    return readSuccess;
}

int Worker::get_years_working(const char* today) {
    int yearDif = atoi(&today[6]) - atoi(&admissionDate[6]);

    int monthDif = 10 * today[3] + today[4] - 10 * admissionDate[3] - admissionDate[4];

    if (monthDif < 0) {
        yearDif--;
    }
    else if (!monthDif) {
        int dayDif = 10 * today[0] + today[1] - 10 * admissionDate[0] - admissionDate[1];

        if (dayDif < 0) {
            yearDif--;
        }
    }

    return yearDif;
}

// --------------------------------------------------------------------

WorkerBase::WorkerBase(int _maxSize) {
    workers = new Worker[_maxSize];
    maxSize = _maxSize;
    realSize = 0;
}
WorkerBase::WorkerBase(const char* fileName, int maxSize) : WorkerBase(maxSize) {
    FILE* f; fopen_s(&f, fileName, "r");

    if (!f) throw fileName;

    Worker worker_buffer;
    while (worker_buffer.scan(f) == 5) {
        add_worker(worker_buffer);
    }

    fclose(f);
}
WorkerBase::WorkerBase(const WorkerBase& _base) : WorkerBase(_base.maxSize) {
    realSize = _base.realSize;

    for (int i = 0; i < realSize; i++) {
        workers[i] = _base.workers[i];
    }

};
WorkerBase::~WorkerBase() {
    delete[] workers;
}

WorkerBase& WorkerBase::operator =(const WorkerBase& _base) {
    if (this == &_base) return *this;

    if (maxSize != _base.maxSize) {
        delete[] workers;
        workers = new Worker[_base.maxSize];
    }

    realSize = _base.realSize;
    maxSize = _base.maxSize;

    for (int i = 0; i < realSize; i++) {
        workers[i] = _base.workers[i];
    }

    return *this;
}

void WorkerBase::add_worker(const Worker& _worker) {
    while (realSize >= maxSize) {
        maxSize *= 2;
        Worker* bigger_base = new Worker[maxSize];

        for (int i = 0; i < realSize; i++) {
            bigger_base[i] = workers[i];
        }

        delete[] workers;
        workers = bigger_base;
    }

    workers[realSize++] = _worker;
}
void WorkerBase::delete_worker(char* workerFio) {
    for (int i = 0; i < realSize; i++) {
        if (strcmp(workers[i].get_fio(), workerFio) == 0) {
            workers[i] = workers[--realSize];
            return;
        }
    }

    throw workerFio;
}
void WorkerBase::change_fio(char* oldWorkerFio, char* newWorkerFio) {
    for (int i = 0; i < realSize; i++) {
        if (strcmp(workers[i].get_fio(), oldWorkerFio) == 0) {
            workers[i].set_fio(newWorkerFio);
            return;
        }
    }

    throw oldWorkerFio;
}
void WorkerBase::change_salary(char* workerFio, float newSalary) {
    for (int i = 0; i < realSize; i++) {
        if (strcmp(workers[i].get_fio(), workerFio) == 0) {
            workers[i].set_salary(newSalary);
            return;
        }
    }

    throw workerFio;
}

void WorkerBase::print() {
    for (int i = 0; i < realSize; i++) {
        workers[i].print();
    }
    printf("real size = %d, max size = %d\n\n", realSize, maxSize);
}

// -----------------------------------------------------------------------------
char** FindWorkersWithXp(Worker* workers, int n, const char* today, int yearsWorking) {
    char** names = new char* [n];
    for (int i = 0; i < n; i++) {
        names[i] = new char[60];
        names[i][0] = '\0';
    }

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (workers[i].get_years_working(today) > yearsWorking) {
            strcpy(names[j++], workers[i].get_fio());
        }
    }

    return names;
}
void PrintStrArray(char** _array, int n) {
    for (int i = 0; i < n && strcmp(_array[i], "\0"); i++) {
        puts(_array[i]);
    }
}