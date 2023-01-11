#include "CKnapsackProblem.h"
#include "CIndividual.h"

CKnapsackProblem::CKnapsackProblem(std::vector<CKnapsackItem*> items, int capacity) {
	pc_items = items;
	i_size = items.size();
	i_capacity = capacity;
}

int CKnapsackProblem::i_get_individual_fitness(CIndividual* pcIndividual) {
	//other way round? (CIndividual calling CKnapsackProblem method)
	pcIndividual->v_calculate_fitness(this);
	return pcIndividual->i_get_fitness();
}

int CKnapsackProblem::i_get_capacity() {
	return i_capacity;
}

int CKnapsackProblem::i_get_size() {
	return i_size;
}

std::vector<CKnapsackItem*> CKnapsackProblem::pc_get_items() {
	return pc_items;
}
