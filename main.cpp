/*Воронов К.М.
Разработать классы согласно варианту задания, классы должны наследоваться 
от базового класса Figure. Фигуры являются фигурами вращения. 
Все классы должны поддерживать набор общих методов:
  1.Вычисление геометрического центра фигуры;
  2.Вывод в стандартный поток вывода std::cout координат вершин фигуры; 
  3.Вычисление площади фигуры.

Вариант 27

Прямоугольник ромб трапеция
*/

#include "iostream"
#include <vector>
#include <valarray>

using namespace std;

class Coord{
 public:
 double x,y;

 Coord(): x(0),y(0){};
 Coord(double a, double b): x(a),y(b){};
 	friend ostream & operator<<(ostream &out,const Coord &a);
 ~Coord(){};

};

ostream & operator<<(ostream &out,const Coord &a){
	out<<"("<<a.x<<","<<a.y<<")";
	return out;
}

class Figure{
 public:

 virtual double square() = 0;
 virtual Coord centre() = 0;
 virtual void print()=0;

};


class Pramougol: public Figure{
public: 

Coord t;
double a,b;

Pramougol():a(0),b(0),t(){};
Pramougol(double x,double y,double a1, double b1): a(a1), b(b1), t(x,y){};

double square() override{
	return a*b;
}

Coord centre() override {
	Coord t2(t.x+a,t.y);
	Coord t3(t.x+a,t.y+b);
	Coord t4(t.x,t.y+b);
	t2.x=(t.x+t2.x+t3.x+t4.x)/4;
	t2.y=(t.y+t2.y+t3.y+t4.y)/4;
	return (t2);
}

void print() override {
	Coord t2(t.x+a,t.y);
	Coord t3(t.x+a,t.y+b);
	Coord t4(t.x,t.y+b);

	cout << t4 << " "<< t3 << endl<<endl<<t<<" "<<t2<<endl;
}
};

class Romb: public Figure{
public:

Coord t;
double a,b;

Romb():t(),a(0),b(0){};
Romb(double x,double y,double a1, double b1): a(a1),b(b1),t(x,y){};

double square() override{
	return a*b/2;
}

Coord centre() override {
	Coord t2(t.x,t.y+b);
	Coord t3(t.x+a/2,t.y+b/2);
	Coord t4(t.x-a/2,t.y+b/2);
	t2.x=(t.x+t2.x+t3.x+t4.x)/4;
	t2.y=(t.y+t2.y+t3.y+t4.y)/4;
	return t2;
}

void print() override {
	Coord t2(t.x,t.y+b);
	Coord t3(t.x+a/2,t.y+b/2);
	Coord t4(t.x-a/2,t.y+b/2);
	cout<<"     "<<t2<<endl<<endl<<t4<<"   "<<t3<<endl<<endl <<"     "<<t<<endl;
}
};

class Trapecia: public Figure{
public:

Coord t;
double a,b,c;

Trapecia():a(0),b(0),c(0),t(){};
Trapecia(double x,double y,double a1, double b1,double c1): a(a1), b(b1),c(c1), t(x,y){};

double square() override{
	double g = (a - b)/2;
	g=sqrt(c*c-g*g);
	return((a+b)*g/2);
}

Coord centre() override {
	double g1 = (a - b)/2;
	double g2=sqrt(c*c-g1*g1);
	Coord t2(t.x+a,t.y);
	Coord t3(t.x+g1,t.y+g2);
	Coord t4(t2.x-g1,t.y+g2);
	t2.x=(t.x+t2.x+t3.x+t4.x)/4;
	t2.y=(t.y+t2.y+t3.y+t4.y)/4;
	return t2;
}

void print() override {
	double g1 = (a - b)/2;
	double g2=sqrt(c*c-g1*g1);
	Coord t2(t.x+a,t.y);
	Coord t3(t.x+g1,t.y+g2);
	Coord t4(t2.x-g1,t.y+g2);
	cout<<"  "<<t3<<"  "<<t4<<endl<<endl<<t<<"                  "<<t2<<endl;
}
};

int main(){
vector<Figure*> f(3);
double x,y,a,b,c,pl;
Coord cen;

printf("Введите координату нижней левой точки прямоугольника и длины сторон, прилегающих к ней, начиная с горизонтальной\n");
cin>>x>>y>>a>>b;
if((!cin)||(a<0)||(b<0)){
	printf("Введены неверные данные\n");
	return 1;
}
f[0] = new Pramougol(x,y,a,b);
pl=f[0]->square();
cout<<"Площадь - "<<pl<<endl;
cen=f[0]->centre();
cout<<"Центр - "<<cen<<endl;
cout<<"Координаты"<<endl;
f[0]->print();

printf("Введите координату нижней точки ромба и длину его диагоналей, начиная с горизонтальной\n");
cin>>x>>y>>a>>b;
if((!cin)||(a<0)||(b<0)){
	printf("Введены неверные данные\n");
	return 1;
}
f[1] = new Romb(x,y,a,b);
pl=f[1]->square();
cout<<"Площадь - "<<pl<<endl;
cen=f[1]->centre();
cout<<"Центр - "<<cen<<endl;
cout<<"Координаты"<<endl;
f[1]->print();

printf("Введите координату нижней левой точки трапеции, наибольшее основание, наименьшее основание и длину боковой стороны\n");
cin>>x>>y>>a>>b>>c;
if(!cin){
	printf("Введены неверные данные\n");
	return 1;
}
double g1 = (a - b)/2;
double g2=sqrt(c*c-g1*g1);
if((a<0)||(b<0)||(c<0)||(g1+c<g2)||(g2+g1<c)||(g2+c<g1)||(g1<=0)||(g2<=0)){
	printf("Введены неверные данные\n");
	return 1;
}
f[2] = new Trapecia(x,y,a,b,c);
pl=f[2]->square();
cout<<"Площадь - "<<pl<<endl;
cen=f[2]->centre();
cout<<"Центр - "<<cen<<endl;
cout<<"Координаты"<<endl;
f[2]->print();

cout<<"Общая площадь - "<<f[0]->square()+f[1]->square()+f[2]->square()<<endl;

}
