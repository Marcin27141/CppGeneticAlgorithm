#pragma once
#include <vector>

class CKnapsackProblem;
class CIndividual {
public:
	CIndividual(std::vector<bool> genotype);
	CIndividual(const CIndividual& pc_other);
	void v_calculate_fitness(CKnapsackProblem* pcProblem);
	int i_get_fitness();
	std::vector<bool>* pc_get_genotype();
	void v_mutate(float f_mut_probability); //fix arguments name conventions
	std::vector<CIndividual*> pc_cross_individuals(CIndividual* pc_other_individual);
private:
	std::vector<bool> pc_genotype;
	int i_fitness;
};