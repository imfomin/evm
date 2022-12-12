#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "ex.hpp"

using namespace std;

//int main() {
//	setlocale(LC_CTYPE, "ru");
//
//	Matrix M1, M2, M3;
//
//	ifstream in("matrixes.txt");
//	in >> M1 >> M2 >> M3;
//	
//	int operation;
//	int n = 1;
//	printf("%d. Сложить\n", n++);
//	printf("%d. Вычесть\n", n++);
//	printf("%d. Умножить\n", n++);
//	printf("%d. Сравнить\n", n++);
//	printf("%d. Транспонировать\n", n++);
//	printf("%d. Напечатать\n", n++);
//	printf("default. Выйти\n");
//
//	bool looping = true;
//	while (looping) {
//		cin >> operation;
//
//		try {
//			switch (operation) {
//			case 1:
//				cout << "M1 + M2:\n";
//				cout << M1 + M2 << '\n';
//				break;
//			case 2:
//				cout << "M1 - M2:\n";
//				cout << M1 - M2 << '\n';
//				break;
//			case 3:
//				cout << "M1 * M2:\n";
//				cout << M1 * M2 << '\n';
//				break;
//			case 4:
//				cout << "M1 " << (M1 == M2 ? "==" : "!=") << " M2" << '\n';
//				cout << "M2 " << (M2 == M3 ? "==" : "!=") << " M3" << '\n';
//				break;
//			case 5:
//				M1.transpose();
//
//				cout << "M1:\n";
//				cout << M1 << '\n';
//				break;
//			case 6:
//				cout << "M1:\n";
//				cout << M1 << '\n';
//
//				cout << "M2:\n";
//				cout << M2 << '\n';
//
//				cout << "M3:\n";
//				cout << M3 << '\n';
//				break;
//			default:
//				looping = false;
//			}
//		}
//		catch (const char* msg) {
//			cout << msg << '\n';
//		}
//	}
//
//	return 0;
//}

int main() {
	Matrix A, B, C;
	ifstream in("matrixes2.txt");
	in >> A >> B >> C;

	try {
		Matrix D = C * (A + B);
		cout << D;
	}
	catch (error& err) {
		err.print();
	}

	cout << "max element in A: " << A.max_element() << '\n';

	return 0;
}

//int main() {
//	setlocale(LC_CTYPE, "rus");
//
//	ifstream in("sqmatrixes.txt");
//
//	SqMatrix M1; in >> M1;
//	SqMatrix M2; in >> M2;
//	SqMatrix M3; in >> M3;
//
//	int operation;
//	int n = 1;
//	printf("%d. Сложить\n", n++);
//	printf("%d. Вычесть\n", n++);
//	printf("%d. Умножить\n", n++);
//	printf("%d. Сравнить\n", n++);
//	printf("%d. Транспонировтаь\n", n++);
//	printf("%d. Напечатать\n", n++);
//	printf("%d. Определители\n", n++);
//	printf("%d. Степени\n", n++);
//	printf("default. Выйти\n");
//
//	bool looping = true;
//	while (looping) {
//		cin >> operation;
//
//		try {
//			switch (operation) {
//			case 1:
//				cout << "M1 + M2:\n";
//				cout << M1 + M2 << '\n';
//				break;
//			case 2:
//				cout << "M1 - M2:\n";
//				cout << M1 - M2 << '\n';
//				break;
//			case 3:
//				cout << "M1 * M2:\n";
//				cout << M1 * M2 << '\n';
//				break;
//			case 4:
//				cout << "M1 " << (M1 == M2 ? "==" : "!=") << " M2" << '\n';
//				cout << "M2 " << (M2 == M3 ? "==" : "!=") << " M3" << '\n';
//				break;
//			case 5:
//				M1.transpose();
//
//				cout << "M1:\n";
//				cout << M1 << '\n';
//				break;
//			case 6:
//				cout << "M1:\n";
//				cout << M1 << '\n';
//
//				cout << "M2:\n";
//				cout << M2 << '\n';
//
//				cout << "M3:\n";
//				cout << M3 << '\n';
//				break;
//			case 7:
//				cout << "det(M1) = " << M1.det() << '\n';
//				cout << "det(M2) = " << M2.det() << '\n';
//				cout << "det(M3) = " << M3.det() << '\n';
//			case 8:
//				int power;
//				cout << "Степень: ";
//				cin >> power;
//
//				cout << "M1^" << power << '\n';
//				cout << M1.pow(power) << '\n';
//
//				cout << "M2^" << power << '\n';
//				cout << M2.pow(power) << '\n';
//
//				cout << "M3^" << power << '\n';
//				cout << M3.pow(power) << '\n';
//
//				break;
//			default:
//				looping = false;
//			}
//		}
//		catch (const char* msg) {
//			cout << msg << '\n';
//		}
//	}
//
//	return 0;
//}
