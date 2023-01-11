#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>
int main()
{
	CKnapsackProblem *pcProblem = CKnapsackProblem::pc_load_knapsackProblem_from_file("CKnapsackProblem.txt");
	CGeneticAlgorithm pcAlgorithm;
	pcAlgorithm.v_solve_problem(pcProblem);

	std::vector<bool> bestSolution = pcAlgorithm.pc_get_best_solution();
	for (int i = 0; i < bestSolution.size(); i++)
		std::cout << bestSolution.at(i);
}

