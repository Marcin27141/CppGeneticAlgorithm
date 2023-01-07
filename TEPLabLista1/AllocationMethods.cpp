#include <string>
#include <iostream>
#include "AllocationMethods.h"
using namespace std;

//zadanie 1
void v_show_table(int* pi_table, int iSize) {
    if (iSize >= 0) {
        for (int i = 0; i < iSize; i++)
            cout << pi_table[i] << endl;
    }
}

void v_alloc_table_fill_34(int iSize) {
    if (iSize >= 0) {
        int* pi_table = new int[iSize];
        for (int i = 0; i < iSize; i++)
            pi_table[i] = I_DEFAULT_TABLE_VALUE;
        v_show_table(pi_table, iSize);
        delete []pi_table;
    }    
}

//zadanie 2
bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0)
        return false;
    *piTable = new int* [iSizeX];
    for (int i = 0; i < iSizeX; i++)
        (*piTable)[i] = new int[iSizeY];
    return true;
}

void v_fill_two_dimenstional_array(int*** piTable, int iSizeX, int iSizeY) {
    if (iSizeX > 0 && iSizeY > 0) {
        for (int i = 0; i < iSizeX; i++)
            for (int j = 0; j < iSizeY; j++)
                (*piTable)[i][j] = I_DEFAULT_TABLE_VALUE;
    }
}

void v_show_two_dimensional_table(int** piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0) return;
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++)
            cout << piTable[i][j] << " ";
        cout << endl;
    }
}

//zadanie 3
bool b_dealloc_table_2_dim(int** piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0)
        return false;
    for (int i = 0; i < iSizeX; i++)
        delete []piTable[i];
    delete []piTable;
    return true;
}

//modyfikacja
bool b_alloc(int*** piTable, int iSize) {
    if (iSize < 0)
        return false;
    *piTable = new int* [iSize];
    for (int i = 0; i < iSize; i++)
        (*piTable)[i] = new int[i + 1];
    return true;
}