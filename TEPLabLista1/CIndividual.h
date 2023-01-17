#pragma once
#include <vector>
#include <sstream>

class CKnapsackProblem;
class CIndividual {
public:
	CIndividual(std::vector<int> genotype);
	CIndividual(const CIndividual& other);
	void v_calculate_fitness(CKnapsackProblem* knapsackProblem);
	int i_get_fitness();
	std::vector<int>* pc_get_genotype();
	void v_print_genotype();
	std::string s_get_genotype_string();
	void v_mutate(float mutProbability);
	std::vector<CIndividual*> c_cross_individuals(CIndividual* other);
private:
	std::vector<int> c_genotype;
	int i_fitness;
};