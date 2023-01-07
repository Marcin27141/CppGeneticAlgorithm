#pragma once
#include <string>
#include <iostream>

static const std::string S_DEFAULT_NAME = "default_name";
static const int I_TABLE_DEFAULT_LENGTH = 5;

class CTable {
public:
	CTable();
	CTable(std::string sName, int iTableLen);
	CTable(const CTable& pcOther);
	CTable(CTable&& pcOther);
	CTable* pcClone();
	~CTable();
	CTable operator=(const CTable& pcOther);
	CTable operator+(const CTable& pcOther);
	CTable operator++(int);
	void v_print();
	void v_set_value_at(int iOffset, int iNewVal);
	void v_set_name(std::string sName);
	bool b_set_new_size(int iTableLen);
	static void v_mod_tab(CTable* pcTab, int iNewSize);
	static void v_mod_tab(CTable cTab, int iNewSize);
private:
	void v_copy(const CTable& cOther);
	int* pi_table;
	int pi_table_length;
	std::string s_name;
};
