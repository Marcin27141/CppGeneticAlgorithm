#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>
int main()
{
	CKnapsackProblem *pcProblem = CKnapsackProblem::pc_load_knapsack_problem_from_file("CKnapsackProblem.txt");
	CGeneticAlgorithm pcAlgorithm;
	pcAlgorithm.v_solve_problem(pcProblem);
	pcAlgorithm.v_set_solving_time(15);

	CIndividual* bestIndividual = pcAlgorithm.pc_get_best_solution();
	std::cout << bestIndividual->s_get_genotype_string() << std::endl;
}

