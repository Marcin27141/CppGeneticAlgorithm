#include "CKnapsackProblem.h"
#include "CIndividual.h"

CKnapsackProblem::CKnapsackProblem(std::vector<int> values, std::vector<int> weigths, int capacity) {
	//pair datatype for weight/value
	i_size = -1;
	i_capacity = -1;
	if (values.size() == weigths.size()) {
		i_capacity = capacity;
		i_size = values.size();
		pi_values = values;
		pi_weigths = weigths;
	}
}

int CKnapsackProblem::i_get_individual_fitness(CIndividual* pcIndividual) {
	//other way round? (CIndividual calling CKnapsackProblem method)
	pcIndividual->v_calculate_fitness(this);
	return pcIndividual->i_get_fitness();
}

int CKnapsackProblem::i_get_size() {
	return i_size;
}
