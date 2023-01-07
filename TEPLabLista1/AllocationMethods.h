#pragma once

static const int I_DEFAULT_TABLE_VALUE = 34;

//zadanie 1
void v_show_table(int* pi_table, int iSize);

void v_alloc_table_fill_34(int iSize);

//zadanie 2
bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY);

void v_fill_two_dimenstional_array(int*** piTable, int iSizeX, int iSizeY);

void v_show_two_dimensional_table(int** piTable, int iSizeX, int iSizeY);

//zadanie 3
bool b_dealloc_table_2_dim(int** piTable, int iSizeX, int iSizeY);
