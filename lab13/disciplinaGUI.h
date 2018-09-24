#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include "service.h"
#include "domain.h"
#include <vector>
#include <qlabel.h>
#include <qspinbox.h>
#include "Observer.h"
#include <qtextedit.h>


class MyListModel :public QAbstractListModel {
	Q_OBJECT
private:
	std::vector<Disciplina>vec;
public:
	MyListModel(QListView* parent, std::vector<Disciplina> vec) :QAbstractListModel{ parent }, vec{ vec } {
		changed();
	};
	int rowCount(const QModelIndex & w = QModelIndex()) const override {
		return int(vec.size());
	}
	QVariant data(const QModelIndex &index, int role)const override {
		if (role == Qt::DisplayRole) {
			return QString::fromStdString(vec[index.row()].getDen() );
		}
		if (role == Qt::UserRole) {
			return QString::fromStdString(vec[index.row()].getDen());
		}
		return QVariant();
	}
	void changed() {
		QModelIndex top = createIndex(0, 0);
		QModelIndex bottom = createIndex(rowCount(), 0);
		emit dataChanged(top, bottom);
	}
};

class GUI :public QWidget {
	Q_OBJECT
private:

	QPushButton * btnSortByDen=new QPushButton("Sort by den");
	QPushButton* btnSortByTip = new QPushButton("Sort by tip");
	QPushButton* btnSortByOre = new QPushButton("Sort by ore");
	QPushButton* btnSortByCadru = new QPushButton("Sort by cadru");

	QWidget* widMod=new QWidget;
	QListWidget* listMod = new QListWidget;
	

	QLineEdit* txtDen=new QLineEdit;
	QLineEdit* txtTip=new QLineEdit;
	QLineEdit* txtOre=new QLineEdit;
	QLineEdit* txtCadru=new QLineEdit;
	QLineEdit* txtDen1 = new QLineEdit;
	QLineEdit* txtOreF = new QLineEdit;
	QLineEdit* txtCadruF = new QLineEdit;
	QLineEdit* txtNr = new QLineEdit;

	QPushButton* btnAdd= new QPushButton("&Add");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnContract = new QPushButton("Contract");
	QPushButton* btnContract2 = new QPushButton("ContractRO");
	QPushButton* btnAddC = new QPushButton("Add contract");

	QPushButton* btnDelete = new QPushButton("Delete");
	QPushButton* btnUpdate = new QPushButton("Update");
	QPushButton* btnTipareste = new QPushButton("Tiparire");
	QPushButton* btnCauta = new QPushButton("Cauta");

	QPushButton* btnFltOre = new QPushButton("Filter by hours");
	QPushButton* btnFltCadru= new QPushButton("Filter by cadru");
    
	QPushButton* btnCleanContract = new QPushButton("Clean");
	QPushButton* btnGenerate = new QPushButton("Generate");
	QSpinBox* cntGenerate = new QSpinBox;

	//QListWidget* lst = new QListWidget;
	QListView* view;
	MyListModel* model;


	ContractService & srv;

	void createRightSide(QVBoxLayout* right);
	void createLeftSide(QVBoxLayout* left);
	//void updateList(const std::vector<Disciplina>&);
	void showMessageBox(const std::string&);
	void connectAll();
	void changeModel(std::vector<Disciplina> discipline) {
		delete view->model();
		model = new MyListModel(view, discipline);
		view->setModel(model);
	}
	void clearLineEdit();
	void activateBtn(bool status);
	void cleanColorsS();
	void cleanColorsF();
signals:
	void changeDisciplina();
public:
	void createGUI();
	GUI(ContractService& srv) :srv{ srv } {
		createGUI();
		connectAll();
	};

};

class ContractGUI :public QWidget, Observer {
	Q_OBJECT
private:
	//ContractService & srv;
	ContractStudii & contract;
	QPushButton* btnCleanContract = new QPushButton("Clean");
	QPushButton* btnGenerate = new QPushButton("Generate");
	QPushButton* btnSHTML = new QPushButton("Save HTML");
	QPushButton* btnSCVS = new QPushButton("Save CVS");
	QSpinBox* cntGenerate = new QSpinBox;
	QLineEdit* cartFileName = new QLineEdit;
	//QLabel* priceLabel = new QLabel;
	QListWidget* lstContract = new QListWidget;

	void createGUI();
	void connectAll();

public:
	void update()override;
	ContractGUI(ContractStudii&crt) :contract{ crt }  {
		createGUI();
		connectAll();
		crt.addObserver(this);
	};
};
struct object {
	int x, y;
	QColor c;
	object(int x, int y, QColor c) :x{ x }, y{ y }, c{ c } {};

};

class ContractROGUI :public QWidget, Observer {
	Q_OBJECT
private:
	std::vector<object> list;
	ContractStudii& ctr;
	void paintEvent(QPaintEvent* ev) override;
public:
	ContractROGUI(ContractStudii& ctr) :ctr{ ctr } {
		ctr.addObserver(this);
		setUpdatesEnabled(false);
		update();
	}
	void update();

};