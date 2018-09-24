#pragma once
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock
#include "Observer.h"
#include "repository.h"
#include "domain.h"
using std::vector;
class ContractStudii:public Observable,Observer {
	vector<Disciplina> inContract;
	//const AbstractRepo<Disciplina>&disciplins;
	AbstractRepo& rep;
public:
	//ContractStudii() = default;
	ContractStudii(AbstractRepo& rep) :rep{ rep } {
		rep.addObserver(this);
	}
	void adauga(const Disciplina& d) {
		inContract.push_back(d);
		this->notifyAll();
	}
	void goleste() {
		inContract.clear();
		this->notifyAll();
	}
	void update_contract();
	const std::vector<Disciplina>& addRandom(int cate) {
		genereaza(cate, rep.getAll());
		return lista();
	}
	void genereaza(size_t cate, vector<Disciplina> all) {
		this->goleste();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while (inContract.size() < cate && all.size() > 0) {
			inContract.push_back(all.back());
			all.pop_back();
		}
		this->notifyAll();

	}
	vector<Disciplina>& getAll() {
		return inContract;
	}
	int number() {
		return inContract.size();
	}
	int get_disciplina(const string& den)const;
	void update()override;
	const vector<Disciplina>& lista() const {
		return inContract;
	}
};