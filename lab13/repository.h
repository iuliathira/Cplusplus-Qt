#pragma once
#include <vector>
#include <string>
#include "domain.h"
#include <map>
#include <random>
#include "Observer.h"
using namespace std;








class DisciplinaRepoException {
	string msg;
public:
	DisciplinaRepoException(string m) :msg{ m } {}
	string getMsg()const { return msg; }
	friend ostream& operator<<(ostream& out, const DisciplinaRepoException& ex);

};

class AbstractRepo:public Observable
{
public:
	AbstractRepo() = default;
	AbstractRepo(const AbstractRepo& ot) = delete;
	virtual ~AbstractRepo() = default;
	virtual void store(const Disciplina& d) = 0;
	virtual void del(const Disciplina& d) = 0;
	virtual int find1(const string& den) const = 0;
	virtual const Disciplina& find2(const string& den) const = 0;
	virtual void update(const Disciplina& d) = 0;
	virtual  vector<Disciplina> getAll() const noexcept = 0;
	


};


class DictRepo : public AbstractRepo
{
	std::map<int, Disciplina> dict;
	//vector<Disciplina> v;
	int nr = 0;
	float p;
public:
	DictRepo() { this->p = 0.5; };
	//~DictRepo() = default;
	void store(const Disciplina& d) override {
		//AbstractRepo::store(d);

		for (auto& dis : dict)
		{
			if (dis.second.getDen() == d.getDen())
				throw DisciplinaRepoException("Disciplina existenta!!");
		}
		dict.insert(std::pair<int, Disciplina>(nr, d));
		nr++;
		float r;
		r = (float)(rand()) / float(RAND_MAX);
		//r = r / 10;
		cout << "Random e: " << r << "  iar p e " << p << endl;
		if (r < p)
		{
			throw DisciplinaRepoException("Random a aruncat exceptie!");
		}
	}

	void del(const Disciplina& d) override {
		//AbstractRepo::del(d)
		int poz = -1;
		cout << "Sunt in dictrepooo!" << endl;
		//std::map<int,Disciplina>::iterator it;
		//it = dict.find(d.getDen());
		//dict.erase(it);
		for (auto it = dict.begin();it != dict.end();it++)
		{
			poz++;
			if (it->second.getDen() == d.getDen())
			{
				break;
			}

		}
		/*for (auto& dis : dict) {
		if (dis.second.getDen() == d.getDen()) {
		poz = dis.first;
		break;
		}		}*/
		if (poz > -1) {
			dict.erase(poz);
			nr--;
		}
		else
			throw DisciplinaRepoException("Disciplina inexistenta!");

	}
	void update(const Disciplina& d) override {
		//AbstractRepo::update(d);
		//std::map<string, Disciplina>::iterator it;
		int poz = -1;
		//it = dict.find(d.getDen());
		for (auto&dis : dict) {
			if (dis.second.getDen() == d.getDen()) {
				dis.second = d;
				poz = dis.first;
				break;
			}
			
		}
		if (poz == -1)
			throw DisciplinaRepoException("Disciplina nu exista!");
		//dict.at(d.getDen()) = d);
	}

	int find1(const string& den) const override {
		int poz = -1;
		for (auto& dis : dict) {
			if (dis.second.getDen() == den) {
				poz = dis.first;
				return poz;
			}
		}
		return -1;

	}
	const Disciplina& find2(const string& den)const override {
		//for (std::map<char, int>::iterator it = dict.begin(); it != dict.end(); ++it)
		//std::cout << it->first << " => " << it->second << '\n';
		int poz = -1;
		for (auto& dis : dict) {
			if (dis.second.getDen() == den) {
				poz = dis.first;
				return dis.second;
			}
		}
		throw DisciplinaRepoException("Disciplina nu existaa!");
	}
	/*
	const vector<Disciplina>& getAll() noexcept override {
	for(const auto& d: dict) {
	v.push_back(d.second);
	}
	}*/
	vector<Disciplina> getAll()  const noexcept override {
		vector<Disciplina> v;
		for (const auto& d : dict) {
			v.push_back(d.second);

		}
		return v;
	}
};

class ContractRepo : public AbstractRepo {
	std::vector <Disciplina> all;
	//std::vector < pair<Disciplina, vector<string>>> modificari;
	//std::multimap<string, string> multiMap;

	//vector <Disciplina> contractStudii;
	//bool exist(const Disciplina& d);


public:
	ContractRepo() :AbstractRepo() {};
	/*
	void store(const Disciplina& d) override {
	AbstractRepo::store(d);//se apeleaza metoda din clasa de baza
	}*/

	ContractRepo(const ContractRepo& ot) = delete;
	~ContractRepo() = default;
	void store(const Disciplina& d) override;
	void del(const Disciplina& d) override;
	//AbstractRepo::del(d);
	//}
	int find1(const string& den) const override;
	const Disciplina& find2(const string& den) const override;
	void update(const Disciplina& d) override;
	vector<Disciplina> getAll() const  noexcept override;

	/*ContractRepo() = default;
	ContractRepo(const ContractRepo& ot) = delete;
	virtual ~ContractRepo() = default;
	virtual void store(const Disciplina& d);
	virtual void del(const Disciplina& d);
	int find1(const string& den) const;
	const Disciplina& find2(const string& den) const;
	virtual void update(const Disciplina& d);
	const vector<Disciplina>& getAll()const noexcept;*/

	//const vector<Disciplina>& getCont()const noexcept;
	//void delC();
	//void addC(const string& den);
};



//class ContractRepoFile : public ContractRepo {
class ContractRepoFile : public ContractRepo {
private:
	std::string fileName;
	void loadFromFile();
	void writeToFile();
public:
	ContractRepoFile(std::string fileName) :ContractRepo(), fileName{ fileName } {
		loadFromFile();//incarc datele din fisier
	}
	void store(const Disciplina& d) override {
		ContractRepo::store(d);//se apeleaza metoda din clasa de baza
		writeToFile();
	}
	void del(const Disciplina& d) override {
		ContractRepo::del(d);
		writeToFile();
	}
	void update(const Disciplina& d) override {
		ContractRepo::update(d);
		writeToFile();
	}

};
