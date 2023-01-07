#include "CTab.h"
#include <iostream>

CTab::CTab()
{
	pi_tab = new int[I_DEF_TAB_SIZE];
	i_size = I_DEF_TAB_SIZE;
}

CTab::CTab(const CTab& cOther)
{
	v_copy(cOther);
}

CTab::CTab(CTab&& cOther)
{
	pi_tab = cOther.pi_tab;
	i_size = cOther.i_size;
	cOther.pi_tab = NULL;
}

CTab::~CTab()
{
	if (pi_tab != NULL) delete pi_tab;
}

CTab CTab::operator=(const CTab& cOther)
{
	if (pi_tab != NULL) delete pi_tab;
	v_copy(cOther);
	return(*this);
}

bool CTab::bSetSize(int iNewSize) {
	if (iNewSize < 0) return false;
	if (iNewSize > i_size)
		pi_tab = new int[iNewSize];
	i_size = iNewSize;
	return true;
}

int CTab::iGetSize() {
	return(i_size);
}

void CTab::v_copy(const CTab& cOther)
{
	pi_tab = new int[cOther.i_size];
	i_size = cOther.i_size;
	for (int ii = 0; ii < cOther.i_size; ii++)
		pi_tab[ii] = cOther.pi_tab[ii];
}