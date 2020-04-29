#include <iostream>
#include <string>
using namespace std;
class wheel;
class engine;
class body;
class car;
class visitor
{
public:
	virtual void visit(wheel& w)=NULL;
	virtual void visit(engine& w) = NULL;
	virtual void visit(body& w) = NULL;
	virtual void visit(car& c) = NULL;
};

class wheel
{
public:
	wheel(string name)
	{
		this->name = name;
	}
	void accept(visitor& v)
	{
		v.visit(*this);
	}
	string& getName() { return this->name; }
private:
	string name;
};

class engine
{
public:
	void accept(visitor& v)
	{
		v.visit(*this);
	}
};
class body
{
public:
	void accept(visitor& v)
	{
		v.visit(*this);
	}
};
class car
{
public:
	car()
	{
		e = new engine;
		b = new body;
		w[0] = new wheel("front left");
		w[1] = new wheel("front right");
		w[2] = new wheel("back left");
		w[3] = new wheel("back right");
	}
	~car()
	{
		delete e;
		delete b;
		for (int i = 0; i < 4; ++i)
			delete w[i];
	}
	void accept(visitor& v)
	{
		v.visit(*this);
		e->accept(v);
		b->accept(v);
		for (int i = 0; i < 4; ++i)
			w[i]->accept(v);
	}
private:
	engine* e;
	body* b;
	typedef  wheel* pwheel;
	pwheel w[4];
};


class printVisitor :public visitor
{
public:
	void visit(wheel& w) override { cout << "visiting " << w.getName() << " whell" << endl; };
	void visit(engine& e) override { cout << "Visiting engine" << endl; }
	void visit(body& b) override { cout << "Visiting body" << endl; }
	void visit(car& c) override  { cout << "Visiting car" << endl; }
};


int main()
{
	car c;
	visitor* v = new printVisitor;
	c.accept(*v);
}