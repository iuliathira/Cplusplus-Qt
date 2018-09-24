#include "exporta.h"
#include "domain.h"
#include <fstream>
#include <string>
#include <vector>
#include "repository.h"
/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca PetException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fileName, const std::vector<Disciplina>& dis) {
	std::ofstream out(fileName, std::ios::trunc);
	if (!out.is_open()) {
		throw DisciplinaRepoException("Unable to open file:" + fileName);
	}
	for (const auto& d : dis) {
		out << d.getDen() << ",";
		out << d.getOre() << ",";
		out << d.getTip() << ",";
		out << d.getCadru() << std::endl;
	}
	out.close();
}
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca PetException daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fileName, const std::vector<Disciplina>& dis) {
	std::ofstream out(fileName, std::ios::trunc);
	if (!out.is_open()) {
		throw DisciplinaRepoException("Unable to open file:" + fileName);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& d : dis) {
		out << "<tr>" << std::endl;
		out << "<td>" << d.getDen() << "</td>" << std::endl;
		out << "<td>" << d.getOre() << "</td>" << std::endl;
		out << "<td>" << d.getTip() << "</td>" << std::endl;
		out << "<td>" << d.getCadru() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}