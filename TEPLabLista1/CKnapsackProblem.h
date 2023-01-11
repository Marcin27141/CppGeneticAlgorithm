#pragma once
#include <vector>
#include "CIndividual.h"

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
	CKnapsackProblem(std::vector<CKnapsackItem*>, int capacity);
	int i_get_individual_fitness(CIndividual* pcIndividual);
	int i_get_capacity();
	int i_get_size();
	std::vector<CKnapsackItem*> pc_get_items();
private:
	int i_capacity;
	int i_size;
	std::vector<CKnapsackItem*> pc_items;
};