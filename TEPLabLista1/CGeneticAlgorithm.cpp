#include "CGeneticAlgorithm.h"
#include <random>
#include <time.h>

CGeneticAlgorithm::CGeneticAlgorithm(int popSize, float crossProb, float mutProb) {
	i_pop_size = popSize;
	f_cross_prob = crossProb;
	f_mut_prob = mutProb;

	pc_best_solution = std::vector<short>();
	i_best_solution_fitness = -1;
	i_number_of_populations = 0;
}

std::vector<short> CGeneticAlgorithm::pc_get_best_solution() {
	return pc_best_solution;
}

std::vector<CIndividual*> CGeneticAlgorithm::pc_generate_population(int iGenotypeSize) {
	std::vector<CIndividual*> pcPopulation(i_pop_size);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);

	for (int i = 0; i < i_pop_size; i++) {
		std::vector<short> genome(iGenotypeSize);
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

std::vector<CIndividual*> CGeneticAlgorithm::pc_cross_population(std::vector<CIndividual*> prevPopulation) {
	std::vector<CIndividual*> pcNewPopulation;
	srand(time(NULL));
	while (pcNewPopulation.size() < i_pop_size) {
		CIndividual* firstParentOpt1 = prevPopulation.at(rand() % i_pop_size);
		CIndividual* firstParentOpt2 = prevPopulation.at(rand() % i_pop_size); //TODO can't be the same as first parent option 1
		CIndividual* firstParent = (firstParentOpt1->i_get_fitness() >= firstParentOpt2->i_get_fitness()) ? firstParentOpt1 : firstParentOpt2;
		//code duplication
		CIndividual* secondParentOpt1 = prevPopulation.at(rand() % i_pop_size);
		CIndividual* secondParentOpt2 = prevPopulation.at(rand() % i_pop_size); 
		CIndividual* secondParent = (secondParentOpt1->i_get_fitness() >= secondParentOpt2->i_get_fitness()) ? secondParentOpt1 : secondParentOpt2;
		//code duplication

		if (f_cross_prob > ((double)rand() / (RAND_MAX))) {
			std::vector<CIndividual*> children = firstParent->pc_cross_individuals(secondParent);
			pcNewPopulation.push_back(children.at(0)); //safe?
			pcNewPopulation.push_back(children.at(1)); //safe?
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
	srand(time(NULL));
	for (int i = 0; i < population.size(); i++) {
		std::vector<short>* currentGenotype = population.at(i)->pc_get_genotype();
		for (int j = 0; j < currentGenotype->size(); j++) {
			if (f_mut_prob > ((double)rand() / (RAND_MAX)))
				currentGenotype->at(j) = currentGenotype->at(j) == 0 ? 1 : 0;
		}
	}
}

void CGeneticAlgorithm::v_solve_problem(CKnapsackProblem* pcProblem) {
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