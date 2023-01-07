#include <vector>

template <typename T> class CTreeDynamicT;

template <typename T>
class CNodeDynamicT
{
public:
	CNodeDynamicT();
	~CNodeDynamicT();
	void vSetValue(T tNewVal);
	int iGetChildrenNumber();
	void vAddNewChild();
	CNodeDynamicT* pcGetChild(int iChildOffset);
	void vPrint();
	void vPrintAllBelow();
	void vPrintUp();
	int iCount(T tVal);
	friend class CTreeDynamicT<T>;
private:
	CNodeDynamicT** pc_tree_root;
	std::vector<CNodeDynamicT*> v_children;
	CNodeDynamicT* pc_parent_node;
	T t_val;
};

template <typename T>
class CTreeDynamicT
{
public:
	CTreeDynamicT();
	~CTreeDynamicT();
	CNodeDynamicT<T>* pcGetRoot();
	void vPrintTree();
	bool bMoveSubtree(CNodeDynamicT<T>* pcParentNode, CNodeDynamicT<T>* pcNewChildNode);
	int iCount(T tVal);
private:
	CNodeDynamicT<T>* pc_root;
};

//----------------------------------CNodeDynamicT---------------------------------

template <typename T>
CNodeDynamicT<T>::CNodeDynamicT() {
	t_val = T();
	pc_parent_node = NULL;
	pc_tree_root = NULL;
}

template <>
CNodeDynamicT<std::string>::CNodeDynamicT() {
	t_val = "empty";
	pc_parent_node = NULL;
	pc_tree_root = NULL;
}

template <typename T>
CNodeDynamicT<T>::~CNodeDynamicT() {
	for (int i = 0; i < v_children.size(); i++) {
		delete v_children[i];
	}
	std::vector<CNodeDynamicT*>().swap(v_children);
}

template <typename T>
void CNodeDynamicT<T>::vSetValue(T tNewVal) {
	t_val = tNewVal;
}

template <typename T>
int CNodeDynamicT<T>::iGetChildrenNumber() {
	return v_children.size();
}

template <typename T>
void CNodeDynamicT<T>::vAddNewChild() {
	v_children.resize(v_children.size() + 1);
	CNodeDynamicT* newChild = new CNodeDynamicT();
	newChild->pc_parent_node = this;
	newChild->pc_tree_root = this->pc_tree_root;
	v_children[v_children.size() - 1] = newChild;
}

template <typename N>
CNodeDynamicT<N>* CNodeDynamicT<N>::pcGetChild(int iChildOffset) {
	if (iChildOffset < 0 || iChildOffset > v_children.size())
		return NULL;
	return v_children[iChildOffset];
}

template <typename T>
void CNodeDynamicT<T>::vPrint() {
	std::cout << " " << t_val;
}

template <typename T>
void CNodeDynamicT< T>::vPrintAllBelow() {
	vPrint();
	for (int i = 0; i < v_children.size(); i++)
		v_children[i]->vPrintAllBelow();
}

template <typename T>
void CNodeDynamicT<T>::vPrintUp() {
	vPrint();
	if (pc_parent_node != NULL)
		pc_parent_node->vPrintUp();
}

template <typename T>
int CNodeDynamicT<T>::iCount(T tVal) {
	int result = (t_val == tVal ? 1 : 0);
	for (int i = 0; i < v_children.size(); i++)
		result += v_children[i]->iCount(tVal);
	return result;
}

//-------------------------CTreeDynamicT---------------------------

template <typename T>
CTreeDynamicT<T>::CTreeDynamicT() {
	pc_root = new CNodeDynamicT<T>();
	pc_root->pc_tree_root = &pc_root;
}

template <typename T>
CTreeDynamicT<T>::~CTreeDynamicT() {
	delete pc_root;
}

template <typename T>
CNodeDynamicT<T>* CTreeDynamicT<T>::pcGetRoot() {
	return pc_root;
}

template <typename T>
void CTreeDynamicT<T>::vPrintTree() {
	pc_root->vPrintAllBelow();
}

template <typename T>
bool CTreeDynamicT<T>::bMoveSubtree(CNodeDynamicT<T>* pcParentNode, CNodeDynamicT<T>* pcNewChildNode) {
	if (pcParentNode->pc_tree_root == pcNewChildNode->pc_tree_root)
		return false;

	//usuniecie starego node z v_children rodzica
	if (pcNewChildNode->pc_parent_node != NULL) {
		std::vector<CNodeDynamicT<T>*>& oldParentChildren = pcNewChildNode->pc_parent_node->v_children;
		typename std::vector<CNodeDynamicT<T>*>::iterator position = std::find(oldParentChildren.begin(), oldParentChildren.end(), pcNewChildNode);
		if (position != oldParentChildren.end()) oldParentChildren.erase(position);
	}
	else { //jesli przenosimy korzen, ustawiamy pc_root obiektu CTreeDynamic na NULL
		*(pcNewChildNode->pc_tree_root) = NULL;
	};

	//wpiecie starego node do nowego drzewa
	pcNewChildNode->pc_parent_node = pcParentNode;
	pcParentNode->v_children.push_back(pcNewChildNode);

	return true;
}

template <typename T>
int CTreeDynamicT<T>::iCount(T tVal) {
	return pc_root->iCount(tVal);
}

