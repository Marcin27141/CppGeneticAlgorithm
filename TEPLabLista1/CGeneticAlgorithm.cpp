#include "CGeneticAlgorithm.h"
#include <random>
#include <time.h>

CGeneticAlgorithm::CGeneticAlgorithm(int popSize, float crossProb, float mutProb) {
	i_pop_size = (popSize < MIN_POPULATION_SIZE) ? POPULATION_SIZE : popSize;
	f_cross_prob = (crossProb < 0 || crossProb > 1) ? CROSSING_PROBABILITY : crossProb;
	f_mut_prob = (f_mut_prob < 0 || f_mut_prob > 1) ? MUTATION_PROBABILITY : f_mut_prob;

	pc_best_solution = std::vector<bool>();
	i_best_solution_fitness = -1;
	i_number_of_populations = 0;
}

std::vector<bool> CGeneticAlgorithm::pc_get_best_solution() {
	return pc_best_solution;
}

std::vector<CIndividual*> CGeneticAlgorithm::pc_generate_population(int iGenotypeSize) {
	std::vector<CIndividual*> pcPopulation(i_pop_size);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);

	for (int i = 0; i < i_pop_size; i++) {
		std::vector<bool> genome(iGenotypeSize);
		for (int j = 0; j < iGenotypeSize; j++)
			genome[j] = distrib(gen);
		pcPopulation[i] = new CIndividual(genome);
	}

	i_number_of_populations++;
	return pcPopulation;
}

CIndividual* CGeneticAlgorithm::pc_get_individuals_fitness(std::vector<CIndividual*> population, CKnapsackProblem* pcProblem) {
	CIndividual* bestIndividual = population.at(0); //safe?
	for (int i = 0; i < i_pop_size; i++) {
		population.at(i)->v_calculate_fitness(pcProblem);
		if (population.at(i)->i_get_fitness() > bestIndividual->i_get_fitness())
			bestIndividual = population.at(i);
	}
	return bestIndividual;
}

CIndividual* CGeneticAlgorithm::pc_select_parent(std::vector<CIndividual*> population) {
	CIndividual* parentOpt1 = population.at(rand() % i_pop_size);
	CIndividual* parentOpt2;
	do {
		parentOpt2 = population.at(rand() % i_pop_size);
	} while (parentOpt2 == parentOpt1);
	return (parentOpt1->i_get_fitness() >= parentOpt2->i_get_fitness()) ? parentOpt1 : parentOpt2;
}

std::vector<CIndividual*> CGeneticAlgorithm::pc_cross_population(std::vector<CIndividual*> prevPopulation) {
	std::vector<CIndividual*> pcNewPopulation;
	while (pcNewPopulation.size() < i_pop_size) {
		CIndividual* firstParent = pc_select_parent(prevPopulation);
		CIndividual* secondParent = pc_select_parent(prevPopulation);

		if (f_cross_prob > ((double)rand() / (RAND_MAX))) {
			std::vector<CIndividual*> children = firstParent->pc_cross_individuals(secondParent);
			pcNewPopulation.push_back(children.at(0));
			pcNewPopulation.push_back(children.at(1));
		}
		else {
			pcNewPopulation.push_back(new CIndividual(*firstParent));
			pcNewPopulation.push_back(new CIndividual(*secondParent));
		}
	}

	i_number_of_populations++;
	return pcNewPopulation;
}

void CGeneticAlgorithm::v_mutate_population(std::vector<CIndividual*>& population) {
	for (int i = 0; i < population.size(); i++) {
		population.at(i)->v_mutate(f_mut_prob);
	}
}

void CGeneticAlgorithm::v_solve_problem(CKnapsackProblem* pcProblem) {
	srand(time(NULL));
	std::vector<CIndividual*> currentPopulation = pc_generate_population(pcProblem->i_get_size());
	while (i_number_of_populations < LIMIT_OF_POPULATIONS) {
		CIndividual* bestInPopulation = pc_get_individuals_fitness(currentPopulation, pcProblem);
		if (bestInPopulation->i_get_fitness() > i_best_solution_fitness) {
			pc_best_solution = *(bestInPopulation->pc_get_genotype());
			i_best_solution_fitness = bestInPopulation->i_get_fitness();
		}

		
		std::vector<CIndividual*> newPopulation = pc_cross_population(currentPopulation);
		for (int i = 0; i < i_pop_size; i++) {
			delete currentPopulation.at(i);
		}
		currentPopulation = newPopulation;

		v_mutate_population(currentPopulation);
	}
}