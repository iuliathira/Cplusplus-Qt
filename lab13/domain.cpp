#include "domain.h"

bool cmpDen(const Disciplina& d1, const Disciplina& d2) {
	return d1.getDen() < d2.getDen();
}

bool cmpTip(const Disciplina& d1, const Disciplina& d2) {
	return d1.getTip() < d2.getTip();
}
bool cmpOre(const Disciplina& d1, const Disciplina& d2) {
	return d1.getOre() < d2.getOre();
}
bool cmpCadru(const Disciplina& d1, const Disciplina& d2) {
	return d1.getCadru() < d2.getCadru();
}
