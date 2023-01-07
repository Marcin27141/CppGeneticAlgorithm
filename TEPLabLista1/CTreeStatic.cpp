#include "CTreeStatic.h"
#include "cstddef"
#include <algorithm>
#include <iostream>

//--------------------------------CNodeStatic--------------------------------------

CNodeStatic::CNodeStatic() {
	i_val = 0;
	pc_parent_node = NULL;
	pc_tree_root = NULL;
}

CNodeStatic::~CNodeStatic() {
	std::vector<CNodeStatic>().swap(v_children);
}

bool CNodeStatic::operator==(const CNodeStatic& other) {
	return this == &other;
}

void CNodeStatic::vSetValue(int iNewVal) {
	i_val = iNewVal;
}

void CNodeStatic::vSetRootAndParentAllUnder(CNodeStatic* pcRoot, CNodeStatic* pcParent) {
	pc_tree_root = pcRoot;
	pc_parent_node = pcParent;
	for (int i = 0; i < v_children.size(); i++)
		v_children[i].vSetRootAndParentAllUnder(pcRoot, this);
}

int CNodeStatic::iGetChildrenNumber() {
	return v_children.size();
}

void CNodeStatic::vAddNewChild() {
	v_children.resize(v_children.size() + 1);
	v_children[v_children.size() - 1].pc_parent_node = this;
	v_children[v_children.size() - 1].pc_tree_root = this->pc_tree_root;
}

CNodeStatic* CNodeStatic::pcGetChild(int iChildOffset) {
	if (iChildOffset < 0 || iChildOffset > v_children.size())
		return NULL;
	return &(v_children[iChildOffset]);
}

void CNodeStatic::vPrint() {
	std::cout << " " << i_val;
}

void CNodeStatic::vPrintAllBelow() {
	vPrint();
	for (int i = 0; i < v_children.size(); i++)
		v_children[i].vPrintAllBelow();
}

void CNodeStatic::vPrintUp() {
	vPrint();
	if (pc_parent_node != NULL)
		pc_parent_node->vPrintUp();
}

//----------------------CTreeStatic---------------------------

CTreeStatic::CTreeStatic() {
	c_root.pc_tree_root = &c_root;
}

CTreeStatic::~CTreeStatic() {

}

CNodeStatic* CTreeStatic::pcGetRoot() {
	return &c_root;
}

void CTreeStatic::vPrintTree() {
	c_root.vPrintAllBelow();
}

bool CTreeStatic::bMoveSubtree(CNodeStatic* pcParentNode, CNodeStatic* pcNewChildNode) {
	if (pcParentNode->pc_tree_root == pcNewChildNode->pc_tree_root)
		return false;
	CNodeStatic *pcNewChildOldParent = pcNewChildNode->pc_parent_node;
	
	//wpiecie starego node do nowego drzewa
	pcParentNode->v_children.push_back(*pcNewChildNode);
	pcParentNode->v_children.back().vSetRootAndParentAllUnder(pcParentNode->pc_tree_root, pcParentNode);


	//usuniecie starego node z v_children rodzica
	if (pcNewChildOldParent != NULL) {
		std::vector<CNodeStatic>& oldParentChildren = pcNewChildOldParent->v_children;
		std::vector<CNodeStatic>::iterator position = std::find(oldParentChildren.begin(), oldParentChildren.end(), *pcNewChildNode);
		if (position != oldParentChildren.end()) oldParentChildren.erase(position);
	}
	else { //jesli przenosimy korzen, ustawiamy c_root obiektu CTreeStatic na pusty wezel
		CNodeStatic *root = pcNewChildNode->pc_tree_root;
			std::vector<CNodeStatic>().swap(root->v_children);
			root->i_val = 0;
			root->pc_parent_node = NULL;
		}

	return true;
}