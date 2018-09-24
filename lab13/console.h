#pragma once
#include "service.h"
class ConsoleUi
{

	ContractService& ctr;
	void adaugaUi();
	void adaugaMemo();
	void tiparesteUi(vector<Disciplina> discipline);
	void tiparesteUi1();
	void stergereUi();
	void modificaUi();
	void searchUi();
	void filtrareOre();
	void filtrareCadru();
	void Menu();
	void stergereContract();
	void adaugaContract();
	void tiparireContract();
	int numarDiscipline();
	//void tiparireContract(const vector<Disciplina>& contractElem);
	void generareContract();
public:
	ConsoleUi(ContractService& ctr) noexcept : ctr{ ctr } {}
	ConsoleUi(const ConsoleUi& ot) = delete;
	void start();
};

