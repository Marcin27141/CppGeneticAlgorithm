#pragma warning(disable : 4996)
#include "CGeneticAlgorithm.h"
#include <random>
#include <chrono>
#include <fstream>
#include <time.h>
using namespace std::chrono;

CGeneticAlgorithm::CGeneticAlgorithm(unsigned int randSeed, int popSize, float crossProb, float mutProb) {
	srand(randSeed);
	ui_seed = randSeed;
	i_solving_time = SOLVING_DURATION_IN_MILISECONDS;

	i_pop_size = (popSize < MIN_POPULATION_SIZE) ? POPULATION_SIZE : popSize;
	f_cross_prob = (crossProb < 0 || crossProb > 1) ? CROSSING_PROBABILITY : crossProb;
	f_mut_prob = (mutProb < 0 || mutProb > 1) ? MUTATION_PROBABILITY : mutProb;

	pc_best_solution = NULL;
	i_best_solution_fitness = -1;
	i_number_of_populations = 0;
}

void CGeneticAlgorithm::v_set_solving_time(int timeInMiliseconds) {
	if (timeInMiliseconds > 0)
		i_solving_time = timeInMiliseconds;
}

CIndividual* CGeneticAlgorithm::pc_get_best_solution() {
	return pc_best_solution;
}

std::vector<CIndividual*> CGeneticAlgorithm::pc_generate_population(int iGenotypeSize) {
	std::vector<CIndividual*> pcPopulation(i_pop_size);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);

	for (int i = 0; i < i_pop_size; i++) {
		std::vector<int> genome(iGenotypeSize);
		for (int j = 0; j < iGenotypeSize; j++)
			genome[j] = distrib(gen);
		pcPopulation[i] = new CIndividual(genome);
	}

	i_number_of_populations++;
	return pcPopulation;
}

CIndividual* CGeneticAlgorithm::pc_get_individuals_fitness(std::vector<CIndividual*>& population, CKnapsackProblem* pcProblem) {
	CIndividual* bestIndividual = population.at(0);
	for (int i = 0; i < i_pop_size; i++) {
		population.at(i)->v_calculate_fitness(pcProblem);
		if (population.at(i)->i_get_fitness() > bestIndividual->i_get_fitness())
			bestIndividual = population.at(i);
	}
	return bestIndividual;
}

CIndividual* CGeneticAlgorithm::pc_select_parent(std::vector<CIndividual*>& population) {
	CIndividual* parentOpt1 = population.at(rand() % i_pop_size);
	CIndividual* parentOpt2 = population.at(rand() % i_pop_size);;
	while (parentOpt2 == parentOpt1) {
		parentOpt2 = population.at(rand() % i_pop_size);
	}
	return (parentOpt1->i_get_fitness() >= parentOpt2->i_get_fitness()) ? parentOpt1 : parentOpt2;
}

std::vector<CIndividual*> CGeneticAlgorithm::pc_cross_population(std::vector<CIndividual*>& prevPopulation) {
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
	std::vector<CIndividual*> currentPopulation = pc_generate_population(pcProblem->i_get_size());
	steady_clock::time_point start = high_resolution_clock::now();
	while ((duration_cast<milliseconds>(high_resolution_clock::now()-start)).count() < i_solving_time) {
		CIndividual* bestInPopulation = pc_get_individuals_fitness(currentPopulation, pcProblem);
		if (bestInPopulation->i_get_fitness() > i_best_solution_fitness) {
			delete pc_best_solution;
			pc_best_solution = new CIndividual(*bestInPopulation);
			i_best_solution_fitness = pc_best_solution->i_get_fitness();
		}
			
		std::vector<CIndividual*> newPopulation = pc_cross_population(currentPopulation);
		for (int i = 0; i < i_pop_size; i++) {
			delete currentPopulation.at(i);
		}
		currentPopulation = newPopulation;

		v_mutate_population(currentPopulation);
	}
	//b_print_record_to_file("CKnapsackRecords.txt");
}

bool CGeneticAlgorithm::b_print_record_to_file(std::string filePath) {
	std::ofstream fileStream(filePath, std::ios::app);
	std::string nextLine;

	if (fileStream.is_open()) {
		time_t my_time = time(NULL);

		fileStream << ctime(&my_time);
		fileStream << "Seed: " << ui_seed << ", Population size: " << i_pop_size << ", Crossing Probability: " << f_cross_prob << ", Mutation Probability: " << f_mut_prob << std::endl;
		fileStream << "Solving time: " << i_solving_time << "ms, Best solution: " << pc_best_solution->s_get_genotype_string() << ", Best solution fitness: " << i_best_solution_fitness << std::endl << std::endl;

		fileStream.close();
		return true;
	}
	else return false;
}