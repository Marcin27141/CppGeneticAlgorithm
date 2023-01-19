#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>
int main()
{
	CKnapsackProblem* pcProblem = new CKnapsackProblem();
	int loadResult = pcProblem->i_load_knapsack_problem_from_file("CKnapsackProblem.txt");
	CGeneticAlgorithm pcAlgorithm;
	pcAlgorithm.v_set_solving_time(15);

	if (loadResult == FILE_LOAD_SUCCESSFUL) {
		pcAlgorithm.v_solve_problem(pcProblem);

		CIndividual* bestIndividual = pcAlgorithm.pc_get_best_solution();
		std::cout << bestIndividual->s_get_genotype_string() << std::endl;
	}
}

