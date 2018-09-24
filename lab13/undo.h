#pragma once
#include "domain.h"
#include "repository.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};
class UndoAdauga : public ActiuneUndo {
	Disciplina disAdaugata;
	//ContractRepo& rep;
	AbstractRepo& rep;
public:
	//UndoAdauga(ContractRepo& rep, const Disciplina& d) :rep{ rep }, disAdaugata{ d } {}
	UndoAdauga(AbstractRepo& rep, const Disciplina& d) :rep{ rep }, disAdaugata{ d } {}
	void doUndo() override {
		rep.del(disAdaugata);
	}
};
class UndoSterge : public ActiuneUndo {
	Disciplina disStearsa;
	//ContractRepo& rep;
	AbstractRepo& rep;
public:
	//UndoSterge(ContractRepo& rep, const Disciplina& d) :rep{ rep }, disStearsa{ d } {}
	UndoSterge(AbstractRepo& rep, const Disciplina& d) :rep{ rep }, disStearsa{ d } {}
	void doUndo() override {
		rep.store(disStearsa);
	}
};
class UndoModifica : public ActiuneUndo {
	Disciplina disModificata;
	//ContractRepo& rep;
	AbstractRepo& rep;
public:
	//UndoModifica(ContractRepo& rep, const Disciplina& d) :rep{ rep }, disModificata{ d } {}
	UndoModifica(AbstractRepo& rep, const Disciplina& d) :rep{ rep }, disModificata{ d } {}
	void doUndo() override {
		rep.update(disModificata);
	}
};






