#include "tests.h"
#include "domain.h"
#include "assert.h"
#include "contractDisciplina.h"
#include "repository.h"
#include "service.h"
#include "validator.h"
#include <fstream>

void testDomain() {
	Disciplina d = Disciplina("mate", 4, "f", "Pop");
	assert(d.getDen() == "mate");
	assert(d.getOre() == 4);
	assert(d.getCadru() == "Pop");
	assert(d.getTip() == "f");
	Disciplina d1 = Disciplina("info", 5, "o", "Istvan");
	assert(cmpDen(d, d1) == false);
	assert(cmpTip(d, d1) == true);
	assert(cmpOre(d, d1) == true);
	assert(cmpCadru(d, d1) == false);
	DisciplinaValidator val;
	try {
		val.validate(Disciplina("", -3, "", ""));
	}
	catch (ValidateException& ex) {
		ex.getMsg();
	}
}
void testRepo() {
	//test store
	ContractRepo repo;
	Disciplina d = Disciplina("grafuri", 6, "o", "Suciu");
	repo.store(d);
	assert(repo.getAll().size() == 1);
	assert(repo.find2("grafuri").getDen() == "grafuri");

	try {
		repo.store(Disciplina("grafuri", 6, "o", "Suciu"));
	}
	catch (DisciplinaRepoException&) {}
	try {
		//cout << "Aici avem: ";
		repo.find2("graff");
	}
	catch (DisciplinaRepoException&) {
		//assert(true);
	}
	assert(repo.find1("grafuri") == 0);
	assert(repo.find1("graff") == -1);
	//test update

	Disciplina d1 = Disciplina("grafuri", 7, "o", "Mihaita");
	repo.update(d1);
	assert(repo.getAll()[0].getCadru() == "Mihaita");
	try {
		repo.update(Disciplina("xx", 6, "g", "u"));
	}
	catch (DisciplinaRepoException& ex) {
		cout << ex;
	}
	//Test del
	//cout << d1.getDen() << " " << d1.getOre() << " " << d1.getCadru();
	//cout << repo.getAll().size();
	repo.del(d1);
	try {
		repo.del(d1);
	}
	catch (DisciplinaRepoException&) {}

	Disciplina d2 = Disciplina("sd", 4, "o", "serban");
	repo.store(d2);
	Disciplina d3 = Disciplina("geome", 4, "o", "alina");
	repo.store(d3);
	DictRepo repp;
	try {
		repp.store(Disciplina("ana", 5, "gh", "gg"));
	}
	catch (DisciplinaRepoException& ex) { ex.getMsg(); }
	try {
		repp.store(Disciplina("ana", 5, "gh", "gg"));
	}
	catch (DisciplinaRepoException&ex) { ex.getMsg(); }
	int i = repp.find1("ana");
	int j = repp.find1("hjgh");
	Disciplina duu = repp.find2("ana");
	try {
		Disciplina dry = repp.find2("disciplina");}
	catch (DisciplinaRepoException&) {}
	repp.update(Disciplina("ana", 6, "h", "i"));
	try {
		repp.update(Disciplina("affffna", 5, "gh", "gg"));
	}
	catch (DisciplinaRepoException&) {}
	vector <Disciplina>v = repp.getAll();
	repp.del(Disciplina("ana", 6, "h", "i"));
	try {
		repp.del(Disciplina("a77una", 6, "h", "i"));
	}
	catch (DisciplinaRepoException& ex) { ex.getMsg(); }

	ContractStudii contra{ repo };
	contra.get_disciplina("ana");
	contra.update();
	contra.update_contract();
}

void testService() {
	ContractRepo repo1;
	DisciplinaValidator val;
	ContractService ctrl{ repo1,val };
	//cout<<ctrl.getAll().size();
	ctrl.addDisciplina("sisteme", 4, "facultativ", "Marcel");
	ctrl.undo();
	assert(ctrl.getAll().size() == 1);
	ctrl.undo();
	try {

		ctrl.undo();
	}
	catch (DisciplinaRepoException&) {}
	ctrl.addDisciplina("sisteme", 4, "facultativ", "Marcel");
	Disciplina ddd = ctrl.searchDis("sisteme");
	Disciplina d11 = ctrl.searchDis("uhh");
	ctrl.addDisciplina("structuri", 5, "obligatoriu", "Istvan");
	ctrl.addDisciplina("grafuri", 6, "obligatoriu", "Suciu");
	ctrl.addDisciplina("oop", 5, "facultativ", "Istvan");
	ctrl.addContract("sisteme");
	try {
		ctrl.addContract("siste");
	}
	catch (DisciplinaRepoException&) {}
	ctrl.addRandom(3);
	try {
		ctrl.addDisciplina("oopr", -3, "f", "g");
	}
	catch (ValidateException& ex) {
		cout << ex;
		assert(true);
	}
	auto v = ctrl.getD();
	ctrl.deleteContract();
	try {
		ctrl.addDisciplina("sistem", -4, "g", "t");
	}
	catch (ValidateException&) {
		//assert(true);
	}


	ContractStudii co{ repo1 };

	int i;
	i = ctrl.searchDisciplina("sisteme");
	assert(i == 0);
	assert(ctrl.fltOre(5).size() == 1);
	string cadru = "Suciu";
	assert(ctrl.fltCadru(cadru).size() == 1);
	ctrl.updateDisciplina("sisteme", 4, "facultativ", "Serban");
	ctrl.undo();
	ctrl.updateDisciplina("sisteme", 4, "facultativ", "Serban");
	assert(ctrl.getAll()[0].getCadru() == "Serban");
	assert(ctrl.sortByDen()[0].getDen() == "grafuri");
	assert(ctrl.sortByTip()[0].getTip() == "facultativ");
	assert(ctrl.sortByOre()[0].getOre() == 4);
	assert(ctrl.sortByCadru()[0].getCadru() == "Istvan");
	ctrl.addContract("sisteme");
	ctrl.deleteDisciplina("sisteme", "facultativ");
	
	ctrl.undo();
	ctrl.deleteDisciplina("sisteme", "facultativ");
	try {
		ctrl.deleteDisciplina("sisteme", "facultativ");
	}
	catch (DisciplinaRepoException&) {}
	ctrl.addRandom(2);
	co.update_contract();
	ctrl.exportContractCVS("testCVS.cvs");
	ctrl.exportContractHTML("testHTMl.html");
	try {
		ctrl.exportContractCVS("test/Export.cvs");
	}
	catch (DisciplinaRepoException&) {}
	try {
		ctrl.exportContractHTML("a/b/c/Export.html");
	}
	catch (DisciplinaRepoException&) {}



}
void testFileRepo() {
	std::ofstream out("testDis.txt", std::ios::trunc);
	out.close();
	ContractRepoFile repF{ "testDis.txt" };
	repF.store(Disciplina("mate", 5, "ab", "mihai"));
	ContractRepoFile repF2{ "testDis.txt" };
	auto p = repF2.find2("mate");
	assert(p.getOre() == 5);
	repF2.update(Disciplina("mate", 5, "ab", "xxx"));
	try {
		repF2.find2("aaa2");
	}
	catch (DisciplinaRepoException&) {
	}
	repF2.del(Disciplina("mate", 5, "ab", "xxx"));
	assert(repF2.getAll().size() == 0);
	try {
		repF2.del(Disciplina{ "aaa2",12,"bbb2","dd" });
	}
	catch (DisciplinaRepoException&) {
	}

	ContractRepoFile repF3{ "testDis.txt" };
	assert(repF3.getAll().size() == 0);

	//fisierul nu exista si nu se poate crea (nu se creaza si directoare)
	//ar trebui sa arunce exceptie
	//ContractRepoFile repF4{ "/_###te///\./stPets.txt" };
	try {
		ContractRepoFile repF4{ "/_###stPets.txt" };}
	catch (DisciplinaRepoException&) {}

}

