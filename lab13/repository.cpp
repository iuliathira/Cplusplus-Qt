#include "repository.h"
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

//Add a subject
//In:den,tip,cadru,ore
//Prec:den-string,tip-string,cadru-string,ore-int
//Post-
void ContractRepo::store(const Disciplina& d) {
	auto found = std::find_if(all.begin(), all.end(), [d](const Disciplina& dd) {
		return dd.getDen() == d.getDen();
		
	});
	if (found != all.end()) {
		throw DisciplinaRepoException{ "Disciplina existenta(adaugare)!!!" };
	}
	else
	all.push_back(d);
}

//Verify if a subject exists
//In:d
//Out:true,false
//Prec:s-Disciplina
//Post:bool
/*
const Disciplina& ContractRepo::exist(const Disciplina& d) {

auto found = std::find_if(all.begin(), all.end(), [d](const Disciplina& dd) {
return dd.getDen() == d.getDen();
});
if (found != all.end())
throw DisciplinaRepoException{ "Disciplina inexistenta!" };
return *found;

}*/
//Delete a subject
//In:den,tip
//Out:-
//Prec:den-string,tip-string
//Post-
void ContractRepo::del(const Disciplina& d) {
	auto found = std::find_if(all.begin(), all.end(), [d](const Disciplina& dd) {
		return dd.getDen() == d.getDen();
	});
	if (found == all.end()) {
		throw DisciplinaRepoException{ "Disciplina inexistenta!!!" };
	}
	//stergem pet
	auto rez = all.erase(found);
}
/*
void ContractRepo::delC() {
for (const auto& elem : contractStudii)
{
auto poz = find(contractStudii.begin(), contractStudii.end(), elem);
contractStudii.erase(poz);

}
}*/

/*
void ContractRepo::addC(const string& den) {
if (exist(Disciplina(den, 4, "tip", "cadru"))) {
Disciplina d = find2(den);
contractStudii.push_back(d);
}
}*/
//Update a subject
//In:den,tip,ore,cadru
//Out:-
//Prec:den-string,tip-string
//Post:-
void ContractRepo::update(const Disciplina& d) {
	auto found = std::find_if(all.begin(), all.end(), [d](const Disciplina& dd) {
		return dd.getDen() == d.getDen();
	});
	if (found == all.end()) {
		throw DisciplinaRepoException{ "Disciplina inexistenta!!!" };
	}
	//auto rez = all.erase(found);
	
		//all.push_back(d);
	int i = find1(d.getDen());
	all.at(i) = d;
	
}

//Search a subject
//In:den,tip
//Out:i
//Prec:den-string,tip-string
//Post:i-int
int ContractRepo::find1(const string& den) const {
	int i = -1;
	for (const Disciplina& d : all) {
		i++;
		if (d.getDen() == den) {
			return i;
		}

	}
	i = -1;
	return i;
}
//Search a subject
//In:den
//Out:d or Exception
//Prec:den-string
//Post: d- Disciplina or Exception if it doesn't exist
const Disciplina& ContractRepo::find2(const string& den) const {
	for (const Disciplina& d : all) {
		if (d.getDen() == den) {
			return d;
		}

	}
	throw DisciplinaRepoException("Nu exista disciplina: " + den);
}
vector<Disciplina> ContractRepo::getAll()const  noexcept {
	return all;
}

/*
const vector<Disciplina>& ContractRepo::getCont()const noexcept {
//return contractStudii;
return all;
}*/



ostream& operator<<(ostream& out, const DisciplinaRepoException& ex) {
	out << ex.msg;
	return out;
}

void ContractRepoFile::loadFromFile() {
	std::ifstream in(fileName);
	if (!in.is_open()) {
		throw DisciplinaRepoException("Unable tu open file: " + fileName);
	}
	while (!in.eof()) {
		std::string den;
		int ore;
		std::string tip;
		std::string cadru;
		in >> den;
		in >> ore;
		in >> tip;
		in >> cadru;
		if (in.eof()) {
			break;
		}
		Disciplina d{ den.c_str(),ore,tip.c_str(),cadru.c_str() };
		ContractRepo::store(d);

	}
	in.close();
}
void ContractRepoFile::writeToFile() {
	std::ofstream out(fileName);
	if (!out.is_open()) {//std::string msg("Unable to open file. ");
		throw DisciplinaRepoException("Unable to open file. ");
	}
	for (auto& d : getAll()) {
		out << d.getDen();
		out << std::endl;
		out << d.getOre();
		out << std::endl;
		out << d.getTip();
		out << std::endl;
		out << d.getCadru();
		out << std::endl;

	}
	out.close();
}
