
/* Воронов К.М. М8О-207Б-19
Создать класс Position для работы с географическими координатами. 
Координаты задаются двумя числами широта и долгота. 
Долгота находится в диапазоне от -180 до 180 градусов. 
Широта находится в диапазоне от -90 до 90 градусов. 
Реализовать арифметические операции сложения, вычитания, умножения и деления, 
а также операции сравнения в виде перегрузки операторов.
Необходимо реализовать пользовательский литерал для работы с константами типа Position.
*/


#include <iostream>

using namespace std;

class Position{
public:

	double dol; //-180 180
	double shir; //-90 90

	Position(): dol(0),shir(0) {};
	Position(double a, double b){
		dol=a;
		shir=b;
	}

	friend Position operator+(const Position &a, const Position &b);
	friend Position operator-(const Position &a, const Position &b);
	friend Position operator*(const Position &a, const Position &b);
	friend Position operator/(const Position &a, const Position &b);
	friend bool operator>(const Position &a, const Position &b);
	friend bool operator<(const Position &a, const Position &b);
	friend bool operator==(const Position &a, const Position &b);
	friend ostream & operator << (std::ostream &out, const Position &a);

	~Position(){};

};

double mod(double a,int n){
	int c=a/n;
	return a-c*n;
}

/* Реализация операторов класса */

Position operator+(const Position &a, const Position &b){
	return Position (mod((a.dol+b.dol),180),mod((a.shir+b.shir),90));
}

Position operator-(const Position &a, const Position &b){
	return Position (mod((a.dol-b.dol),180),mod((a.dol-b.dol),90));
}

Position operator*(const Position &a, int ch){
	return Position (mod((a.dol*ch),180),mod((a.shir*ch),90));
}

Position operator/(const Position &a, int ch){
	return Position (mod((a.dol/ch),180),mod((a.shir/ch),90));
}

bool operator>(const Position &a, const Position &b){
	if(a.dol!=b.dol)
		return a.dol>b.dol;
	else
		return	a.shir>b.shir;
}

bool operator<(const Position &a, const Position &b){
	if(a.dol!=b.dol)
		return a.dol<b.dol;
	else
		return	a.shir<b.shir;
}

bool operator==(const Position &a, const Position &b){
	if((a.dol==b.dol)&&(a.shir==b.shir))
		return true;
	else 
		return false;
}

ostream & operator << (std::ostream &out, const Position &a) {
	out << a.dol <<" "<< a.shir ;
	return out;
}

/* Реализация парсера для итерала */

Position operator "" _position(const char* st,  size_t n){
	
	double dol=0,shir=0;

	string s(st);
	int l=0, u=0;
	for(int i = 0; i < n; ++i){
		if(s[i]==','){
			if(u==0){
				dol=stod(s.substr(l,i-l+1));
			}
			l=i+1;
			break;
		}
	}

	shir=stod(s.substr(l,n));

	return Position(dol,shir);
}

int main(){

printf("Пользовательские литералы\n");

cout<<"44,42"_position<<endl;
cout<<"-124,-42"_position<<endl;
cout<<"-12.4,-4.2"_position<<endl;

Position a,b,c;
double ch;
printf("Введите две координаты\n");
cin >> a.dol >> a.shir >> b.dol >> b.shir;
if((!cin) || (a.dol>180) || (a.dol<-180) || (a.shir>90)||(a.shir<-90)|| (b.dol>180) || (b.dol<-180) || (b.shir>90)||(b.shir<-90)){
	printf("Вы ввели неверные координаты\n");
	return 1;
}

printf("Сумма\n");
c = a + b;
cout<<c.dol<<" "<<c.shir<<endl;

printf("Разность\n");
c = a - b;
cout<<c.dol<<" "<<c.shir<<endl;

printf("Умножение\n");
printf("Введите число\n");
cin>>ch;
if(!cin){
	printf("Вы ввели неверное число\n");
}else{
c = a * ch;
cout<<c.dol<<" "<<c.shir<<endl;
c = b * ch;
cout<<c.dol<<" "<<c.shir<<endl;
}

printf("Деление\n");
printf("Введите число\n");
cin>>ch;
if(!cin){
	printf("Вы ввели неверное число\n");
} 
else{
if (ch==0)
	printf("Деление невозможно\n");
else{
	c = a / ch;
	cout<<c.dol<<" "<<c.shir<<endl;
	c= b / ch;
	cout<<c.dol<<" "<<c.shir<<endl;
}
}

printf("Сравнение\n");
if(a==b)
	printf("Координаты равны\n");
else if(a>b)
	 printf("Первая координата больше\n");
else printf("Вторая координата больше\n");

}