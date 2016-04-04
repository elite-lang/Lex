#ifndef REGEX_H
#define REGEX_H

#include <stack>
#include <vector>
#include <set>
#include "CharSet.h"
#include "EquivalenceClass.h"

struct node;

/**
 * @brief lex正则表达式求自动机的中间变量
 */
struct node_func
{
	int num;
	bool nullable;
	std::set<node*> firstpos;
	std::set<node*> lastpos;
	std::set<node*> followpos;
};

/**
 * @brief lex中正则表达式的节点结构体
 */
struct node
{
	int type;
	node* left;
	node* right;
	CharSet* data;
	std::set<unsigned short> class_set;
	node_func* func;
	node(int _type, node* _left, node* _right, CharSet* pSet){
		this->type = _type;
		this->left = _left;
		this->right = _right;
		this->data = pSet;
	}
	~node()
	{
		delete data;
		delete func;
		delete left;
		delete right;
	}
};

const char node_type[][3] = {
	{0,0,0},	// id=0 leaf node
	{1,2,2},	// id=1 cat, it will combine two nodes
	{'|',2,1}, 	// id=2 or
	{'*',1,3},	// id=3 0 or many
	{'+',1,3},	// id=4
	{'?',1,3},	// id=5
	{'/',2,1}	// id=6 look forward
//	{0,2}		// id=7 it used to make the left node repeat right node times
};


/**
 * @brief 正则表达式类
 */
class Regex
{
public:
	Regex();
	~Regex();

	// it's same as init method
	Regex(const estring& pattern, EquivalenceClass* pEClass);

	bool init(const estring& pattern, EquivalenceClass* pEClass = NULL);

    node* getRoot() { return root; }

	// === setter and getter ===

	void setEClass(EquivalenceClass* pEClass);
	EquivalenceClass* getEClass();
    std::string getPattern() { return pattern.to_utf8(); }

private:

	void run(echar_t c);
	CharSet* makeEscape();
	void doCharSet(CharSet*);
	void doOperater(echar_t);
	void operate();
	void putOperater(echar_t c);

	void push(echar_t c);
	void pop();
	// ===================
	// member variable
	// ===================

	estring pattern;

	int pointer = 0;

	// it's the root of the tree
	node* root; // for test ,so put it in public

	std::stack<echar_t> operater_stack;
	std::stack<node*> obj_stack;

	EquivalenceClass* pEClass;

	estring tempSet;
	estring tempLeftInt;
	estring tempRightInt;

	bool isEnd = false;
};



#endif // REGEX_H
