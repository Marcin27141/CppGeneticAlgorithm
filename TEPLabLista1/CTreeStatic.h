#pragma once
#include <vector>

class CNodeStatic {
public:
	CNodeStatic();
	~CNodeStatic();
	bool operator==(const CNodeStatic& other);
	void vSetValue(int iNewVal);
	void vSetRootAndParentAllUnder(CNodeStatic* pcRoot, CNodeStatic* pcParent);
	int iGetChildrenNumber();
	void vAddNewChild();
	CNodeStatic* pcGetChild(int iChildOffset);
	void vPrint();
	void vPrintAllBelow();
	void vPrintUp();
	friend class CTreeStatic;
private:
	CNodeStatic* pc_tree_root;
	std::vector<CNodeStatic> v_children;
	CNodeStatic* pc_parent_node;
	int i_val;
};

class CTreeStatic
{
public:
	CTreeStatic();
	~CTreeStatic();
	CNodeStatic* pcGetRoot();
	void vPrintTree();
	bool bMoveSubtree(CNodeStatic* pcParentNode, CNodeStatic* pcNewChildNode);
private:
	CNodeStatic c_root;
};


