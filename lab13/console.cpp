#include <iostream>
#include <vector>
#include "console.h"
#include <string>
#include "domain.h"
#include "service.h"
using namespace std;


void ConsoleUi::adaugaMemo() {
	ctr.addDisciplina("geometrie", 5, "facultativ", "Blaga");
	ctr.addDisciplina("oop", 6, "obligatoriu", "Istvan");
	ctr.addDisciplina("grafuri", 3, "optional", "Suciu");
	ctr.addDisciplina("sda", 11, "facultativ", "Gabi");
	ctr.addDisciplina("sd", 3, "facultativ", "Serban");
	ctr.addDisciplina("sisteme", 5, "obligatoriu", "Boian");
}


template<typename T>
T myread(const char* msg) {
	T cmd{};
	while (true) {
		std::cout << std::endl << msg;
		std::cin >> cmd;
		const bool fail = std::cin.fail();
		std::cin.clear();//resetez failbit
		const auto& aux = std::cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1) {
			break; //am reusit sa citesc numar
		}
	}
	return cmd;
}
//Add a subject
//In:den,tip,cadru,ore
//Prec:den-string,tip-string,cadru-string,ore-int
//Post-


void ConsoleUi::adaugaUi() {
	string den, tip, cadru;
	int ore;
	cout << "Dati denumirea: ";
	cin >> den;
	cout << "Dati nr de ore: ";
	cin >> ore;
	cout << "Dati tipul disciplinei: ";
	cin >> tip;
	cout << "Dati nume cadru didactic: ";
	cin >> cadru;
	ctr.addDisciplina(den, ore, tip, cadru);
	cout << "Adaugare efectuata cu succes!";
}
void ConsoleUi::adaugaContract() {
	string den;
	cout << "Introduceti numele disciplinei pe care doriti sa o adaugati: ";
	cin >> den;
	tiparesteUi(ctr.addContract(den));
}
//Print all subject
//In:discipline
//Prec:discipline-vector
//Post-

void ConsoleUi::tiparesteUi(vector<Disciplina> discipline) {
	cout << "Disciplinele:\n";
	int i;
	//Disciplina dd = Disciplina("nume", 5, "f", "g");
	for (i = 0;i < discipline.size();i++) {
		//Disciplina dds=Disciplina("inff",5,"f","d");
		//dds.operator=(disciplina);
		cout << discipline[i].getDen() << " " << discipline[i].getOre() << " " << discipline[i].getTip() << " " << discipline[i].getCadru() << "\n";
		//cout << " " << disciplina.getDen() << " " << disciplina.getOre() << " " << disciplina.getTip() << " " << disciplina.getCadru() << "\n";
	}
	cout << "Sfarsit lista discipline";
}

void ConsoleUi::tiparesteUi1() {
	vector<Disciplina> v = ctr.getAll();
	for (const auto& disciplina : v) {
		//Disciplina dds=Disciplina("inff",5,"f","d");
		//dds.operator=(disciplina);
		cout << " " << disciplina.getDen() << " " << disciplina.getOre() << " " << disciplina.getTip() << " " << disciplina.getCadru() << "\n";
	}
	cout << "Sfarsit lista discipline";
}

//Search a subject
//In:den,tip
//Out:
//Prec:den-string,tip-string
//Post


void ConsoleUi::searchUi() {
	/*//string den, tip;
	string den;
	cout << "Dati denumirea: ";
	cin >> den;
	//cout << "Dati tipul disciplinei: ";
	//cin >> tip;
	//int i = ctr.searchDisciplina(den, tip);
	int i = ctr.searchDisciplina(den);
	if (i == -1)
	cout << "Element inexistent!";
	else
	cout << "Element gasit" << " " << ctr.getAll()[i].getDen() << " " << ctr.getAll()[i].getOre() << " " << ctr.getAll()[i].getTip() << " " << ctr.getAll()[i].getCadru();
	*/

	string den;
	cout << "Dati denumirea: ";
	cin >> den;

	Disciplina d = ctr.searchDis(den);
	if (d.getDen() == "NULL")
		cout << "Element inexistent";
	else
		cout << "Element gasit" << " " << d.getDen() << " " << d.getOre() << " " << d.getTip() << " " << d.getCadru();

}

//Delete a subject
//In:den,tip
//Out:-
//Prec:den-string,tip-string
//Post-

void ConsoleUi::stergereUi() {
	string den, tip;
	cout << "Dati denumirea: ";
	cin >> den;
	cout << "Dati tipul disciplinei: ";
	cin >> tip;
	ctr.deleteDisciplina(den, tip);
	cout << "Stergere efectuata ccu succes!";
}
//Delete all subjects from a study contract
//Study Contract - empty
void ConsoleUi::stergereContract() {
	cout << "Contract golit!";
	//tiparesteUi(ctr.deleteContract());
	ctr.deleteContract();
}
void ConsoleUi::tiparireContract() {
	cout << "Contract: \n";
	tiparesteUi(ctr.getD());
}
//Update a subject
//In:den,tip,ore,cadru
//Out:-
//Prec:den-string,tip-string
//Post-

void ConsoleUi::modificaUi() {
	string den, tip, cadru;
	int ore;
	cout << "Dati denumirea: ";
	cin >> den;
	cout << "Dati tipul disciplinei: ";
	cin >> tip;
	cout << "Dati nr de ore ale disciplinei: ";
	cin >> ore;
	cout << "Dati nume cadru al disciplinei: ";
	cin >> cadru;
	ctr.updateDisciplina(den, ore, tip, cadru);
	cout << "Stergere efectuata ccu succes!";
}
// Filter subjects by ore
//In:ore
//Out:elem - Disciplina
//Prec:ore-int
//Post-print vector

void ConsoleUi::filtrareOre() {
	int ore;
	cout << "Filtreaza disciplinele cu nr de ore mai mic decat: ";
	cin >> ore;
	tiparesteUi(ctr.fltOre(ore));

}
// Filter subjects by cadru
//In:cadru
//Out:elem - Disciplina
//Prec:cadru-string
//Post-print vector

void ConsoleUi::filtrareCadru() {
	string cadru;
	cout << "Filtreaza disciplinele care au acelasi cadru didactic: ";
	cin >> cadru;
	tiparesteUi(ctr.fltCadru(cadru));

}

void ConsoleUi::generareContract() {
	cout << "Cate discipline doriti generate?\n";
	int cate;
	cin >> cate;
	tiparesteUi(ctr.addRandom(cate));

}
int ConsoleUi::numarDiscipline() {
	return ctr.getD().size();
}
void ConsoleUi::Menu() {
	cout << "\nMenu:\n";
	cout << "1.Adauga disciplina\n";
	cout << "2.Tipareste discipline\n";
	cout << "3.Sterge disciplina\n";
	cout << "4.Modifica disciplina\n";
	cout << "5.Cauta disciplina\n";
	cout << "6.Sorteaza dupa denumire\n";
	cout << "7.Sorteaza dupa tip\n";
	cout << "8.Sorteaza dupa ore\n";
	cout << "9.Sorteaza dupa nume cadru didactic\n";
	cout << "10.Filtreada dupa numarul de ore\n";
	cout << "11.Filtreaza dupa cadru didactic\n";
	cout << "12.Adauga discipline in contract\n";
	cout << "13.Goleste contract\n";
	cout << "14.Genereaza contract random\n";
	cout << "15.Exporta in CVS\n";
	cout << "16.Exporta in HTML\n";
	cout << "17.Undo\n";
	cout << "0.Exit\n";
}
void ConsoleUi::start() {
	while (true) {
		Menu();
		int cmd;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaUi();
				break;
			case 2:
				tiparesteUi(ctr.getAll());
				//tiparesteUi1();
				break;
			case 3:
				stergereUi();
				break;
			case 4:
				modificaUi();
				break;
			case 5:
				searchUi();
				break;
			case 6:
				tiparesteUi(ctr.sortByDen());
				break;
			case 7:
				tiparesteUi(ctr.sortByTip());
				break;
			case 8:
				tiparesteUi(ctr.sortByOre());
				break;
			case 9:
				tiparesteUi(ctr.sortByCadru());
				break;
			case 10:
				filtrareOre();
				break;
			case 11:
				filtrareCadru();
				break;
			case 12:
				adaugaContract();
				cout << "\nNumar de discipline din contract: " << numarDiscipline();
				break;
			case 13:
				stergereContract();
				cout << "\nNumar de discipline din contract: " << numarDiscipline();
				break;
			case 14:
				//tiparireContract(ctr.getContract());
				generareContract();
				cout << "Numar de discipline din contract: " << numarDiscipline();
				break;
			case 15:
				ctr.exportContractCVS(myread<string>("CVS File:"));
				break;
			case 16:
				ctr.exportContractHTML(myread<string>("HTML File:"));
				break;
			case 17:
				ctr.undo();
				break;
			case 0:
				return;

			default:
				cout << "Comanda invalida!\n";
			}
		}
		catch (DisciplinaRepoException& ex) {
			cout << ex << "\n";
		}
		catch (ValidateException& ex) {
			cout << ex << "\n";
		}



	}


}

