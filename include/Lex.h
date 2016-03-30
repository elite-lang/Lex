/*
* @Author: sxf
* @Date:   2014-10-02 20:30:46
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-29 20:45:10
*/


#ifndef LEX_H
#define LEX_H

#include "LexInterface.h"
#include <vector>
#include <iostream>

using namespace std;

class RuleManager;
class DFA;
class DFACore;
class EquivalenceClass;

/**
 * @brief Lex is the main controller for the system
 */
class Lex : public LexInterface
{
public:
	Lex();
	~Lex();

	/// @brief get the next token ,if it is done ,will return NULL
	/// 	   it may throw exception, please try and catch it
    virtual Token* Read();

	/// @brief initialize the Lex system, must be called before Read Token, it can also set the pData
	virtual void Init(const char* pData = NULL);

	/// @brief read the config, you need to call it manually before init system, it will find the lex.cfg at the ./ path
	bool ReadConfig(const char* path = NULL);

	/// @brief add a new Lex rule
	int AddRule(const char* pName, const char* pattern); // return the rule's id

	/// @brief find the rule, will return the id of it.
	int FindRule(const char* pName);

	/// @brief  find the rule name
    virtual const char* getRule(int id);

    /// @brief get the rules sum
    virtual int getRuleSize();

    /// @brief init the main DFA core
    void InitCore();

	// ============================================
	// getter and setter
	// ============================================
	const char* getData();
	virtual void setData(const char* pData);
	DFA* getMainDFA();
private:

	/// @brief when you change the Rule, you should run it manually
	DFA* combineAllDFA();
	int testin(vector< int > newvec, vector< vector< int > > statelist);
	bool testequal(vector< int > , vector< int > );
    void addStopState(vector<int>&,int);
    void printvec(vector<int> v);

	// ============================================
	// member variable
	// ============================================

	/// Main dfa for all dfa combine to one
	DFA* mainDFA;

	/// the core of main DFA
    DFACore* core;

    /// the Equivalence Class 等价类表
    EquivalenceClass* pEClass;
	const char* pData = NULL; //all the data need to be splited

	/// pointer for the data, it's always point to the next char need to be scan.
	int pointer = 0;

	/// used to manage the rules
	RuleManager* ruleManager;
	//if the class is declared before defined, use it must be a pointer.
	//because the complier didn't know how much memory it need to allocated.

};

#endif //LEX_H
