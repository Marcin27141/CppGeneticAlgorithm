#pragma once
#include <vector>
#include "CIndividual.h"

class CKnapsackProblem {
public:
	CKnapsackProblem(std::vector<int> values, std::vector<int> weigths, int capacity);
	int i_get_individual_fitness(CIndividual* pcIndividual);
	int i_get_size();
	friend class CIndividual;
private:
	int i_capacity;
	int i_size;
	std::vector<int> pi_values;
	std::vector<int> pi_weigths;
};