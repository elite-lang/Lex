#ifndef DFACORE_H
#define DFACORE_H
#include "DFA.h"
#include "Lex.h"
#include "EquivalenceClass.h"

class DFACore
{
public:
    DFACore() {}
    ~DFACore() { if (t != NULL) delete t; }
    
    DFACore(DFA* _dfa, EquivalenceClass* _pEClass) { 
        Init(_dfa, _pEClass); 
    }

    void Init(DFA* _dfa, EquivalenceClass* _pEClass) {
        dfa = _dfa; pEClass = _pEClass;
        point = 0; row_point =1; line_point = 0;
    }

    void setData(const char* pData) {
        data = pData;
        getNextLine(0);
    }

    Token* Read();

private:
    DFA* dfa;
    int state;
    estring tokendata; // 当前的token数据
    estring data; // 全文件数据
    std::string outdata;
    std::string nowline;
    int point, row_point, line_point; //处理位置指针
    Token* t = NULL; // 上一次的token
    EquivalenceClass* pEClass;
    void getNextLine(int point);
};

#endif // DFACORE_H
