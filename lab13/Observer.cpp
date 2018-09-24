#include "Observer.h"


void Observable::addObserver(Observer* ob) {
	list.push_back(ob);
}


void Observable::notifyAll() {
	for (auto e : list) {
		e->update();}
}