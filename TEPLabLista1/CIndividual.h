#pragma once
#include <vector>
#include <sstream>

class CKnapsackProblem;
class CIndividual {
public:
	CIndividual(std::vector<int> genotype);
	CIndividual(const CIndividual& pc_other);
	void v_calculate_fitness(CKnapsackProblem* pcProblem);
	int i_get_fitness();
	std::vector<int>* pc_get_genotype();
	void v_print_genotype();
	std::string s_get_genotype_string();
	void v_mutate(float f_mut_probability); //fix arguments name conventions
	std::vector<CIndividual*> pc_cross_individuals(CIndividual* pc_other_individual);
	
private:
	std::vector<int> pc_genotype;
	int i_fitness;
};