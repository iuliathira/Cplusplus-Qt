#pragma once
#include <string>
#include <iostream>

using std::string;

class Disciplina
{
	std::string den;
	int ore;
	std::string tip;
	std::string cadru;
public:
	Disciplina(const string dn, int o, const string t, const string c) :den{ dn }, ore{ o }, tip{ t }, cadru{ c } { };
	string getDen() const {
		return den;
	}
	string getTip() const {
		return tip;
	}
	string getCadru() const {
		return cadru;
	}
	int getOre() const noexcept {
		return ore;
	}
	void operator=(const Disciplina& ot)
	{
		den = ot.den;
		tip = ot.tip;
		ore = ot.ore;
		cadru = ot.cadru;
	}
	bool operator==(const Disciplina& el1) {
		return this->den == el1.getDen();
	}
};
bool cmpDen(const Disciplina& d1, const Disciplina& d2);
bool cmpTip(const Disciplina& d1, const Disciplina& d2);
bool cmpOre(const Disciplina& d1, const Disciplina& d2);
bool cmpCadru(const Disciplina& d1, const Disciplina& d2);

