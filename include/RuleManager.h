/* 
* @Author: sxf
* @Date:   2014-10-02 23:31:33
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-29 20:46:26
*/

#include <string>
#include <vector>
#include <map>
#include "EquivalenceClass.h"
#include "DFA.h"
#include "DFACore.h"
#include "estring.h"

#ifndef RULEMANAGER_H
#define RULEMANAGER_H

/**
 * @brief 一条词法规则
 * @details 描述词法规则的结构体，含有名字、对应的正则式，及由它生成的DFA
 */
struct Rule{
	Rule() {}
	Rule(const std::string& _name, const estring& _pattern, DFA* _dfa) {
		name = _name; pattern = _pattern; dfa = _dfa;
	}
	void setData(const std::string& _name, const estring& _pattern, DFA* _dfa) {
		name = _name; pattern = _pattern; dfa = _dfa;
	}
	std::string name;
	estring pattern;
	DFA* dfa;
	bool operator== (const std::string& obj){
		return name==obj;
	}
};


/****
* It's a manager for rules and regex.
****/
class RuleManager
{
public:
	RuleManager();
	~RuleManager();
	
	// add a new Lex rule
	int AddRule(const char*, const char*); // return the rule's id

	// find the rule, will return the id of it.
	int FindRule(const char*);
	

	// ====setter and getter =============
    int getRuleSize() { return ruleList.size(); }
    Rule& getRule(int id) { return ruleList.at(id); }
    EquivalenceClass* getEClass() { return pEClass; }
    const std::vector<Rule>& getRuleList() { return ruleList; }
private:
	std::vector<Rule> ruleList;
	EquivalenceClass* pEClass;
	
	/*
	// add a new Lex rule
	int AddRule(std::wstring pName, std::wstring pattern); // return the rule's id

	// delete a Lex rule
	bool DeleteRule(std::wstring pName);
	bool DeleteRule(int id); //also can use the id to delete it.

	// change a Lex rule
	bool ChangeRule(std::wstring pName, std::wstring pattern);
	bool ChangeRule(int id,std::wstring pattern);

	
	*/
};

#endif //RULEMANAGER_H
