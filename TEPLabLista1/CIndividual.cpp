#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include <time.h>

CIndividual::CIndividual(std::vector<bool> genotype) {
	pc_genotype = genotype;
}

CIndividual::CIndividual(const CIndividual& pc_other) {
	pc_genotype = pc_other.pc_genotype;
	i_fitness = pc_other.i_fitness;
}

void CIndividual::v_calculate_fitness(CKnapsackProblem* pcProblem) {
	int fitness = 0;
	int weigth = 0;
	std::vector<CKnapsackItem*> items = pcProblem->pc_get_items();
	for (int i = 0; i < pcProblem->i_get_size(); i++) {
		if (pc_genotype.at(i) == 1) {
			fitness += items.at(i)->i_get_value();
			weigth += items.at(i)->i_get_weigth();
		}
	}

	i_fitness = (weigth > pcProblem->i_get_capacity()) ? 0 : fitness;
}

int CIndividual::i_get_fitness() {
	return i_fitness;
}

std::vector<bool>* CIndividual::pc_get_genotype() {
	return &pc_genotype;
}

void CIndividual::v_mutate(float f_mut_probability) {
	for (int i = 0; i < pc_genotype.size(); i++) {
		if (f_mut_probability > ((double)rand() / (RAND_MAX)))
			pc_genotype.at(i).flip();
	}
}

std::vector<CIndividual*> CIndividual::pc_cross_individuals(CIndividual* pc_other_individual) {
	int partingPoint = (rand() % (pc_genotype.size() - 1)) + 1;
	std::vector<CIndividual*> children;

	std::vector<bool> firstNewGenotype(pc_genotype.begin(), pc_genotype.begin() + partingPoint);
	std::vector<bool> secondNewGenotype(pc_other_individual->pc_genotype.begin(), pc_other_individual->pc_genotype.begin() + partingPoint);
	for (int i = partingPoint; i < pc_genotype.size(); i++) {
		firstNewGenotype.push_back(pc_other_individual->pc_genotype.at(i));
		secondNewGenotype.push_back(pc_genotype.at(i));
	}

	children.push_back(new CIndividual(firstNewGenotype));
	children.push_back(new CIndividual(secondNewGenotype));
	return children;
}
