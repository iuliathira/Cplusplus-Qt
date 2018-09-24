#include "disciplinaGUI.h"
#include "domain.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <algorithm>
#include <qpainter.h>
#include <qlistview.h>




void GUI::createRightSide(QVBoxLayout* right) {
	right->addWidget(new QLabel("Name"));
	right->addWidget(txtDen);
	right->addWidget(new QLabel("Ore"));
	right->addWidget(txtOre);
	right->addWidget(new QLabel("Tip"));
	right->addWidget(txtTip);
	right->addWidget(new QLabel("Cadru"));
	right->addWidget(txtCadru);
	right->addStretch();
	right->addWidget(btnAdd);
	right->addWidget(btnUpdate);
	right->addWidget(btnDelete);
	right->addWidget(btnUndo);
	right->addWidget(btnCleanContract);
	right->addWidget(btnGenerate);
	right->addWidget(cntGenerate);
	cntGenerate->setVisible(false);
	right->addWidget(btnContract);
	right->addWidget(btnContract2);
	right->addWidget(btnAddC);
	right->addStretch();
}

void GUI::createLeftSide(QVBoxLayout* left) {


	QVBoxLayout* vert = new QVBoxLayout;
	QHBoxLayout* hor1 = new QHBoxLayout;
	QHBoxLayout* hor2 = new QHBoxLayout;
	view = new QListView;
	model = new MyListModel(view,srv.getAll());
	view->setModel(model);

	QHBoxLayout* lly = new QHBoxLayout;
	widMod->setLayout(lly);
	lly->addWidget(listMod);

	//vert->addWidget(lst);
	vert->addWidget(view);
	//lst->setFixedWidth(600);
	this->changeModel(srv.getAll());
	//vert->addStretch();
	//vert->addStretch();
	vert->addSpacing(50);
	vert->addLayout(hor1);
	vert->addLayout(hor2);
	hor1->addWidget(btnSortByDen);
	hor1->addWidget(btnSortByTip);
	hor1->addWidget(btnSortByOre);
	hor1->addWidget(btnSortByCadru);
	btnFltCadru->setEnabled(false);
	btnFltOre->setEnabled(false);
	/*
	btnFn->setEnabled(false);
	btnFp->setEnabled(false);
	btnFm->setEnabled(false);*/
	hor2->addWidget(btnFltCadru);
	hor2->addWidget(btnFltOre);
	left->addLayout(vert);
	//left->addStretch();
}
/*
void GUI::updateList(const std::vector<Disciplina>& discipline) {
	//lst->clear();
	for (const auto& p : discipline) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getDen()), lst);
		item->setData(Qt::UserRole, QString::fromStdString(p.getTip()));
		//item->setBackground(QBrush{ Qt::black, Qt::SolidPattern });
		QColor colours[10] = { QColor("cyan"), QColor("magenta"), QColor("red"),
			QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
			QColor("green"), QColor("darkGreen"), QColor("yellow"),
			QColor("blue") };
		int i = rand() % 10;
		item->setTextColor(colours[i]);
		//item->setTextColor(Qt::blue);
		item->setData(Qt::UserRole, QString{ "informatii care nu se vad" });
		//item->setCheckState(Qt::Checked);
		//item->setIcon(QApplication::style()->standardIcon(QStyle::SP_BrowserReload));

			//adaug in lista (invizibil) si type 
			/*if (std::find(colorize.cbegin(), colorize.cend(), p) !=colorize.end()){//merge pt ca am adaugat operator== la Pet
			item->setBackground(QBrush{ QColor{Qt::red},Qt::CrossPattern });
			item->setBackgroundColor(QColor{ Qt::red });
			}*/
	//}/
//}
void GUI::showMessageBox(const std::string& msg) {
	QMessageBox::warning(nullptr, "Warning", QString::fromStdString(msg));
}

void GUI::connectAll() {
		QObject::connect(view, &QListView::clicked, [&]() {
			if (view->NoSelection) {
				//nu este nimic selectat (golesc detaliile)
				txtDen->setText("");
				txtTip->setText("");
				txtOre->setText("");
				txtCadru->setText("");
				btnFltCadru->setEnabled(false);
				btnFltOre->setEnabled(false);
				return;
			}

			
			QModelIndex index = view->currentIndex();
			QString info = index.data(Qt::DisplayRole).toString();
			//QStringList list=info
			txtDen->setText(info);

			widMod->show();
			listMod->clear();
			for (auto dis : srv.getModif()) {
				if (dis.getDen() == info.toStdString())
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(dis.getDen() + " " + dis.getTip() + " " + to_string(dis.getOre()) + " " + dis.getCadru()),listMod);
			}

			//QListWidgetItem* selItem = lst->selectedItems().at(0);
			//QString den = selItem->text();
			//txtDen->setText(den);
			//QString tip = selItem->data(Qt::UserRole).toString();
			//txtTip->setText(tip);
			try {
				//cautam Pet
				Disciplina d = srv.searchDis(info.toStdString());
				txtTip->setText(QString::fromStdString(d.getTip()));
				txtOre->setText(QString::number(d.getOre()));
				txtCadru->setText(QString::fromStdString(d.getCadru()));
			}
			catch (DisciplinaRepoException& ex) {
				QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
			}
		});
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {

			//std::stringstream out;
			try {
				this->srv.addDisciplina(txtDen->text().toStdString(),txtOre->text().toInt(),txtTip->text().toStdString(),txtCadru->text().toStdString());
			}
			catch (const ValidateException& ex) {
				showMessageBox(ex.getMsg());
			}
			catch (const DisciplinaRepoException& ex){
				showMessageBox(ex.getMsg());
			}
			//this->updateList(srv.getAll());
			
			this->clearLineEdit();
		});
		QObject::connect(btnDelete, &QPushButton::clicked, [&]() {

			//std::stringstream out;
			try {
				this->srv.deleteDisciplina(txtDen->text().toStdString(), txtTip->text().toStdString());
			}
			catch (const ValidateException& ex) {
				showMessageBox(ex.getMsg());
			}
			catch (const DisciplinaRepoException& ex) {
				showMessageBox(ex.getMsg());
			}
			this->changeModel(srv.getAll());
			this->clearLineEdit();
		});


		

		QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {

			//std::stringstream out;
			try {
				this->srv.updateDisciplina(txtDen->text().toStdString(), txtOre->text().toInt(), txtTip->text().toStdString(), txtCadru->text().toStdString());
			}
			catch (const ValidateException& ex) {
				showMessageBox(ex.getMsg());
			}
			catch (const DisciplinaRepoException& ex) {
				showMessageBox(ex.getMsg());
			}
			this->changeModel(srv.getAll());
			//emit changeDisciplina();
			this->clearLineEdit();
		});
		QObject::connect(btnSortByDen, &QPushButton::clicked, [&]() {
			if (btnSortByDen->isCheckable() == false) {
				changeModel(srv.sortByDen());
				cleanColorsS();
				cleanColorsF();
				btnSortByDen->setCheckable(true);
				activateBtn(false);
				btnSortByDen->setStyleSheet("color: blue;" "background-color: gray;");
			}
			else {
				changeModel(srv.getAll());
				cleanColorsS();
				cleanColorsF();
				activateBtn(true);
			}
		});
		QObject::connect(btnSortByTip, &QPushButton::clicked, [&]() {
			if (btnSortByTip->isCheckable() == false) {
				changeModel(srv.sortByTip());
				cleanColorsS();
				cleanColorsF();
				btnSortByTip->setCheckable(true);
				activateBtn(false);
				btnSortByTip->setStyleSheet("color: blue;" "background-color: gray;");
			}
			else {
				changeModel(srv.getAll());
				cleanColorsS();
				cleanColorsF();
				activateBtn(true);
			}
		});
		QObject::connect(btnSortByCadru, &QPushButton::clicked, [&]() {
			if (btnSortByCadru->isCheckable() == false) {
				changeModel(srv.sortByCadru());
				cleanColorsS();
				cleanColorsF();
				btnSortByCadru->setCheckable(true);
				activateBtn(false);
				btnSortByCadru->setStyleSheet("color: blue;" "background-color: gray;");
			}
			else {
				changeModel(srv.getAll());
				cleanColorsS();
				cleanColorsF();
				activateBtn(true);
			}
		});
		QObject::connect(btnSortByOre, &QPushButton::clicked, [&]() {
			if (btnSortByOre->isCheckable() == false) {
				changeModel(srv.sortByOre());
				cleanColorsS();
				cleanColorsF();
				btnSortByOre->setCheckable(true);
				activateBtn(false);
				btnSortByOre->setStyleSheet("color: blue;" "background-color: gray;");
			}
			else {
				//updateList(srv.getAll());
				changeModel(srv.getAll());
				cleanColorsS();
				cleanColorsF();
				activateBtn(true);
			}
		});
		QObject::connect(btnFltOre, &QPushButton::clicked, [&]() {
			if (btnFltOre->isCheckable() == false) {
				//updateList(srv.fltOre(txtOre->text().toInt()));
				changeModel(srv.fltOre(txtOre->text().toInt()));
				cleanColorsF();
				cleanColorsS();
				btnFltOre->setCheckable(true);
				activateBtn(false);
				btnFltOre->setStyleSheet("color: white;" "background-color: black;");
			}
			else {
				changeModel(srv.getAll());
				//updateList(srv.getAll());
				cleanColorsF();
				cleanColorsS();
				activateBtn(true);
			}
		});
		QObject::connect(btnFltCadru, &QPushButton::clicked, [&]() {
			if (btnFltCadru->isCheckable() == false) {
				//updateList(srv.fltCadru(txtCadru->text().toStdString()));
				changeModel(srv.fltCadru(txtCadru->text().toStdString()));
				cleanColorsF();
				cleanColorsS();
				btnFltCadru->setCheckable(true);
				activateBtn(false);
				btnFltCadru->setStyleSheet("color: white;" "background-color: black;");
			}
			else {
				//updateList(srv.getAll());
				changeModel(srv.getAll());
				cleanColorsF();
				cleanColorsS();
				activateBtn(true);
			}
		});

		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
			try {
				srv.undo();
				changeModel(srv.getAll());
				//updateList(srv.getAll());
			}
			catch (const DisciplinaRepoException&ex) {
				showMessageBox(ex.getMsg());
			}
		});

		QObject::connect(btnContract, &QPushButton::clicked, [&]() {
			ContractGUI* guiC = new ContractGUI{ srv.contract };
			//lst->setCurrentRow(-1);
			guiC->show();
		});

		QObject::connect(btnAddC, &QPushButton::clicked, [&]() {
		
				srv.addContract(txtDen->text().toStdString());
				
				//updateList(srv.getD());	
		});
		QObject::connect(btnCleanContract, &QPushButton::clicked, [&]() {

			srv.deleteContract();
			//updateList(srv.getD());	
		});
		QObject::connect(btnContract2, &QPushButton::clicked, [&]() {
			ContractROGUI* guiC2 = new ContractROGUI{ srv.contract };
			//lst->setCurrentRow(-1);
			guiC2->show();
		});

		QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
			if (cntGenerate->isVisible() == false) {
				cntGenerate->setVisible(true);
			}
			else {
				srv.addRandom(cntGenerate->value());
				//srv.contract.generate(cntGenerate->value());
				cntGenerate->setVisible(false);
			}
		});

}

void GUI::clearLineEdit()
{
	txtDen->setText("");
	txtOre->setText("");
	txtTip->setText("");
	txtCadru->setText("");
}


void GUI::activateBtn(bool status)
{
	if (status == true) {
		if (btnSortByDen->isCheckable() == false && btnSortByCadru->isCheckable() == false && btnSortByTip->isCheckable() == false && btnSortByOre->isCheckable() == false && btnFltCadru->isCheckable() == false && btnFltOre->isCheckable() == false) {
			btnAdd->setEnabled(status);
			btnUpdate->setEnabled(status);
			btnDelete->setEnabled(status);
			btnUndo->setEnabled(status);
		}
	}
	else {
		btnAdd->setEnabled(status);
		btnUpdate->setEnabled(status);
		btnDelete->setEnabled(status);
		btnUndo->setEnabled(status);
	}
}


void GUI::cleanColorsS()
{
	btnSortByDen->setStyleSheet("color:black;" "background-color: light gray;");
	btnSortByTip->setStyleSheet("color:black" "background-color: light gray;");
	btnSortByOre->setStyleSheet("color:black" "background-color: light gray;");
	btnSortByCadru->setStyleSheet("color:black" "background-color: light gray;");

	btnSortByDen->setCheckable(false);
	btnSortByTip->setCheckable(false);
	btnSortByOre->setCheckable(false);
	btnSortByCadru->setCheckable(false);
}

void GUI::cleanColorsF()
{
	btnFltCadru->setStyleSheet("color:black" "background-color: light gray;");
	btnFltOre->setStyleSheet("color:black" "background-color: light gray;");
	
	btnFltCadru->setCheckable(false);
	btnFltOre->setCheckable(false);
}

void GUI::createGUI()
{
	QVBoxLayout*right = new QVBoxLayout;
	QVBoxLayout*left = new QVBoxLayout;
	QHBoxLayout* mainLayout = new QHBoxLayout;

	createRightSide(right);
	createLeftSide(left);

	mainLayout->addLayout(left);
	mainLayout->addStretch();
	mainLayout->addLayout(right);
	this->setLayout(mainLayout);
}

void ContractGUI::createGUI() {
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(lstContract);
	//layout->addWidget(priceLabel);
	//priceLabel->setText("Price: 0");
	//lstContract->setReadOnly(true);
	//lstContract->setLineWidth(600);
	layout->addWidget(btnGenerate);
	layout->addWidget(cntGenerate);
	layout->addWidget(btnCleanContract);
	layout->addWidget(btnSHTML);
	layout->addWidget(btnSCVS);
	layout->addWidget(cartFileName);
	cntGenerate->setVisible(false);
	cartFileName->setVisible(false);
	this->setFixedWidth(300);
	this->setFixedHeight(500);
	this->setLayout(layout);
	update();

}


void ContractGUI::connectAll()
{
	QObject::connect(btnCleanContract, &QPushButton::clicked, [&]() {
		contract.goleste();
	});



	


	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		if (cntGenerate->isVisible() == false) {
			cntGenerate->setVisible(true);
		}
		else {
			contract.addRandom(cntGenerate->value());
			//contract.genereaza(cntGenerate->value(),contract.getAll());
			cntGenerate->setVisible(false);
		}
	});
	/*
	QObject::connect(btnSHTML, &QPushButton::clicked, [&]() {
		if (cartFileName->isVisible() == false) {
			cartFileName->setVisible(true);
			btnSCVS->setEnabled(false);
		}
		else {
			cartFileName->setVisible(false);
			btnSCVS->setEnabled(true);
			srv.exportContractHTML(cartFileName->text().toStdString());
			cartFileName->setText("");
			contract.goleste();
			lstContract->setText("");
			//priceLabel->setText(QString::fromStdString("Price: " + std::to_string(crt.get_price())));
			QMessageBox::warning(nullptr, "Warning", "Contract saved!");
		}
	});*/
	/*
	QObject::connect(btnSCVS, &QPushButton::clicked, [&]() {
		if (cartFileName->isVisible() == false) {
			cartFileName->setVisible(true);
			btnSHTML->setEnabled(false);
		}
		else {
			cartFileName->setVisible(false);
			btnSHTML->setEnabled(true);
			srv.exportContractCVS(cartFileName->text().toStdString());
			cartFileName->setText("");
			contract.goleste();
			lstContract->setText("");
			//priceLabel->setText(QString::fromStdString("Price: " + std::to_string(crt.get_price())));
			QMessageBox::warning(nullptr, "Warning", "Contract saved!");
		}
	});*/
}

void ContractGUI::update() {
	lstContract->clear();
	for (const auto& p : contract.getAll()) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getDen()),lstContract);
		item->setData(Qt::UserRole, QString::fromStdString(p.getTip()));
		//item->setBackground(QBrush{ Qt::black, Qt::SolidPattern });
		QColor colours[10] = { QColor("cyan"), QColor("magenta"), QColor("red"),
			QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
			QColor("green"), QColor("darkGreen"), QColor("yellow"),
			QColor("blue") };
		int i = rand() % 10;
		item->setTextColor(colours[i]);
	}
}

void ContractROGUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> w(0, this->size().width() - 50);
	std::uniform_int_distribution<> h(0, this->size().height() - 50);
	srand(time(0));
	int x, y;
	auto n = ctr.number();
	if (n != 0) {
		n -= list.size();
		for (const auto& x : list) {
			p.setPen(x.c);
			p.drawEllipse(x.x, x.y, 50, 50);
		}
		while (n) {
			n--;
			x = w(mt);
			y = h(mt);
			object o{ x,y,QColor(rand() % 255, rand() % 255, rand() % 255) };
			p.setPen(o.c);
			//QLine* ln=new QLine;
			//p.drawLine(ln);
		//	p.drawConvexPolygon(x, 50);
			//p.drawConvexPolygon(p);
			//p.drawConvexPolygon(x, y, 50, 50);
			p.drawRect(x, y, 30, 30);
			//p.drawEllipse(x, y, 50, 50);
			list.push_back(o);

		}
	}
	else {
		list.clear();
	}
}

void ContractROGUI::update()
{
	setUpdatesEnabled(true);
	this->repaint();
	setUpdatesEnabled(false);
}







