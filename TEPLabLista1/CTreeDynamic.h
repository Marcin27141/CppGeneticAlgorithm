#pragma once
#include <vector>

class CNodeDynamic
{
public:
	CNodeDynamic();
	~CNodeDynamic();
	void vSetValue(int iNewVal);
	int iGetChildrenNumber();
	void vAddNewChild();
	CNodeDynamic* pcGetChild(int iChildOffset);
	void vPrint();
	void vPrintAllBelow();
	void vPrintUp();
	int iCount(int iVal);
	friend class CTreeDynamic;
private:
	CNodeDynamic** pc_tree_root;
	std::vector<CNodeDynamic*> v_children;
	CNodeDynamic* pc_parent_node;
	int i_val;
};

class CTreeDynamic
{
public:
	CTreeDynamic();
	~CTreeDynamic();
	CNodeDynamic* pcGetRoot();
	void vPrintTree();
	bool bMoveSubtree(CNodeDynamic* pcParentNode, CNodeDynamic* pcNewChildNode);
	int iCount(int iVal);
private:
	CNodeDynamic* pc_root;
};