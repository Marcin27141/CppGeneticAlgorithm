#pragma once
#include <vector>
#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include <time.h>

static const int SOLVING_DURATION_IN_MILISECONDS = 10;
static const int POPULATION_SIZE = 4;
static const int MIN_POPULATION_SIZE = 2;
static const float CROSSING_PROBABILITY = 0.6f;
static const float MUTATION_PROBABILITY = 0.1f;

class CGeneticAlgorithm {
public:
	CGeneticAlgorithm(unsigned int randSeed, int popSize, float crossProb, float mutProb);
	CGeneticAlgorithm(int popSize, float crossProb, float mutProb) : CGeneticAlgorithm(time(NULL), POPULATION_SIZE, CROSSING_PROBABILITY, MUTATION_PROBABILITY) {}
	CGeneticAlgorithm() : CGeneticAlgorithm(POPULATION_SIZE, CROSSING_PROBABILITY, MUTATION_PROBABILITY) {}
	void v_set_solving_time(int timeInMiliseconds);
	void v_solve_problem(CKnapsackProblem* pcProblem);
	CIndividual* pc_get_best_solution();
private:
	unsigned int ui_seed;
	int i_solving_time;
	int i_pop_size;
	float f_cross_prob;
	float f_mut_prob;
	CIndividual* pc_best_solution;
	int i_best_solution_fitness;
	std::vector<CIndividual*> pc_generate_population(int iGenotypeSize);
	CIndividual* pc_get_individuals_fitness(std::vector<CIndividual*>& population, CKnapsackProblem* pcProblem);
	CIndividual* pc_select_parent(std::vector<CIndividual*>& population);
	std::vector<CIndividual*> pc_cross_population(std::vector<CIndividual*>& prevPopulation);
	void v_mutate_population(std::vector<CIndividual*>& population);
	bool b_print_record_to_file(std::string filePath);
	int i_number_of_populations;
};