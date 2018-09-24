#pragma once
#include <vector>
#include "domain.h"
#include <string>

void exportToCVS(const std::string& fileName, const std::vector<Disciplina>& dis);
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca PetException daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fileName, const std::vector<Disciplina>& dis);