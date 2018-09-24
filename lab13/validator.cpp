#include "validator.h"



void DisciplinaValidator::validate(const Disciplina& d) {
	//vector<string> msgs;
	/*if (d.getOre() < 0) msgs.push_back("Ora negativa!!!");
	if (d.getDen().size() == 0) msgs.push_back("Denumire vida!!!");
	if (d.getTip().size() == 0) msgs.push_back("Tip vid!!!");
	if (d.getCadru().size() == 0) msgs.push_back("Cadru vid!!!");
	if (msgs.size() > 0) { throw ValidateException(msgs); }
	*/
	string msgs;
	if (d.getOre() < 0) msgs += "Ora negativa!!!\n";
	if (d.getDen().size() == 0) msgs += "Denumire vida!!!\n";
	if (d.getTip().size() == 0) msgs += "Tip vid!!!\n";
	if (d.getCadru().size() == 0) msgs += "Cadru vid!!!\n";
	if (size(msgs)>0) { throw ValidateException(msgs); }
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}


