#pragma once
#include <vector>
class Observer
{
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*>list;

public:
	void addObserver(Observer* ob);
	void notifyAll();
};

