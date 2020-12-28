
/*
 * Воронов К.М. М8О-207Б-19
 * Создать приложение, которое будет считывать из стандартного
 * ввода данные фигур, согласно варианту задания, выводить их
 * характеристики на экран и записывать в файл. Фигуры могут
 * задаваться как своими вершинами, так и другими характеристиками
 * (например, координата центра, количество точек и радиус).
 * Программа должна:
 * 1. Осуществлять ввод из стандартного ввода данных фигур,
 *    согласно варианту задания;
 * 2. Программа должна создавать классы, соответствующие введенным
 *    данных фигур;
 * 3. Программа должна содержать внутренний буфер, в который
 *    помещаются фигуры. Для создания буфера допускается
 *    использовать стандартные контейнеры STL. Размер буфера
 *    задается параметром командной строки. Например, для буфера
 *    размером 10 фигур: oop_exercise_08 10
 * 4. При накоплении буфера они должны запускаться на
 *    асинхронную обработку, после чего буфер должен очищаться;
 * 5. Обработка должна производится в отдельном потоке;
 * 6. Реализовать два обработчика, которые должны обрабатывать
 *    данные буфера:
 *    1. Вывод информации о фигурах в буфере на экран;
 *    2. Вывод информации о фигурах в буфере в файл. Для каждого
 *       буфера должен создаваться файл с уникальным именем.
 * 7. Оба обработчика должны обрабатывать каждый введенный буфер.
 *    Т.е. после каждого заполнения буфера его содержимое должно
 *    выводиться как на экран, так и в файл.
 * 8. Обработчики должны быть реализованы в виде лямбда-функций и
 *    должны хранится в специальном массиве обработчиков. Откуда и
 *    должны последовательно вызываться в потоке – обработчике.
 * 9. В программе должно быть ровно два потока (thread). Один
 *    основной (main) и второй для обработчиков;
 * 10. В программе должен явно прослеживаться шаблон
 *    Publish-Subscribe. Каждый обработчик должен быть реализован
 *    как отдельный подписчик.
 * 11. Реализовать в основном потоке (main) ожидание обработки
 *    буфера в потоке-обработчике. Т.е. после отправки буфера на
 *    обработку основной поток должен ждать, пока поток обработчик
 *    выведет данные на экран и запишет в файл.

 Вариант 27 Прямоугольник ромб трапеция
 */

#include<iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <functional>
#include"figure.hpp"
#include"publish_subscribe.hpp"

using namespace std;

Developer < shared_ptr<Figure> > d;

FILE *file = NULL;

string mrandom() {
	unsigned int size = rand() % 10;
	string s = "";
	char c;
	for (int i = 0; i < size; ++i) {
		c = rand() % 26 + 'a';
		s += c;
	}
	return s;
}

void threadFunction() {

	function<void(shared_ptr<Figure> fig)> Print_fig = [](shared_ptr<Figure> fig) {
		fig->Print();
	};

	function<void(shared_ptr<Figure> fig)> Write_fig = [](shared_ptr<Figure> fig) {
		fig->Write(file);
	};

	vector<function<void(shared_ptr<Figure> fig)>> functions({Print_fig, Write_fig});

	bool a = true;
	while(a) {
		if (!d.Empty()) {

			if (d.Front() == NULL) {
				break;
			}

			file = fopen((mrandom()).c_str(), "wb"); 

			while (!d.Empty()) {
				shared_ptr<Figure> f_3 = d.Front();
				d.Pop();
				for (auto func : functions) {
					func(f_3);
				}

			}
			fclose(file);
		}
	}
} 

int main(int argc, char** argv) {

	srand(time(NULL));

	unsigned long long size = stoi(string(argv[1]));
	if (size <= 0) {
		printf("Неверный размер буффера\n");
		return -1;
	}

	thread thread_2(threadFunction);
	vector< shared_ptr<Figure> > figures;
	unsigned long long id;

	printf("Введите 1, чтобы добавить прямоугольник\n");
	printf("Введите 2, чтобы добавить ромб\n");
	printf("Введите 3, чтобы добавить трапецию\n");

	while (cin >> id) {

		if (!cin || id <= 0 || id > 3) {
			printf("Вы ввели неверную команду\n");
			thread_2.join();
			return -1;
		}

		if (id == Rec_Id) {
			figures.push_back(Factory<double, Rectangle<double>>:: Create());
		} else {
			if (id == Romb_Id) {
				figures.push_back(Factory<double, Romb<double>>:: Create());
			} else {
				if (id == Tr_Id) {
					figures.push_back(Factory<double, Trapeze<double>>:: Create());
				}
			}
		}

		if (figures.size() == size) {
			for (int i = 0; i < figures.size(); ++i) {
				d.Add(figures[i]);
			}
			while (!d.Empty()) {}
			figures.clear();
		}

		printf("Введите 1, чтобы добавить прямоугольник\n");
		printf("Введите 2, чтобы добавить ромб\n");
		printf("Введите 3, чтобы добавить трапецию\n");

	}	

	for (int i = 0; i < figures.size(); ++i) {
		d.Add(figures[i]);
	}
	figures.clear();
	shared_ptr<Figure> null = NULL;
	d.Add(null);
	thread_2.join();

}