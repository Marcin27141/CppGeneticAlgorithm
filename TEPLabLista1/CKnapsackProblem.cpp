#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include <fstream>

CKnapsackProblem::CKnapsackProblem(std::vector<CKnapsackItem*> items, int capacity) {
	pc_items = items;
	i_size = items.size();
	i_capacity = capacity;
}

CKnapsackProblem* CKnapsackProblem::pc_load_knapsackProblem_from_file(std::string filePath) {
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
		catch (...) { //catch particular exceptions?
			return NULL;
		}

		//get knapsack items
		while (fileStream.good()) {
			std::getline(fileStream, nextLine);
			CKnapsackItem* nextItem = pc_get_knapsackItem_from_text_line(nextLine);
			if (nextItem == NULL) {
				for (int i = 0; i < items.size(); i++) {
					delete items.at(i);		//proper deallocation?
				};
				fileStream.close();
				return NULL;
			}
			else items.push_back(nextItem);
		}
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
	catch (...) { //catch particular exceptions?
		return NULL;
	}
	return new CKnapsackItem(weigth, value);
}

int CKnapsackProblem::i_get_individual_fitness(CIndividual* pcIndividual) {
	//other way round? (CIndividual calling CKnapsackProblem method)
	pcIndividual->v_calculate_fitness(this);
	return pcIndividual->i_get_fitness();
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
