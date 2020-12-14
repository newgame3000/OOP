
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <list>
#include <stack>
#include <cmath>
#include <string>


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
		printf("Введите координату нижней левой точки трапеции, наибольшее основание, наименьшее основание и длину высоты (трапеция равнобокая)\n");
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

template<class T>
class Document {
public:

	class Action {
	public:
		virtual void PerformAction(Document & fact) = 0;
		virtual ~Action() {}
	};

	stack<shared_ptr <Action> > st_ac;
	list<shared_ptr <Figure> > ls_fig;

	class AddAction: public Action {
	public:
		unsigned long long Position;
		shared_ptr<Figure> AddFigure;

		AddAction(unsigned long long & pos, shared_ptr<Figure> & fig) : Position(pos), AddFigure(fig) {}

		void PerformAction(Document & fact) override {
			fact.AddFigure(Position,AddFigure);
		}

	};

	class DeleteAction: public Action {
	public:
		unsigned long long Position;

		DeleteAction(unsigned long long pos): Position(pos){}

		void PerformAction(Document & fact) override {
			fact.Delete(Position);
		}
	};

	void Create() {
		while (!st_ac.empty()) {
			st_ac.pop();
		}
		ls_fig.clear();
	}

	void Add (unsigned long long & pos, unsigned long long & id) {
		if (id == Rec_Id) {
			AddFigure(pos, Factory<T, Rectangle<T>>:: Create());
		} else {
			if (id == Romb_Id) {
				AddFigure(pos, Factory<T, Romb<T>>:: Create());
			} else {
				if (id == Tr_Id) {
					AddFigure(pos, Factory<T, Trapeze<T>>:: Create());
				}
			}
		}
	}

	void AddFigure(unsigned long long & pos, shared_ptr<Figure> f) {

		list< shared_ptr <Figure> >::iterator it = ls_fig.begin();
		unsigned long long cur_pos = 0;
		while (cur_pos > pos && pos < ls_fig.size() + 1) {
			++it;
			++cur_pos;
		}
		DeleteAction* delAct = new DeleteAction(pos + 1);
		st_ac.push(shared_ptr<Action>(delAct));
		ls_fig.insert(it, f);
	}

	void Delete(unsigned long long & pos) {

		if (ls_fig.empty()) {
			printf("Нечего удалять\n");
			return;
		}

		list< shared_ptr <Figure> >::iterator it = ls_fig.begin();
		unsigned long long cur_pos = 0;
		while (cur_pos > pos && pos < ls_fig.size() + 1) {
			++it;
			++cur_pos;
		}
		AddAction* addAct = new AddAction(cur_pos, *it);
		st_ac.push(shared_ptr<Action>(addAct));
		ls_fig.erase(it);
	}

	void Save(FILE* out) {
		unsigned long long size = ls_fig.size();
		fwrite(&size, sizeof(unsigned long long), 1, out);
		for (list< shared_ptr <Figure> >::iterator it = ls_fig.begin(); it != ls_fig.end(); ++it) {
			(*it)->Write(out);
		}
	}

	void Load(FILE* in) {
		Create();
		unsigned long long size;
		fread(&size, sizeof(unsigned long long), 1, in);
		for (unsigned long long i = 0; i < size; ++i){
			unsigned long long id;
			fread(&id, sizeof(unsigned long long), 1, in);
			if (id == Rec_Id) {
				ls_fig.push_back(Factory<T, Rectangle<T>>:: Read(in));
			} else {
				if (id == Romb_Id) {
					ls_fig.push_back(Factory<T, Romb<T>>:: Read(in));
				} else {
					if (id == Tr_Id) {
						ls_fig.push_back(Factory<T,Trapeze<T>>:: Read(in));
					}
				}
			}
		}
	}

	void Undo() {
		if(st_ac.empty()) {
			printf("Невозможно отменить последнее действие\n");
			return;
		}

		st_ac.top()->PerformAction(*this);
		st_ac.pop();
		st_ac.pop();
	}

};



int main() {
	Document<double> doc;
	int input;

	printf("Введите 1, чтобы создать документ\n");
    printf("Введите 2, чтобы добавить фигуру\n");
    printf("Введите 3, чтобы удалить фигуру\n");
    printf("Введите 4, сохранить документ в файл\n");
    printf("Введите 5, чтобы загрузить элемент из файла\n");
    printf("Введите 6, чтобы вывести содержимое документа\n");
    printf("Введите 7, чтобы отменить последнее действие(удаление, добавление)\n");
    printf("Введите 8, чтобы вывести меню\n");
    

    while (cin >> input) {
    	if (!cin){
		cout << "Введены неверные данные" << endl;
		return -1;
    	}
    	switch(input){
    		case 1:
	    		{
		    		doc.Create();
		    		printf("Документ создан\n");
		    		break;
		    	}
    		case 2:
	    		{
		    		printf("Введите 1, чтобы добавить прямоугольник\n");
		    		printf("Введите 2, чтобы добавить ромб\n");
		    		printf("Введите 3, чтобы добавить трапецию\n");
		    		unsigned long long type;
		    		cin >> type;
		    		if (!cin && type != 1 && type != 2 && type != 3) {
		    			printf("Вы ввели неверную команду\n");
		    			return -1;
		    		}

		    		printf("Введите позицию вставки\n");
		    		unsigned long long p;
		    		cin >> p;
		    		if (!cin) {
		    			printf("Вы ввели неверную позицию\n");
		    			return -1;
		    		}
		    		doc.Add(p,type);
		    		break;
		    	}
    		case 3:
	    		{
	    			unsigned long long poss;
	    			printf("Введите позицию удаления\n");
		    		cin >> poss;
		    		if (!cin) {
		    			printf("Вы ввели неверную позицию\n");
		    			return -1;
		    		}
		    		doc.Delete(poss);
	    			break;
	    		}
    		case 4:
	    		{
	    			string s;
	    			printf("Введите расположение файла\n");
	    			cin >> s;
	    			FILE *file = fopen(s.c_str(),"wb");
	    			if (file == NULL) {
	    				printf("Не удалось открыть файл\n");
	    			} else {
	    				doc.Save(file);
	    				fclose(file);
	    				printf("Документ сохранён\n");
	    			}
	    			break;
	    		}
    		case 5:
    			{
	    			string s;
	    			printf("Введите расположение файла\n");
	    			cin >> s;
	    			FILE *file = fopen(s.c_str(),"rb");
	    			if (file == NULL) {
	    				printf("Не удалось открыть файл\n");
	    			} else {
	    				doc.Load(file);
	    				fclose(file);
	    				printf("Документ загружен\n");
	    			}
	    			break;
    			}
    		case 6:
    			{
    				if (doc.ls_fig.size() == 0) {
    					printf("Документ пуст\n");
    				}
	    			list< shared_ptr <Figure> >::iterator it = doc.ls_fig.begin();
	    			for (int i = 0; i < doc.ls_fig.size(); ++i) {
	    				(*it)->Print();
	    				++it;
	    			}
	    			break;
	    		}
    		case 7:
	    		{
	    			doc.Undo();
	    			break;
	    		}
    		case 8:
	    		{
	    			printf("Введите 1, чтобы создать документ\n");
	    			printf("Введите 2, чтобы добавить фигуру\n");
	   				printf("Введите 3, чтобы удалить фигуру\n");
	    			printf("Введите 4, сохранить документ в файл\n");
	   				printf("Введите 5, чтобы загрузить элемент из файла\n");
	    			printf("Введите 6, чтобы вывести содержимое документа\n");
	    			printf("Введите 7, чтобы отменить последнее действие(удаление, добавление)\n");
	    			printf("Введите 8, чтобы вывести меню\n");
	       			break;
	       		}
    		default:
  				cout<<"Вы ввели неверную команду"<<std::endl;
			  	return -1;
			  	break;
    	}
    }
}