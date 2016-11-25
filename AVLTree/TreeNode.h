#ifndef TREENODE_H
#define TREENODE_H
template<typename ElemType> class AVLTree;
template<typename ElemType>
class TreeNode {
	friend class AVLTree<ElemType>;
	private:
		int height;
        ElemType value;
        TreeNode<ElemType> *left;
        TreeNode<ElemType> *right;
        TreeNode(const ElemType &val) : height(1), value(val), left(nullptr), right(nullptr) { }
};
#endif