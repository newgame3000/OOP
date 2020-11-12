/*Воронов К.М.
Разработать шаблоны классов согласно варианту задания.  
Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат.
Классы должны иметь только публичные поля. В классах не должно быть методов, только поля. 
Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника.
 Для хранения координат фигур необходимо использовать шаблон  std::pair.

Вариант 27

Прямоугольник ромб трапеция
*/




#include "iostream"
#include <vector>
#include <valarray>
#include <tuple>

using namespace std;

template <typename T>
class Pramougol{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
	Pramougol(){};
	Pramougol(T x,T y,T a1, T b1): t(x,y), a(a1), b(b1){};

};

template <typename T>
class Romb{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
	Romb(T x,T y,T a1, T b1): t(x,y), a(a1), b(b1){};
};

template <typename T>
class Trapecia{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
		T c;
	Trapecia(T x,T y,T a1, T b1, T s1): t(x,y), a(a1), b(b1), c(s1){};
};

template <int i = 0, class... Ts>
void print1(tuple<Ts ...> t){
	if constexpr (i < tuple_size<decltype(t)>::value){
		print2(get<i>(t));
		cout << "-----------------------"<< endl;
		print1< i + 1, Ts ... >(t);
		}
		else {
		return;
	}
}

template <int i = 0, class... Ts>
void square1(tuple<Ts ...> t,double pl){
	if constexpr (i < tuple_size<decltype(t)>::value){
		pl+=square2(get<i>(t));
		square1< i + 1, Ts ... >(t, pl);
		}
		else {
		cout << "Общая площадь фигур - " << pl << endl;
		return;
	}
}

template <typename T>
T square2(Pramougol<T> p) {
return p.a*p.b;
}

template <typename T>
T square2(Romb<T> p) {
return p.a*p.b/2;
}

template <typename T>
T square2(Trapecia<T> p) {
	double g = (p.a - p.b)/2;
	g=sqrt(p.c*p.c-g*g);
	return((p.a+p.b)*g/2);
}

template <typename T>
void print2(Pramougol<T> p) {

	pair<T,T> t2((p.t).first + p.a, (p.t).second );
	pair<T,T> t3((p.t).first + p.a, (p.t).second + p.b);
	pair<T,T> t4((p.t).first, (p.t).second + p.b);

cout << "(" << t4.first << "," << t4.second << ") " 
	 << "(" << t3.first << "," << t3.second << ")"
	 << endl << endl << "(" << (p.t).first  << ","
	 << (p.t).second << ") " << "(" << t2.first << ","
	 << t2.second << ")" << endl;
}

template <typename T>
void print2(Romb<T> p) {

	pair<T,T> t2((p.t).first,(p.t).second+p.b);
	pair<T,T> t3((p.t).first + p.a/2,(p.t).second+p.b/2);
	pair<T,T> t4((p.t).first - p.a/2,(p.t).second+p.b/2);

cout << "    (" << t2.first << "," << t2.second << ")     " << endl
	 << endl << "(" << t4.first << "," << t4.second << ")   " << "("
	 << t3.first << "," << t3.second << ")" << endl << endl << "    ("
	 << (p.t).first << "," << (p.t).second << ")" << endl;
}

template <typename T>
void print2(Trapecia<T> p) {

	T g1 = (p.a - p.b)/2;
	T g2=sqrt(p.c*p.c-g1*g1);
	pair<T,T> t2((p.t).first,(p.t).second+p.b);
	pair<T,T> t3((p.t).first + g1, (p.t).second + g2);
	pair<T,T> t4(t2.first-g1,(p.t).second + g2);

cout << "  (" << t3.first << "," << t3.second << ")  (" 
	 << t4.first << "," << t4.second << ")" << endl << endl
	 << "(" << (p.t).first << "," << (p.t).second << ")              ("
	 << t2.first << "," << t2.second << ")" << endl;

}

int main(){
	printf("Введите координату нижней левой точки прямоугольника и длины сторон, прилегающих к ней, начиная с горизонтальной (тип double)\n");
	double x,y,a,b,c;
	cin >> x >> y >> a >> b; 

	if((!cin)||(a<=0)||(b<=0)){
	printf("Введены неверные данные\n");
	return 1;
	}

	Pramougol<double> p1(x,y,a,b);

	printf("Введите координату нижней левой точки прямоугольника и длины сторон, прилегающих к ней, начиная с горизонтальной (тип int)\n");
	int x1,y1,a1,b1,c1;
	cin >> x1 >> y1 >> a1 >> b1;

	if((!cin)||(a1<=0)||(b1<=0)){
	printf("Введены неверные данные\n");
	return 1;
	}

	Pramougol<int> p2(x1,y1,a1,b1);

	printf("Введите координату нижней точки ромба и длину его диагоналей, начиная с горизонтальной (тип double)\n");
	cin >> x >> y >> a >> b;

	if((!cin)||(a<=0)||(b<=0)){
	printf("Введены неверные данные\n");
	return 1;
	}

	Romb<double> r1(x,y,a,b);

	printf("Введите координату нижней точки ромба и длину его диагоналей, начиная с горизонтальной (тип int)\n");
	cin >> x1 >> y1 >> a1 >> b1;

	if((!cin)||(a1<=0)||(b1<=0)){
	printf("Введены неверные данные\n");
	return 1;
	}

	Romb<int> r2(x1,y1,a1,b1);

	printf("Введите координату нижней левой точки трапеции, наибольшее основание, наименьшее основание и длину боковой стороны (тип double)\n");
	cin>>x>>y>>a>>b>>c;

	if(!cin){
		printf("Введены неверные данные\n");
		return 1;
	}

	double g1 = (a - b)/2;
	double g2=sqrt(c*c-g1*g1);
	if((a<=0)||(b<=0)||(c<0)||(g1+c<g2)||(g2+g1<c)||(g2+c<g1)||(g1<=0)||(g2<=0)){
		printf("Введены неверные данные\n");
		return 1;
	}

	Trapecia<double> t1(x,y,a,b,c);

	printf("Введите координату нижней левой точки трапеции, наибольшее основание, наименьшее основание и длину боковой стороны (тип int)\n");
	cin>>x1>>y1>>a1>>b1>>c1;

	if(!cin){
		printf("Введены неверные данные\n");
		return 1;
	}

	int g11 = (a1 - b1)/2;
	int g22=sqrt(c1*c1-g11*g11);
	if((a1<=0)||(b1<=0)||(c1<=0)||(g11+c1<g22)||(g22+g11<c1)||(g22+c1<g11)||(g11<=0)||(g22<=0)){
		printf("Введены неверные данные\n");
		return 1;
	}

	Trapecia<int> t2(x1,y1,a1,b1,c1);

	tuple<Pramougol<double>,Pramougol<int>,Romb<double>,Romb<int>,Trapecia<double>,Trapecia<int>> t{p1,p2,r1,r2,t1,t2};
	print1(t);
	square1(t,0);
}