#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include <time.h>
#include <iostream>
#include <sstream>

CIndividual::CIndividual(std::vector<int> genotype) {
	c_genotype = genotype;
}

CIndividual::CIndividual(const CIndividual& other) {
	c_genotype = other.c_genotype;
	i_fitness = other.i_fitness;
}

void CIndividual::v_calculate_fitness(CKnapsackProblem* knapsackProblem) {
	int iFitness = 0;
	int iWeigth = 0;
	std::vector<CKnapsackItem*> cItems = knapsackProblem->c_get_items();
	for (int i = 0; i < knapsackProblem->i_get_size(); i++) {
		if (c_genotype.at(i) == 1) {
			iFitness += cItems.at(i)->i_get_value();
			iWeigth += cItems.at(i)->i_get_weigth();
		}
	}

	i_fitness = (iWeigth > knapsackProblem->i_get_capacity()) ? 0 : iFitness;
}

int CIndividual::i_get_fitness() {
	return i_fitness;
}

std::vector<int>* CIndividual::pc_get_genotype() {
	return &c_genotype;
}

void CIndividual::v_print_genotype() {
	for (int i = 0; i < c_genotype.size(); i++)
		std::cout << c_genotype.at(i);
	std::cout << std::endl;
}

std::string CIndividual::s_get_genotype_string() {
	std::stringstream cStringStream;
	for (int i = 0; i < c_genotype.size(); i++)
		cStringStream << c_genotype.at(i);
	return cStringStream.str();
}

void CIndividual::v_mutate(float mutProbability) {
	for (int i = 0; i < c_genotype.size(); i++) {
		if (mutProbability > ((double)rand() / (RAND_MAX))) {
			c_genotype.at(i) = (c_genotype.at(i) == 1) ? 0 : 1;
		}
	}
}

std::vector<CIndividual*> CIndividual::c_cross_individuals(CIndividual* otherIndividual) {
	int iPartingPoint = (rand() % (c_genotype.size() - 1)) + 1;
	std::vector<CIndividual*> cChildren;

	std::vector<int> firstNewGenotype(c_genotype.begin(), c_genotype.begin() + iPartingPoint);
	std::vector<int> secondNewGenotype(otherIndividual->c_genotype.begin(), otherIndividual->c_genotype.begin() + iPartingPoint);
	for (int i = iPartingPoint; i < c_genotype.size(); i++) {
		firstNewGenotype.push_back(otherIndividual->c_genotype.at(i));
		secondNewGenotype.push_back(c_genotype.at(i));
	}

	cChildren.push_back(new CIndividual(firstNewGenotype));
	cChildren.push_back(new CIndividual(secondNewGenotype));
	return cChildren;
}
