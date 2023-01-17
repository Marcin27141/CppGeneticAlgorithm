#pragma once
#include <vector>
#include "CIndividual.h"
#include <string>

static const std::string DELIMITER = "::";

class CKnapsackItem {
public:
	CKnapsackItem(int iWeight, int iValue) { i_weigth = iWeight; i_value = iValue; }
	int i_get_weigth() { return i_weigth;  }
	int i_get_value() { return i_value; };
private:
	int i_weigth;
	int i_value;
};

class CKnapsackProblem {
public:
	CKnapsackProblem(std::vector<CKnapsackItem*> items, int capacity);
	~CKnapsackProblem();
	static CKnapsackProblem* pc_load_knapsack_problem_from_file(std::string filePath);
	int i_get_individual_fitness(CIndividual* pcIndividual);
	int i_get_capacity();
	int i_get_size();
	std::vector<CKnapsackItem*> pc_get_items();
private:
	int i_capacity;
	int i_size;
	std::vector<CKnapsackItem*> pc_items;
	static CKnapsackItem* pc_get_knapsackItem_from_text_line(std::string line);
};