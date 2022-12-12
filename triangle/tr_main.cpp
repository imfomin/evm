#include <iostream>
#include <fstream>
#include "triangle.hpp"

int main() {
	setlocale(LC_CTYPE, "ru");

	FILE* f; fopen_s(&f, "coords.txt", "r");

	if (!f) return 1;

	Triangle t1; t1.scan(f);
	Triangle t2; t2.scan(f);
	Triangle t3; t3.scan(f);

	fclose(f);

	printf("1. Ввод t1\n");
	printf("2. Ввод t2\n");
	printf("3. Ввод t3\n");
	printf("4. Печать\n");
	printf("5. Перемещение\n");
	printf("6. Проверка вхождения\n");
	printf("default. Выйти\n");

	bool looping = true;
	int operation; char fix;
	while (looping) {
		scanf_s("%d%c", &operation, &fix, 1);

		switch (operation) {
		case 1:
			t1.scan();
			break;
		case 2:
			t2.scan();
			break;
		case 3:
			t3.scan();
			break;
		case 4:
			printf("Все треугольники:\n");

			t1.print();
			t2.print();
			t3.print();

			break;
		case 5:
			float dx, dy;
			scanf_s("%f%f%c", &dx, &dy, &fix, 1);

			t1.transform(Point(dx, dy));
			t2.transform(Point(dx, dy));
			t3.transform(Point(dx, dy));

			break;
		case 6:
			printf("t1%s входит в t2\n", t1.is_in(t2) ? "\0" : " не");
			printf("t2%s входит в t3\n", t2.is_in(t3) ? "\0" : " не");

			break;
		default:
			looping = false;
		}

	}

	const int n = 10;
	Triangle triangles[n];

	fopen_s(&f, "coords.txt", "r");

	if (!f) return 1;

	printf("Все треугольники:\n");
	for (int i = 0; i < n; i++) {
		triangles[i].scan(f);
		triangles[i].print();
	}

	printf("\nТреугольник наиболльшей площади:\n");
	FindBiggestTriangle(triangles, n).print();

	fclose(f);

	return 0;
}