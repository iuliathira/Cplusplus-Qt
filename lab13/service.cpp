#include "service.h"
#include <functional>
#include <algorithm>
#include <vector>
#include <memory>
#include <iterator>
#include "undo.h"
#include "exporta.h"

//Sort subjects
//In:maiMicF
//Out-v
//Prec:MaiMicF
//Post:v-vector Disciplina
vector<Disciplina> ContractService::generalSort(MaiMicF maiMicF) const {
	vector<Disciplina> v{ rep.getAll() };//fac o copie	
	sort(v.begin(), v.end(), maiMicF);
	//for (size_t i = 0; i < v.size(); i++) {
	//	for (size_t j = i + 1; j < v.size(); j++) {
	//		if (!maiMicF(v[i], v[j])) {
	//			//interschimbam
	//			Pet aux = v[i];
	//			v[i] = v[j];
	//			v[j] =  aux;
	//		}
	//	}
	//}
	return v;
}

//Sort by den
vector<Disciplina> ContractService::sortByDen()const {
	return generalSort(cmpDen);
}
//sort by tip
vector<Disciplina> ContractService::sortByTip()const {
	return generalSort(cmpTip);
}
//sort by ore
vector<Disciplina> ContractService::sortByOre()const {
	return generalSort(cmpOre);
}
//sort by cadru
vector<Disciplina> ContractService::sortByCadru()const {
	return generalSort(cmpCadru);
}
//Add a subject
//In:den,tip,cadru,ore
//Prec:den-string,tip-string,cadru-string,ore-int
//Post-
void ContractService::addDisciplina(const string& den, int  ore, const string& tip, const string& cadru) {
	Disciplina d{ den,ore,tip,cadru };
	val.validate(d);
	rep.store(d);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, d));
}
void ContractService::undo() {
	if (undoActions.empty()) {
		throw DisciplinaRepoException("Nu mai exista operatii!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
//Delete a subject
//In:den,tip
//Out:-
//Prec:den-string,tip-string
//Post-
void ContractService::deleteDisciplina(const string& den, const string& tip) {
	Disciplina d{ den,6,tip,"cadru" };
	val.validate(d);
	rep.del(d);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, d));
}

const std::vector<Disciplina>& ContractService::addContract(const std::string& den) {
	val.validate(Disciplina(den, 4, "tip", "cadru"));
	const Disciplina& d = rep.find2(den);
	contract.adauga(d);
	this->notifyAll();
	//Observable::notifyAll();
	return contract.lista();
}
/*
void ContractService::printare()
{
rep.tiparire();
}*/
//Delete all subjects
//In:-
//Out:empty list

void ContractStudii::update_contract() {
	for (auto&x : rep.getAll()) {
		if (this->get_disciplina(x.getDen()) == -1) {			
			string name = x.getDen();
			inContract.erase((std::remove_if(this->inContract.begin(), this->inContract.end(), [&](const Disciplina&p) {return p.getDen() == name; }), this->inContract.end()));}
	}
}

int ContractStudii::get_disciplina(const string& den) const {
	int idx = 0;
	for (const auto& x : this->rep.getAll()) {
		if (x.getDen() == den) return idx;
		idx++;
	}
	return -1;
}

void ContractStudii::update() {
	update_contract();
	notifyAll();
}
const std::vector<Disciplina>& ContractService::deleteContract() {
	contract.goleste();
	return contract.lista();
}
const std::vector<Disciplina>& ContractService::addRandom(int cate) {
	contract.genereaza(cate, rep.getAll());
	return contract.lista();
}

//Update a subject
//In:den,tip,ore,cadru
//Out:-
//Prec:den-string,tip-string
//Post:-

void ContractService::updateDisciplina(const string& den, int  ore, const string& tip, const string& cadru) {
	Disciplina d{ den,ore,tip,cadru };
	val.validate(d);
	Disciplina dd = rep.find2(den);
	rep.update(d);
	
	modificari.push_back(d);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, dd));
}
vector<Disciplina> ContractService::getModif() {
	return modificari;
}
Disciplina ContractService::searchDis(const string& den) {
	int i = searchDisciplina(den);
	if (i != -1)
	{
		//Disciplina d("",0,"","");
		Disciplina d = getAll()[i];
		return d;
	}
	return Disciplina("NULL", 0, "NULL", "NULL");


}
//Search a subject
//In:den,tip
//Out:
//Prec:den-string,tip-string
//Post
int ContractService::searchDisciplina(const string& den) {
	val.validate(Disciplina{ den,6,"tip","cadru" });
	return rep.find1(den);

}
// Filter subjects by fct
//In:fct
//Out:elem - Disciplina
//Prec:fct- function
//Post-vector

vector<Disciplina> ContractService::filtreaza(function<bool(const Disciplina&)> fct) const {
	std::vector<Disciplina> rez;
	auto all1 = rep.getAll();
	std::copy_if(all1.begin(), all1.end(), back_inserter(rez), [=](const Disciplina& d) {return fct(d);});
	return rez;
}

/*
vector<Disciplina> ContractService::filtreaza(function<bool(const Disciplina&)> fct) const {
vector<Disciplina> rez;
for (const auto& disciplina : rep.getAll()) {
if (fct(disciplina)) {
rez.push_back(disciplina);
}
}
return rez;
}*/
// Filter subjects by ore
//In:ore
//Out:elem - Disciplina
//Prec:ore-int
//Post-print vector
vector<Disciplina> ContractService::fltOre(int ore) const {
	return filtreaza([ore](const Disciplina& d)noexcept {
		return d.getOre() < ore;
	});
}
// Filter subjects by cadru
//In:cadru
//Out:elem - Disciplina
//Prec:cadru-string
//Post-print vector
vector<Disciplina> ContractService::fltCadru(string& cadru) const {
	return filtreaza([cadru](const Disciplina& d)noexcept {
		return d.getCadru() == cadru;
	});
}
vector<Disciplina> ContractService::getD() {
	return contract.lista();
}

ContractService ::~ContractService() {
	//nu mai e nevoie in varianta cu unique_ptr
}

void ContractService::exportContractCVS(std::string fileName) const {
	exportToCVS(fileName, contract.lista());
}
void ContractService::exportContractHTML(std::string fileName) const {
	exportToHTML(fileName, contract.lista());
}