#include "lab13.h"
#include "tests.h"
#include "repository.h"
#include "service.h"
#include <QtWidgets/QApplication>
#include "validator.h"
#include "disciplinaGUI.h"
#include <crtdbg.h>
#include "console.h"
void testAll() {
	testDomain();
	testRepo();
	testService();
	testFileRepo();
}

void ConsoleUI() {
	ContractRepoFile rep{ "dis.txt" };
	DisciplinaValidator val;
	ContractService ctr{ rep,val };
	ConsoleUi ui{ ctr };
	ui.start();

	
	//Test tst;
	//tst.run();

}

int GUI_init(int argc, char *argv[]) {
	//testAll();
	
	ContractRepoFile rep{ "dis.txt" };
	DisciplinaValidator val;
	ContractService ctr{ rep,val };

	QApplication a(argc, argv);
	GUI gui{ ctr };
	gui.show();
	
	//ConsoleUI();
	return a.exec();
}

int main(int argc, char *argv[])
{
	return GUI_init(argc, argv);
}
