#include<iostream>

/* Воронов К.М. М8О-207Б-19
Создать класс TransNumber для работы с трансцендентными числами.
Трансцендентное число представлено парой (a, b), где a – действительная часть,
b – трансцендентная часть. Трансцендентная часть представляет собой действительное
число b, умноженное на константу. Реализовать арифметические операции
(по аналогии с операциями над комплексными числами в алгебраической форме), 
и операции сравнения по значению (a + b ´).
*/

class TransNumber{
	public:          //Составные части трансцедентного числа
		double a;
		double b;

	TransNumber(){
		a=0;b=0;
	}

	void add(TransNumber c){  //Сложение
		a=a+c.a;
		b=b+c.b;
		std::cout<<"a="<<a<<" b="<<b<<std::endl;
	}
	
	void sub(TransNumber c){  //Вычитание
		a=a-c.a;
		b=b-c.b;
		std::cout<<"a="<<a<<" b="<<b<<std::endl;
	}

	void mul(TransNumber c){  //Умножение
		double a2=a;
		a=a*c.a-b*c.b;
		b=a2*c.b+b*c.a;
		std::cout<<"a="<<a<<" b="<<b<<std::endl;
	}

	void div(TransNumber c){  //Деление
		double a2=a;
		a=a*c.a+b*c.b;
		b=b*c.a-a2*c.b;
		double z=c.a*c.a+c.b*c.b;
		std::cout<<"("<<a<<","<<b<<")/"<<z<<std::endl;
	}

	bool equ(TransNumber c){  //Сравнение по а и 
		if((a==c.a)&&(b==c.b)){
			return true;	
		}
		else
			return false;
	}

	bool equ2(TransNumber c){  //Сравнение по а+b
		if(a+b==c.a+c.b){
			return true;
		}
		else
		return false;
	}

	void conj(){  //Сопряжённое число
		b=-b;
		std::cout<<"("<<a<<","<<b<<")"<<std::endl;
	}

};


int main(){
  TransNumber a;
  TransNumber c;
  std::cout<<"Введите 1, чтобы сложить два трансцендентных числа"<<std::endl;
  std::cout<<"Введите 2, чтобы вычесть одно трансцендентное число из другого"<<std::endl;
  std::cout<<"Введите 3, чтобы умножить два трансцендентных числа"<<std::endl;
  std::cout<<"Введите 4, чтобы разделить одно трансцендентное число на другое"<<std::endl;
  std::cout<<"Введите 5, чтобы сравнить два трансцендентных числа по а и b"<<std::endl;
  std::cout<<"Введите 6, чтобы сравнить два трансцендентных числа по а + b"<<std::endl;
  std::cout<<"Введите 7, чтобы вывести сопряжённое число"<<std::endl;
  std::cout<<"Введите 8, чтобы вывести меню"<<std::endl;
  std::cout<<"Введите -1, чтобы прекратить работу программы"<<std::endl;
  long long input=0;

 	while(input!=-1){
 		std::cin>>input;
 		if(!std::cin){
  		std::cout<<"Вы ввели неверную команду"<<std::endl;
  		return -1;
  	}
  switch (input){
  	case 1:
  	 std::cout<<"Введите два трансцендентных числа в виде пар"<<std::endl;
  	 std::cout<<"a1=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b1=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"a2=";
  	 std::cin>>c.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b2=";
  	 std::cin>>c.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 a.add(c);
  	break;
  	case 2:
	 std::cout<<"Введите два трансцендентных числа в виде пар"<<std::endl;
	 std::cout<<"a1=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b1=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"a2=";
  	 std::cin>>c.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b2=";
  	 std::cin>>c.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 a.sub(c);
  	break;
  	case 3:
  	 std::cout<<"Введите два трансцендентных числа в виде пар"<<std::endl;
  	 std::cout<<"a1=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b1=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"a2=";
  	 std::cin>>c.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b2=";
  	 std::cin>>c.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 a.mul(c);
  	break;
  	case 4:
	 std::cout<<"Введите два трансцендентных числа в виде пар"<<std::endl;
  	 std::cout<<"a1=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b1=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"a2=";
  	 std::cin>>c.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b2=";
  	 std::cin>>c.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 a.div(c);
  	break;
  	case 5:
	 std::cout<<"Введите два трансцендентных числа в виде пар"<<std::endl;
  	 std::cout<<"a1=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b1=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"a2=";
  	 std::cin>>c.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b2=";
  	 std::cin>>c.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 if(a.equ(c)){
	 	std::cout<<"Числа равны"<<std::endl;
  	 }else{
  	 	std::cout<<"Числа не равны"<<std::endl;
  	 }
  	break;
  	case 6:
	 std::cout<<"Введите два трансцендентных числа в виде пар"<<std::endl;
   	 std::cout<<"a1=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b1=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"a2=";
  	 std::cin>>c.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b2=";
  	 std::cin>>c.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 if(a.equ2(c)){
	 	std::cout<<"Числа равны"<<std::endl;
  	 }else{
  	 	std::cout<<"Числа не равны"<<std::endl;
  	 }
  	break;
  	case 7:
  	 std::cout<<"Введите трансцендентное число в виде пары"<<std::endl;
	 std::cout<<"a=";
  	 std::cin>>a.a;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 std::cout<<"b=";
  	 std::cin>>a.b;
  	 if(!std::cin){
  		std::cout<<"Вы ввели неверное значение"<<std::endl;
  		return -1;
  	}
  	 std::cout<<std::endl;
  	 a.conj();
  	break;
  	case 8:
  	  std::cout<<"Введите 1, чтобы сложить два трансцендентных числа"<<std::endl;
	  std::cout<<"Введите 2, чтобы вычесть одно трансцендентное число из другого"<<std::endl;
	  std::cout<<"Введите 3, чтобы умножить два трансцендентных числа"<<std::endl;
	  std::cout<<"Введите 4, чтобы разделить одно трансцендентное число на другое"<<std::endl;
	  std::cout<<"Введите 5, чтобы сравнить два трансцендентных числа по а и b"<<std::endl;
	  std::cout<<"Введите 6, чтобы сравнить два трансцендентных числа по а + b"<<std::endl;
	  std::cout<<"Введите 7, чтобы вывести сопряжённое число"<<std::endl;
	  std::cout<<"Введите 8, чтобы вывести меню"<<std::endl;
	  std::cout<<"Введите -1, чтобы прекратить работу программы"<<std::endl;
  	break;
  	case -1:
  	break;
  	default:
  	std::cout<<"Вы ввели неверную команду"<<std::endl;
  	return -1;
  	break;
  }
}
}