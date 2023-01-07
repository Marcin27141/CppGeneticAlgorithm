#include "CTreeDynamic.h"
#include <iostream>
#include <algorithm>

//------------------------------------CNodeDynamic---------------------------------------------

CNodeDynamic::CNodeDynamic() {
	i_val = 0;
	pc_parent_node = NULL;
	pc_tree_root = NULL;
}

CNodeDynamic::~CNodeDynamic() {
	for (int i = 0; i < v_children.size(); i++) {
		delete v_children[i];
	}
	std::vector<CNodeDynamic*>().swap(v_children);
}

void CNodeDynamic::vSetValue(int iNewVal) {
	i_val = iNewVal;
}

int CNodeDynamic::iGetChildrenNumber() {
	return v_children.size();
}

void CNodeDynamic::vAddNewChild() {
	v_children.resize(v_children.size() + 1);
	CNodeDynamic* newChild = new CNodeDynamic();
	newChild->pc_parent_node = this;
	newChild->pc_tree_root = this->pc_tree_root;
	v_children[v_children.size() - 1] = newChild;
}

CNodeDynamic* CNodeDynamic::pcGetChild(int iChildOffset) {
	if (iChildOffset < 0 || iChildOffset > v_children.size())
		return NULL;
	return v_children[iChildOffset];
}

void CNodeDynamic::vPrint() {
	std::cout << " " << i_val;
}

void CNodeDynamic::vPrintAllBelow() {
	vPrint();
	for (int i = 0; i < v_children.size(); i++)
		v_children[i]->vPrintAllBelow();
}

void CNodeDynamic::vPrintUp() {
	vPrint();
	if (pc_parent_node != NULL)
		pc_parent_node->vPrintUp();
}

int CNodeDynamic::iCount(int iVal) {
	int result = (i_val == iVal ? 1 : 0);
	for (int i = 0; i < v_children.size(); i++)
		result += v_children[i]->iCount(iVal);
	return result;
}

//-------------------------------CTreeDynamic---------------------------------------------

CTreeDynamic::CTreeDynamic() {
	pc_root = new CNodeDynamic();
	pc_root->pc_tree_root = &pc_root;
}

CTreeDynamic::~CTreeDynamic() {
	delete pc_root;
}

CNodeDynamic* CTreeDynamic::pcGetRoot() {
	return pc_root;
}

void CTreeDynamic::vPrintTree() {
	pc_root->vPrintAllBelow();
}

bool CTreeDynamic::bMoveSubtree(CNodeDynamic* pcParentNode, CNodeDynamic* pcNewChildNode) {
	if (pcParentNode->pc_tree_root == pcNewChildNode->pc_tree_root)
		return false;

	//usuniecie starego node z v_children rodzica
	if (pcNewChildNode->pc_parent_node != NULL) {
		std::vector<CNodeDynamic*>& oldParentChildren = pcNewChildNode->pc_parent_node->v_children;
		std::vector<CNodeDynamic*>::iterator position = std::find(oldParentChildren.begin(), oldParentChildren.end(), pcNewChildNode);
		if (position != oldParentChildren.end()) oldParentChildren.erase(position);
	}
	else { //jesli przenosimy korzen, ustawiamy pc_root obiektu CTreeDynamic na NULL
		*(pcNewChildNode->pc_tree_root) = NULL;
	}

	//wpiecie starego node do nowego drzewa
	pcNewChildNode->pc_parent_node = pcParentNode;
	pcParentNode->v_children.push_back(pcNewChildNode);

	return true;
}

int CTreeDynamic::iCount(int iVal) {
	return pc_root->iCount(iVal);
}