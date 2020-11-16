/* Воронов К.М.  
Разработать шаблоны классов согласно варианту задания. 
Параметром шаблона должен являться скалярный тип данных задающий тип данных 
для оси координат. Классы должны иметь публичные поля. Фигуры являются 
фигурами вращения, т.е. равносторонними (кроме трапеции и прямоугольника). 
Для хранения координат фигур необходимо использовать шаблон  std::pair.
Создать шаблон динамической коллекцию и итератор.
*/



#include <iostream>
#include <string>
#include <algorithm>
#include"vector.hpp"


template <typename T>
class Rectangle{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
	Rectangle(){};
	Rectangle(T x,T y,T a1, T b1): t(x,y), a(a1), b(b1){};

	friend ostream &operator<< (ostream& out, const Rectangle<double> &p);

};



double square(Rectangle<double> p) {
	return p.a*p.b;
}

void print2(Rectangle<double> p) {

	pair<double,double> t2((p.t).first + p.a, (p.t).second );
	pair<double,double> t3((p.t).first + p.a, (p.t).second + p.b);
	pair<double,double> t4((p.t).first, (p.t).second + p.b);

cout << "(" << t4.first << "," << t4.second << ") " 
	 << "(" << t3.first << "," << t3.second << ")"
	 << endl << endl << "(" << (p.t).first  << ","
	 << (p.t).second << ") " << "(" << t2.first << ","
	 << t2.second << ")" << endl << "-----------------" << endl;
}


void Add(TVector<Rectangle<double>> &v, TVector<Rectangle<double>>::Iterator &begin, Rectangle<double> r){

	double x,y,a,b;


	if (v.size() < 2) {
		printf("Введите координату нижней левой точки прямоугольника и длины сторон, прилегающих к ней, начиная с горизонтальной\n");
		cin >> x >> y >> a >> b;
		if ((a<0) || (b<0) || !cin){
			cout << "Введены неверные данные" << endl;
			return;
		}
	    (r.t).first = x;
		(r.t).second = y;
		r.a = a;
		r.b = b;
		v.insert(r, begin);
		return;
	}

	int index;
	printf("Введите индекс элемента массива, перед которым добавить элемент\n");
		cin >> index;
		begin = v.begin();
		if(index > v.size() || index < 0 || !cin){
			cout << "Введены неверные данные" << endl;
			return;
		}

		while(begin.index < index) {
			++begin;
		}

		printf("Введите координату нижней левой точки прямоугольника и длины сторон, прилегающих к ней, начиная с горизонтальной\n");
		cin >> x >> y >> a >> b;
		if ((a<0) || (b<0) || !cin){
			cout << "Введены неверные данные" << endl;
			return;
		}
		(r.t).first = x;
		(r.t).second = y;
		r.a = a;
		r.b = b;
		v.insert(r, begin);
		return;

}

void Delete(TVector<Rectangle<double>> &v, TVector<Rectangle<double>>::Iterator &begin){

	int index;

	if (v.size() == 0){
		cout <<"Вектор пуст" << endl;
		return;
	}

	printf("Введите индекс элемента для удаления\n");
		cin >> index;
		if((index < 0) || (!cin) || (index > v.size())) {
		cout << "Введены неверные данные" << endl;
		return;
	}
		begin = v.begin();
		while(begin.index < index) {
			++begin;
		}
		v.erase(begin);
	return;
}

double s;

bool ifsquare(Rectangle<double> p){
	if (square(p) < s)
		return true;
	else return false;
}

void Square(TVector<Rectangle<double>> ::Iterator &it,TVector<Rectangle<double>> v ){

	printf("Введите площадь\n");
	cin >> s;
	if(!cin){
		cout << "Введены неверные данные" << endl;
		return;
	}
	int a;
	a = count_if(v.begin(),v.end(), ifsquare);
	cout << a << endl;

}


void Print(TVector<Rectangle<double>> ::Iterator &it,TVector<Rectangle<double>> v ){

	if (v.size() == 0){
		cout <<"Вектор пуст" << endl; 
		return;
	}

	for_each(v.begin(), v.end(),print2);
	return;
}

void Menu(){
	printf("Введите 1, чтобы добавить элемент\n");
    printf("Введите 2, чтобы удалить элемент\n");
    printf("Введите 3, чтобы вывести вектор\n");
    printf("Введите 4, чтобы вывести количество фигур, меньших заданной площади\n");
    printf("Введите 5, чтобы вывести меню\n");
}

int main(){
	TVector<Rectangle<double>> v;

	auto begin = v.begin();
	auto end = v.end();

	double x,y,a,b;

	int input;

    Rectangle<double> r;

    printf("Введите 1, чтобы добавить элемент\n");
    printf("Введите 2, чтобы удалить элемент\n");
    printf("Введите 3, чтобы вывести вектор\n");
    printf("Введите 4, чтобы вывести фигуры меньшей заданной площади\n");
    printf("Введите 5, чтобы вывести меню\n");

    while (cin >> input) {
    	if (!cin){
		cout << "Введены неверные данные" << endl;
		return -1;
    	}
    	switch(input){
    		case 1:
	    		Add(v,begin,r);
	    		break;
    		case 2:
	    		Delete(v,begin);
	    		break;
    		case 3:
    			Print(begin,v);
    			break;
    		case 4:
    			Square(begin,v);
    			break;
    		case 5:
    			Menu();
    			break;
    		default:
  				cout<<"Вы ввели неверную команду"<<std::endl;
			  	return -1;
			  	break;
    	}
    }
}
