#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>
#include <memory>

using namespace std;

class Figure {
public:
	virtual void Print() = 0;
	virtual void Write(FILE* out) = 0;
	virtual ~Figure() {}
};

const unsigned long long Rec_Id = 1;
const unsigned long long Romb_Id = 2;
const unsigned long long Tr_Id = 3;

template <typename T>
class Rectangle: public Figure{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
	Rectangle(){};
	Rectangle(T x,T y,T a1, T b1): t(x,y), a(a1), b(b1){};

	void Print() override {
		pair<double,double> t2(t.first + a, t.second );
		pair<double,double> t3(t.first + a, t.second + b);
		pair<double,double> t4(t.first, t.second + b);
		cout << "------------------" << endl;
		cout << "Rectangle" << endl;
		cout << "(" << t4.first << "," << t4.second << ") " 
		<< "(" << t3.first << "," << t3.second << ")"
		<< endl << endl << "(" << t.first  << ","
		<< t.second << ") " << "(" << t2.first << ","
		<< t2.second << ")" << endl;
	}

	void Write(FILE* out) override {
		fwrite(&Rec_Id, sizeof(unsigned long long), 1, out);
		fwrite(&t.first, sizeof(T), 1, out);
		fwrite(&t.second, sizeof(T), 1, out);
		fwrite(&a, sizeof(T), 1, out);
		fwrite(&b, sizeof(T), 1, out);
	}
};

template <typename T>
class Romb: public Figure{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
	Romb(T x,T y,T a1, T b1): t(x,y), a(a1), b(b1){};

	void Print() override {
		pair<T,T> t2(t.first,t.second+b);
		pair<T,T> t3(t.first + a/2,t.second+b/2);
		pair<T,T> t4(t.first - a/2,t.second+b/2);
		cout << "------------------" << endl;
		cout << "Romb" << endl;
		cout << "    (" << t2.first << "," << t2.second << ")     " << endl
		<< endl << "(" << t4.first << "," << t4.second << ")   " << "("
		<< t3.first << "," << t3.second << ")" << endl << endl << "    ("
		<< t.first << "," << t.second << ")" << endl;
	}

	void Write(FILE* out) override {
		fwrite(&Romb_Id, sizeof(unsigned long long), 1, out);
		fwrite(&t.first, sizeof(T), 1, out);
		fwrite(&t.second, sizeof(T), 1, out);
		fwrite(&a, sizeof(T), 1, out);
		fwrite(&b, sizeof(T), 1, out);
	}

};

template <typename T>
class Trapeze: public Figure{
	public:
		using type = T;
		pair<T,T> t;
		T a;
		T b;
		T c;
	Trapeze(T x,T y,T a1, T b1, T s1): t(x,y), a(a1), b(b1), c(s1){};

	void Print() override {
		pair<T,T> t2(t.first,t.second + a);
		pair<T,T> t3(t.first + (a - b)/2, t.second + c);
		pair<T,T> t4(t2.first + a - (a - b)/2, t.second + c);
		cout << "------------------" << endl;
		cout << "Trapeze" << endl;
		cout << "  (" << t3.first << "," << t3.second << ")  (" 
		<< t4.first << "," << t4.second << ")" << endl << endl
		<< "(" << t.first << "," << t.second << ")              ("
		<< t2.first << "," << t2.second << ")" << endl;
	}

	void Write(FILE* out) override {
		fwrite(&Tr_Id, sizeof(unsigned long long), 1, out);
		fwrite(&t.first, sizeof(T), 1, out);
		fwrite(&t.second, sizeof(T), 1, out);
		fwrite(&a, sizeof(T), 1, out);
		fwrite(&b, sizeof(T), 1, out);
		fwrite(&c, sizeof(T), 1, out);
	}
};


template<class T, class FIGURE>
class Factory;

template<class T>
class Factory<T, Rectangle<T> > {
public:
	static shared_ptr<Figure> Create() {
		pair <T,T> c;
		T a,b;
		printf("Введите координату нижней левой точки прямоугольника и длины сторон, прилегающих к ней, начиная с горизонтальной\n");
		cin >> c.first >> c.second >> a >> b;
		if((!cin)||(a<=0)||(b<=0)){
			printf("Введены неверные данные, взяты значения по умолчанию: 0 0 1 1\n");
			c.first = 0;
			c.second = 0;
			a = 1;
			b = 1;
		}
		Rectangle<T> * rect = new Rectangle<T>(c.first,c.second, a, b);
		return shared_ptr<Figure>(rect);
	}

	static shared_ptr<Figure> Read(FILE* in) {
		pair <T,T> c;
		T a,b;
		fread(&c.first, sizeof(T), 1, in);
		fread(&c.second, sizeof(T), 1, in);
		fread(&a, sizeof(T), 1, in);
		fread(&b, sizeof(T), 1, in);

		Rectangle<T> * rect = new Rectangle<T>(c.first,c.second, a, b);
		return shared_ptr<Figure>(rect);
	}
};

template<class T>
class Factory<T, Romb<T> > {
public:
	static shared_ptr<Figure> Create() {
		pair <T,T> c;
		T a,b;
		printf("Введите координату нижней точки ромба и длину его диагоналей, начиная с горизонтальной\n");
		cin >> c.first >> c.second >> a >> b;
		if((!cin)||(a<=0)||(b<=0)){
			printf("Введены неверные данные, взяты значения по умолчанию: 0 0 1 1\n");
			c.first = 0;
			c.second = 0;
			a = 1;
			b = 1;
		}
		Romb<T> * romb = new Romb<T>(c.first,c.second, a, b);
		return shared_ptr<Figure>(romb);
	}

	static shared_ptr<Figure> Read(FILE* in) {
		pair <T,T> c;
		T a,b;
		fread(&c.first, sizeof(T), 1, in);
		fread(&c.second, sizeof(T), 1, in);
		fread(&a, sizeof(T), 1, in);
		fread(&b, sizeof(T), 1, in);

		Romb<T> * romb = new Romb<T>(c.first, c.second, a, b);
		return shared_ptr<Figure>(romb);
	}
};

template<class T>
class Factory<T, Trapeze<T> > {
public:
	static shared_ptr<Figure> Create() {
		pair <T,T> c;
		T a,b,d;
		printf("Введите координату нижней левой точки трапеции, наибольшее основание, наименьшее основание и длину высоты (трапеция равнобедренная)\n");
		cin >> c.first >> c.second >> a >> b >> d;
		if((a<=0)||(b<=0)||(d<=0)){
			printf("Введены неверные данные, взяты значения по умолчанию 0 0 5 2 4\n");
			c.first = 0;
			c.second = 0;
			a = 10;
			b = 5;
			d = 5;
		}
		Trapeze<T> * tr = new Trapeze<T>(c.first,c.second, a, b, d);
		return shared_ptr<Figure>(tr);
	}

	static shared_ptr<Figure> Read(FILE* in) {
		pair <T,T> c;
		T a,b,d;
		fread(&c.first, sizeof(T), 1, in);
		fread(&c.second, sizeof(T), 1, in);
		fread(&a, sizeof(T), 1, in);
		fread(&b, sizeof(T), 1, in);
		fread(&d, sizeof(T), 1, in);

		Trapeze<T> * tr = new Trapeze<T>(c.first,c.second, a, b, d);
		return shared_ptr<Figure>(tr);
	}
};

#endif