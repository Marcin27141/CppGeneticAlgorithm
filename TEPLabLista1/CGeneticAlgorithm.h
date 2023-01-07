#pragma once
#include <vector>
#include "CIndividual.h"
#include "CKnapsackProblem.h"

static const int POPULATION_SIZE = 4;
static const float CROSSING_PROBABILITY = 0.6f;
static const float MUTATION_PROBABILITY = 0.1f;
static const int LIMIT_OF_POPULATIONS = 10;

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm(int popSize, float crossProb, float mutProb);
	CGeneticAlgorithm() : CGeneticAlgorithm(POPULATION_SIZE, CROSSING_PROBABILITY, MUTATION_PROBABILITY) {}
	void v_solve_problem(CKnapsackProblem* pcProblem);
	std::vector<bool> pc_get_best_solution();
private:
	int i_pop_size;
	float f_cross_prob;
	float f_mut_prob;
	std::vector<bool> pc_best_solution;
	int i_best_solution_fitness;
	std::vector<CIndividual*> pc_generate_population(int iGenotypeSize);
	CIndividual* pc_get_individuals_fitness(std::vector<CIndividual*> population, CKnapsackProblem* pcProblem);
	std::vector<CIndividual*> pc_cross_population(std::vector<CIndividual*> prevPopulation);
	void v_mutate_population(std::vector<CIndividual*>& population);
	int i_number_of_populations;
};