/* 
* @Author: sxf
* @Date:   2014-10-02 20:47:00
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-29 20:10:33
*/
#include "Lex.h"
#include <iostream>
#include <fstream>
#include "RuleManager.h"
using namespace std;

Lex::Lex() {
	ruleManager = new RuleManager();
}

Lex::~Lex() {
    delete ruleManager;
}

Token* Lex::Read() {
    return core->Read();
}

void Lex::Init(const char* pData){
    // init the lex system
    this->pEClass = ruleManager->getEClass();
    combineAllDFA();
    InitCore();
    if (pData != NULL) setData(pData);
}

int Lex::AddRule(const char* pName,const char* pattern){
	return ruleManager->AddRule(pName,pattern);
} 

int Lex::FindRule(const char* pName){
    return ruleManager->FindRule(pName);
}

const char* Lex::getData(){
	return this->pData;
}

void Lex::setData(const char* pData){
	this->pData = pData;
    core->setData(pData);
}

int Lex::getRuleSize() {
    return ruleManager->getRuleSize();
}

const char* Lex::getRule(int id) {
    const Rule& r = ruleManager->getRule(id);
    return r.name.c_str();
}

bool Lex::ReadConfig(const char* path) {
    fstream cfgFile;  
    cfgFile.open(path);//打开文件      
    if(!cfgFile.is_open())  
    {  
        printf("can not open cfg file!\n");
        return false;  
    }
    char tmp[1000];  
    while(!cfgFile.eof())//循环读取每一行  
    {  
        cfgFile.getline(tmp,1000);//每行读取前1000个字符，1000个应该足够了  
        std::string line(tmp);  
        size_t pos = line.find('=');//找到每行的“=”号位置，之前是key之后是value  
        if(pos==string::npos) return false;  
        std::string key = line.substr(0,pos);//取=号之前  
        std::string value = line.substr(pos + 1);
        // printf("%s = %s\n",key.c_str(), value.c_str());
        AddRule(key.c_str(), value.c_str());
    }  
    
    return true;  
}

void Lex::InitCore() {
    core = new DFACore();
    core->Init(mainDFA,pEClass);
}


DFA* Lex::combineAllDFA(){
    vector<int> states;
    vector<vector<int>> statelist;
    mainDFA = new DFA();
    for (auto& r : ruleManager->getRuleList()) {
        states.push_back(0);
        r.dfa->CreateDFA();
        // r.dfa->print_func();
        // r.dfa->print_StateMap();
    }
    statelist.push_back(states);
    addStopState(states,0);
    // printvec(states);
    mainDFA->Top = 0;
    int i = 0;
    while (i<statelist.size())
    {
        bool b = true;
        mainDFA->m_base.push_back(0);
        mainDFA->m_default.push_back(0);
        // 等价类是从1-n的
        for (int c = 1; c <= pEClass->getSum(); ++c)
        {
            vector<int>* newvec = new vector<int>();
            for (int j = 0; j< getRuleSize(); ++j)
            {
                Rule& r = ruleManager->getRule(j);
                DFA* dfa = r.dfa;
                int nowstate = statelist[i][j];
                int nextstate = -1;
                if (nowstate != -1)
                    nextstate = dfa->nextState(nowstate,c);
                newvec->push_back(nextstate);
            }
            // 第一次找到转移时对base数组进行计算赋值
            if (b) {
                b = false;
                mainDFA->m_base[i] = mainDFA->Top - c;
            }

            int p = testin(*newvec,statelist);
            if (p == -2) {
                statelist.push_back(*newvec);
                p = statelist.size()-1;
                addStopState(*newvec,p);
            } 
            mainDFA->addEdge(i,p,c);
            // printf("state: %d  next: %d char: %d  ", i, p, c);
            // printvec(*newvec);
        }
        ++i;
    }
    mainDFA->setEClass(this->pEClass);
    // mainDFA->print_StateMap();
    // this->pEClass->print();

    return mainDFA;
}

void Lex::addStopState(vector<int>& newvec,int p)
{
    for (int i = 0; i < newvec.size(); ++i) {
        if (newvec[i] != -1) {
            Rule& r = ruleManager->getRule(i);
            DFA* dfa = r.dfa;
            if (dfa->isStopState(newvec[i]) != -1) {
                mainDFA->setStopState(p,i);
            }
        }
    }
}

int Lex::testin(vector< int > newvec, vector< vector< int > > statelist){
    bool isError = true;
    for (auto p = newvec.begin(); p != newvec.end(); ++p) {
        if (*p != -1) isError = false;
    }
    if (isError) return -1;

    for (auto p = statelist.begin(); p != statelist.end(); ++p)
    {
        if (testequal(newvec, *p)) return p - statelist.begin();
    }
    return -2;
}

bool Lex::testequal(vector< int > a, vector< int > b) {
    if (a.size() != b.size()) return false;  // 其实是没必要的，输入保证其相等
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


void Lex::printvec(vector<int> v) {
    printf("allstate: ");
    for (auto p = v.begin(); p != v.end(); ++p) {
        printf("%d ",*p);
    }
    printf("\n");
}

DFA* Lex::getMainDFA(){
    return mainDFA;
}