#include "CTable.h"
using namespace std;

CTable::CTable() {
	s_name = S_DEFAULT_NAME;
	pi_table_length = I_TABLE_DEFAULT_LENGTH;
	pi_table = new int[pi_table_length];
}

CTable::CTable(std::string sName, int iTableLen) {
	s_name = sName;
	if (!b_set_new_size(iTableLen)) {
		pi_table_length = I_TABLE_DEFAULT_LENGTH;
		pi_table = new int[pi_table_length];
	}
}

CTable::CTable(const CTable& pcOther) {
	s_name = pcOther.s_name + "_copy";
	pi_table_length = pcOther.pi_table_length;
	pi_table = new int[pi_table_length];
	*pi_table = *pcOther.pi_table;
	for (int i = 0; i < pi_table_length; i++)
		pi_table[i] = pcOther.pi_table[i];
}

CTable::CTable(CTable&& pcOther) {
	s_name = pcOther.s_name;
	pi_table_length = pcOther.pi_table_length;
	pi_table = pcOther.pi_table;
	pcOther.pi_table = NULL;
}

CTable* CTable::pcClone() {
	return new CTable(*this);
}

CTable::~CTable() {
	delete[]pi_table;
}

CTable CTable::operator=(const CTable& pcOther) {
	if (pi_table != NULL) delete pi_table;
	v_copy(pcOther);
	return(*this);
}

CTable CTable::operator+(const CTable& pcOther) {
	CTable pc_result;
	pc_result.s_name = s_name + "_concat_" + pcOther.s_name;
	pc_result.b_set_new_size(pi_table_length + pcOther.pi_table_length);
	int i = 0;
	for (; i < pi_table_length; i++)
		pc_result.pi_table[i] = pi_table[i];
	for (int j = 0; j < pcOther.pi_table_length; j++)
		pc_result.pi_table[i + j] = pcOther.pi_table[j];
	return (std::move(pc_result));
}

CTable CTable::operator++(int) {
	CTable temp(*this);
	b_set_new_size(pi_table_length + 1);
	for (int i = 0; i < pi_table_length - 1; i++)
		pi_table[i] = temp.pi_table[i];
	pi_table[pi_table_length - 1] = 0;
	return(*this);
}

void CTable::v_print() {
	for (int i = 0; i < pi_table_length; i++)
		std:cout << pi_table[i] << " ";
	std::cout << endl;
}

void CTable::v_set_name(std::string sName) {
	s_name = sName;
}

bool CTable::b_set_new_size(int iTableLen) {
	if (iTableLen < 0)
		return false;
	if (iTableLen > pi_table_length)
		pi_table = new int[iTableLen];
	pi_table_length = iTableLen;
	return true;
}

void CTable::v_set_value_at(int iOffset, int iNewVal) {
	if (iOffset >= 0 && iOffset < pi_table_length)
		pi_table[iOffset] = iNewVal;
}

void CTable::v_mod_tab(CTable* pcTab, int iNewSize) {
	if (iNewSize >= 0) {
		pcTab->pi_table_length = iNewSize;
		pcTab->pi_table = new int[iNewSize];
	}
}

void CTable::v_mod_tab(CTable cTab, int iNewSize) {
	if (iNewSize >= 0) {
		cTab.pi_table_length = iNewSize;
		cTab.pi_table = new int[iNewSize];
	}
}

void CTable::v_copy(const CTable& cOther)
{
	pi_table = new int[cOther.pi_table_length];
	s_name = cOther.s_name;
	pi_table_length = cOther.pi_table_length;
	for (int ii = 0; ii < cOther.pi_table_length; ii++)
		pi_table[ii] = cOther.pi_table[ii];
}