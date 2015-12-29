
#ifndef DFA_H
#define DFA_H

#include "Regex.h"
#include <list>
using namespace std;


/// @brief DFA类是一个基本的DFA自动机类，支持从正则式创建、
/// @details 从0状态开始，0为初始状态
class DFA
{
public:
	DFA();
	~DFA();

	/// @brief it will build a DFA from the regex grammer tree
	void Init(Regex* re);

    /// @brief build the DFA
    void CreateDFA();

	/// @brief it's used for debug
	void print_func();

	// ========== State Map =========
	
	/// @brief used to get the next state
	int nextState(int s, echar_t a);
	
	/// @brief add a new edge
	void addEdge(int s, int obj, echar_t a);

    /// @brief is the stop state, 返回对应的token id
    int isStopState(int s);

	// === setter and getter ===

	void setEClass(EquivalenceClass* pEClass);
	EquivalenceClass* getEClass();
	int getStateSum();  // 得到总状态数，从0状态开始，故为最大状态号+1

    void setStopState(int s,int t) {
        stopState.insert(make_pair(s,t));
    }

	// ===== for debug ======
	/// @brief 打印DFA状态图
	void print_StateMap();
private:
	/// @brief calculate the pos;
	void dfs(node*);
	void cal_first_and_last();
	void cal_follow();


	vector<node*> node_vec;
	vector<node_func*> node_function;

	set<node*> GetNextSet(set<node*> &setNode, CharSet p);
	bool IsNodeSetInList(set<node*> &setNodeNext, int &nIdx);
	bool IsContainAcceptingState(set<node*> &setNode);
	// bool Check(const echar_t* data);
	vector<set<node*>> listSet;
	
	EquivalenceClass* pEClass;
	
    Regex* re;

    map<int,int> stopState;
public:
	int Top;
	
	vector<echar_t>	m_default;
	vector<int>	m_base;
	vector<int>	m_next;
	vector<int>	m_check;

// 	int state_base; // 表示状态初始状态的开始标号 已弃用
// 	void setState_base(int _b) { state_base = _b; }
// 	int getState_base() { return state_base; }
	
};

#endif // DFA_H
