#pragma once
#include <string>
#include <vector>
#include <memory>
#include "contractDisciplina.h"
#include <functional>
#include "validator.h"
#include "repository.h"
#include "domain.h"
#include "undo.h"

using std::unique_ptr;

typedef bool(*MaiMicF)(const Disciplina&, const Disciplina&);

class ContractService :public Observable{
	//ContractRepo& rep;
	friend class GUI;
	AbstractRepo& rep;
	//DictRepo& rep;
	DisciplinaValidator& val;
	vector<Disciplina> modificari;
	vector<Disciplina> generalSort(MaiMicF maiMicF)const;
	vector<Disciplina> filtreaza(function<bool(const Disciplina&)> fct) const;
	//ContractStudii& contract;
	ContractStudii contract;
	std::vector<unique_ptr<ActiuneUndo>>undoActions;

public:
	//ContractService(ContractRepo& rep, DisciplinaValidator& val) noexcept : rep{ rep }, val{ val } {}
	ContractService(AbstractRepo& rep, DisciplinaValidator& val) noexcept : rep{ rep }, val{ val }, contract{ ContractStudii(rep) } {}
	//ContractStudii(ContractStudii& c):contract{c}{}
	ContractService(const ContractService& ot) = delete;
	~ContractService();
	vector<Disciplina> getModif();
	
	//void printare();
	void undo();
	vector<Disciplina> getAll() const noexcept {
		return rep.getAll();
	}
	/*const vector<Disciplina>& getContract() const noexcept {
	return rep.getCont();
	}*/
	void addDisciplina(const string& den, int  ore, const string& tip, const string& cadru);
	void deleteDisciplina(const string& den, const string& tip);
	void updateDisciplina(const string& den, int  ore, const string& tip, const string& cadru);
	int searchDisciplina(const string& den);
	Disciplina searchDis(const string& den);
	vector<Disciplina> sortByDen()const;
	vector<Disciplina> sortByTip()const;
	vector<Disciplina> sortByOre()const;
	vector<Disciplina> sortByCadru()const;
	vector<Disciplina> fltOre(int ore) const;
	vector<Disciplina> fltCadru(string& cadru) const;
	const std::vector<Disciplina>& deleteContract();
	vector<Disciplina> getD();
	//void addContract(const string& den);
	const std::vector<Disciplina>& addContract(const std::string& den);
	const std::vector<Disciplina>& addRandom(int cate);
	void exportContractCVS(std::string fileName) const;
	void exportContractHTML(std::string fileName) const;
};

