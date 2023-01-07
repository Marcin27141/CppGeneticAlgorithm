#pragma once
#include <vector>

class CKnapsackProblem;
class CIndividual {
public:
	CIndividual(std::vector<short> genotype);
	CIndividual(const CIndividual& pc_other);
	void v_calculate_fitness(CKnapsackProblem* pcProblem);
	int i_get_fitness();
	std::vector<short>* pc_get_genotype();
	void v_mutate();
	std::vector<CIndividual*> pc_cross_individuals(CIndividual* pc_other_individual);
private:
	std::vector<short> pc_genotype;
	int i_fitness;
};