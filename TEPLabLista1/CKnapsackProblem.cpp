#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include <fstream>

CKnapsackProblem::CKnapsackProblem(std::vector<CKnapsackItem*> items, int capacity) {
	c_items = items;
	i_size = items.size();
	i_capacity = capacity;
}

CKnapsackProblem::CKnapsackProblem() {
	i_size = -1;
	i_capacity = -1;
}

CKnapsackProblem::~CKnapsackProblem() {
	for (int i = 0; i < i_size; i++) {
		delete c_items[i];
	}
}

//file format:
// {capacity}
// {item1weigth}{delimiter}{item1value}
// {item2weigth}{delimiter}{item2value}
// ...

bool CKnapsackProblem::b_load_knapsack_problem_from_file(std::string filePath) {
	int iCapacity;
	std::vector<CKnapsackItem*> cItems;

	std::ifstream cFileStream(filePath);
	std::string sNextLine;

	if (cFileStream.is_open()) {
		
		//get capacity
		std::getline(cFileStream, sNextLine);
		try {
			iCapacity = std::stoi(sNextLine);;
		}
		catch (...) {
			return false;
		}

		//get knapsack items
		while (cFileStream.good()) {
			std::getline(cFileStream, sNextLine);
			CKnapsackItem* nextItem = pc_get_knapsackItem_from_text_line(sNextLine);
			if (nextItem == NULL) {
				for (int i = 0; i < cItems.size(); i++) {
					delete cItems.at(i);
				};
				cFileStream.close();
				return false;
			}
			else cItems.push_back(nextItem);
		}
	}
	else {
		return false;
	}

	this->c_items = cItems;
	this->i_size = c_items.size();
	this->i_capacity = iCapacity;
	return true;
}

CKnapsackItem* CKnapsackProblem::pc_get_knapsackItem_from_text_line(std::string line) {
	int iDelimeterIndex = line.find(DELIMITER);
	if (iDelimeterIndex <= 0) return NULL;
	std::string sWeightStr = line.substr(0, iDelimeterIndex);
	std::string sValueStr = line.substr(iDelimeterIndex + DELIMITER.length(), line.length());
	int iWeigth, iValue;
	try {
		iWeigth = std::stoi(sWeightStr);;
		iValue = std::stoi(sValueStr);;
	}
	catch (...) {
		return NULL;
	}
	return new CKnapsackItem(iWeigth, iValue);
}

int CKnapsackProblem::i_get_individual_fitness(CIndividual* individual) {
	int iFitness = 0;
	int iWeigth = 0;
	for (int i = 0; i < i_size; i++) {
		if (individual->pc_get_genotype()->at(i) == 1) {
			iFitness += c_items.at(i)->i_get_value();
			iWeigth += c_items.at(i)->i_get_weigth();
		}
	}

	return (iWeigth > i_capacity) ? 0 : iFitness;
}

int CKnapsackProblem::i_get_capacity() {
	return i_capacity;
}

int CKnapsackProblem::i_get_size() {
	return i_size;
}

std::vector<CKnapsackItem*> CKnapsackProblem::c_get_items() {
	return c_items;
}
