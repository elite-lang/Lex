
#include "RuleManager.h"
#include "DebugJson.h"
#include <algorithm>
#include <exception>
#include <queue>
#include <cstring>


RuleManager::RuleManager() {
	pEClass = new EquivalenceClass();
	debug_json = new DebugJson();
}

RuleManager::~RuleManager() {
	delete pEClass;
	delete debug_json;
}

int RuleManager::AddRule(const char* pName, const char* pPattern)
{
	string name(pName);
	estring pattern(pPattern);
	int id = FindRule(pName);
	if (id != -1) { // 已经找到了已有的Rule，更新其
		Rule& r = ruleList[id];
		delete r.dfa;
		r.setData(name, pattern, new DFA());
		r.dfa->setEClass(pEClass);
		r.dfa->Init(new Regex(pattern, pEClass));
		return id;
	}
	// 新建Rule，构建DFA
	Rule r;
	r.setData(name, pattern, new DFA());
	r.dfa->setEClass(pEClass);
	r.dfa->Init(new Regex(pattern, pEClass));

	if (name == string("ignore"))
		ruleList.insert(ruleList.begin(),r);
	else
		ruleList.push_back(r);

	debug_json->addRegex(pName, pPattern);
	return ruleList.size();
}

int RuleManager::FindRule(const char* pName){
	std::string name(pName);
	auto result = std::find(ruleList.begin(), ruleList.end(), name);
	if (result == ruleList.end()) return -1;
	return (int)(result - ruleList.begin());
}


// ====setter and getter =============


/*
int RuleManager::AddRule(std::wstring pName, std::wstring pattern){
	int size = ruleList.size();
// 	ruleList.push_back(pName);
	return size;
}


bool RuleManager::DeleteRule(std::wstring pName){
	auto result = std::find(ruleList.begin(), ruleList.end(), pName);
	if (result == ruleList.end()) return false;
	ruleList.erase(result);
	return true;
}

bool RuleManager::DeleteRule(int id){
	try {
		ruleList.at(id);
	}
	catch (std::exception e) {
		return false;
	}
	ruleList.erase(ruleList.begin()+id);
	return true;
}


bool RuleManager::ChangeRule(std::wstring pName, std::wstring pattern){
	int k = FindRule(pName);
	if (k == -1) return false;
	ruleList[k].pattern = pattern;
	return true;
}

bool RuleManager::ChangeRule(int id, std::wstring pattern){
	try {
		ruleList.at(id);
	}
	catch (std::exception e) {
		return false;
	}
	ruleList[id].pattern = pattern;
	return true;
}



*/
