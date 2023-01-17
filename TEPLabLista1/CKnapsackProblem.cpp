#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include <fstream>

CKnapsackProblem::CKnapsackProblem(std::vector<CKnapsackItem*> items, int capacity) {
	pc_items = items;
	i_size = items.size();
	i_capacity = capacity;
}

CKnapsackProblem::~CKnapsackProblem() {
	for (int i = 0; i < i_size; i++) {
		delete pc_items[i];
	}
}

//file format:
// {capacity}
// {item1weigth}{delimiter}{item1value}
// {item2weigth}{delimiter}{item2value}
// ...
CKnapsackProblem* CKnapsackProblem::pc_load_knapsack_problem_from_file(std::string filePath) {
	int capacity;
	std::vector<CKnapsackItem*> items;

	std::ifstream fileStream(filePath);
	std::string nextLine;

	if (fileStream.is_open()) {
		
		//get capacity
		std::getline(fileStream, nextLine);
		try {
			capacity = std::stoi(nextLine);;
		}
		catch (...) {
			return NULL;
		}

		//get knapsack items
		while (fileStream.good()) {
			std::getline(fileStream, nextLine);
			CKnapsackItem* nextItem = pc_get_knapsackItem_from_text_line(nextLine);
			if (nextItem == NULL) {
				for (int i = 0; i < items.size(); i++) {
					delete items.at(i);
				};
				fileStream.close();
				return NULL;
			}
			else items.push_back(nextItem);
		}
	}
	else {
		return NULL;
	}

	return new CKnapsackProblem(items, capacity);
}

CKnapsackItem* CKnapsackProblem::pc_get_knapsackItem_from_text_line(std::string line) {
	int delimeterIndex = line.find(DELIMITER);
	if (delimeterIndex <= 0) return NULL;
	std::string weightStr = line.substr(0, delimeterIndex);
	std::string valueStr = line.substr(delimeterIndex + DELIMITER.length(), line.length());
	int weigth, value;
	try {
		weigth = std::stoi(weightStr);;
		value = std::stoi(valueStr);;
	}
	catch (...) {
		return NULL;
	}
	return new CKnapsackItem(weigth, value);
}

int CKnapsackProblem::i_get_individual_fitness(CIndividual* pcIndividual) {
	int fitness = 0;
	int weigth = 0;
	for (int i = 0; i < i_size; i++) {
		if (pcIndividual->pc_get_genotype()->at(i) == 1) {
			fitness += pc_items.at(i)->i_get_value();
			weigth += pc_items.at(i)->i_get_weigth();
		}
	}

	return (weigth > i_capacity) ? 0 : fitness;
}

int CKnapsackProblem::i_get_capacity() {
	return i_capacity;
}

int CKnapsackProblem::i_get_size() {
	return i_size;
}

std::vector<CKnapsackItem*> CKnapsackProblem::pc_get_items() {
	return pc_items;
}
