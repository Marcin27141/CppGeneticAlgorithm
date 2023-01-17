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

CGeneticAlgorithm::~CGeneticAlgorithm() {
	delete pc_best_solution;
}

void CGeneticAlgorithm::v_set_solving_time(int timeInMiliseconds) {
	if (timeInMiliseconds > 0)
		i_solving_time = timeInMiliseconds;
}

CIndividual* CGeneticAlgorithm::pc_get_best_solution() {
	return pc_best_solution;
}

std::vector<CIndividual*> CGeneticAlgorithm::c_generate_population(int genotypeSize) {
	std::vector<CIndividual*> cPopulation(i_pop_size);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);

	for (int i = 0; i < i_pop_size; i++) {
		std::vector<int> genotype(genotypeSize);
		for (int j = 0; j < genotypeSize; j++)
			genotype[j] = distrib(gen);
		cPopulation[i] = new CIndividual(genotype);
	}

	i_number_of_populations++;
	return cPopulation;
}

CIndividual* CGeneticAlgorithm::pc_get_individuals_fitness(std::vector<CIndividual*>& population, CKnapsackProblem* knapsackProblem) {
	CIndividual* pcBestIndividual = population.at(0);
	for (int i = 0; i < i_pop_size; i++) {
		population.at(i)->v_calculate_fitness(knapsackProblem);
		if (population.at(i)->i_get_fitness() > pcBestIndividual->i_get_fitness())
			pcBestIndividual = population.at(i);
	}
	return pcBestIndividual;
}

CIndividual* CGeneticAlgorithm::pc_select_parent(std::vector<CIndividual*>& population) {
	CIndividual* pcParentOpt1 = population.at(rand() % i_pop_size);
	CIndividual* pcParentOpt2 = population.at(rand() % i_pop_size);;
	while (pcParentOpt2 == pcParentOpt1) {
		pcParentOpt2 = population.at(rand() % i_pop_size);
	}
	return (pcParentOpt1->i_get_fitness() >= pcParentOpt2->i_get_fitness()) ? pcParentOpt1 : pcParentOpt2;
}

std::vector<CIndividual*> CGeneticAlgorithm::pc_cross_population(std::vector<CIndividual*>& prevPopulation) {
	std::vector<CIndividual*> cNewPopulation;
	while (cNewPopulation.size() < i_pop_size) {
		CIndividual* pcFirstParent = pc_select_parent(prevPopulation);
		CIndividual* pcSecondParent = pc_select_parent(prevPopulation);

		if (f_cross_prob > ((double)rand() / (RAND_MAX))) {
			std::vector<CIndividual*> cChildren = pcFirstParent->c_cross_individuals(pcSecondParent);
			cNewPopulation.push_back(cChildren.at(0));
			cNewPopulation.push_back(cChildren.at(1));
		}
		else {
			cNewPopulation.push_back(new CIndividual(*pcFirstParent));
			cNewPopulation.push_back(new CIndividual(*pcSecondParent));
		}
	}

	i_number_of_populations++;
	return cNewPopulation;
}

void CGeneticAlgorithm::v_mutate_population(std::vector<CIndividual*>& population) {
	for (int i = 0; i < population.size(); i++) {
		population.at(i)->v_mutate(f_mut_prob);
	}
}

void CGeneticAlgorithm::v_solve_problem(CKnapsackProblem* knapsackProblem) {
	std::vector<CIndividual*> cCurrentPopulation = c_generate_population(knapsackProblem->i_get_size());
	steady_clock::time_point cStart = high_resolution_clock::now();
	while ((duration_cast<milliseconds>(high_resolution_clock::now()- cStart)).count() < i_solving_time) {
		CIndividual* pcBestInPopulation = pc_get_individuals_fitness(cCurrentPopulation, knapsackProblem);
		if (pcBestInPopulation->i_get_fitness() > i_best_solution_fitness) {
			delete pc_best_solution;
			pc_best_solution = new CIndividual(*pcBestInPopulation);
			i_best_solution_fitness = pc_best_solution->i_get_fitness();
		}
			
		std::vector<CIndividual*> cNewPopulation = pc_cross_population(cCurrentPopulation);
		for (int i = 0; i < i_pop_size; i++) {
			delete cCurrentPopulation.at(i);
		}
		cCurrentPopulation = cNewPopulation;

		v_mutate_population(cCurrentPopulation);
	}
	b_print_record_to_file(RECORDS_FILE);
}

bool CGeneticAlgorithm::b_print_record_to_file(std::string filePath) {
	std::ofstream cFileStream(filePath, std::ios::app);
	std::string sNextLine;

	if (cFileStream.is_open()) {
		time_t cTime = time(NULL);

		cFileStream << ctime(&cTime);
		cFileStream << "Seed: " << ui_seed << ", Population size: " << i_pop_size << ", Crossing Probability: " << f_cross_prob << ", Mutation Probability: " << f_mut_prob << std::endl;
		cFileStream << "Solving time: " << i_solving_time << "ms, Best solution: " << pc_best_solution->s_get_genotype_string() << ", Best solution fitness: " << i_best_solution_fitness << std::endl << std::endl;

		cFileStream.close();
		return true;
	}
	else return false;
}