#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>
int main()
{
	/*std::vector<int> values = { 60, 100, 120 };
	std::vector<int> weights = { 10, 20, 30 };*/
	std::vector<int> values = { 5, 1, 4, 3 };
	std::vector<int> weights = { 4, 1, 3, 2 };
	CKnapsackProblem* pcProblem = new CKnapsackProblem(values, weights, 5);

	CGeneticAlgorithm pcAlgorithm;
	pcAlgorithm.v_solve_problem(pcProblem);
	std::vector<bool> bestSolution = pcAlgorithm.pc_get_best_solution();
	for (int i = 0; i < bestSolution.size(); i++)
		std::cout << bestSolution.at(i);
}

