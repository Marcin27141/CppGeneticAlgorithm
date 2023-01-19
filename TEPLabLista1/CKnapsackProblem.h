#pragma once
#include <vector>
#include "CIndividual.h"
#include <string>

static const std::string DELIMITER = "::";
static const int FILE_LOAD_SUCCESSFUL = 0;
static const int FILE_NOT_OPENED_ERROR = 1;
static const int FILE_FORMAT_ERROR = 2;

class CKnapsackItem {
public:
	CKnapsackItem(int weight, int value) { i_weigth = weight; i_value = value; }
	int i_get_weigth() { return i_weigth;  }
	int i_get_value() { return i_value; };
private:
	int i_weigth;
	int i_value;
};

class CKnapsackProblem {
public:
	CKnapsackProblem(std::vector<CKnapsackItem*> items, int capacity);
	CKnapsackProblem();
	~CKnapsackProblem();
	int i_load_knapsack_problem_from_file(std::string filePath);
	int i_get_individual_fitness(CIndividual* individual);
	int i_get_capacity();
	int i_get_size();
	std::vector<CKnapsackItem*> c_get_items();
private:
	int i_capacity;
	int i_size;
	std::vector<CKnapsackItem*> c_items;
	CKnapsackItem* pc_get_knapsackItem_from_text_line(std::string line);
};