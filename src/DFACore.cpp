#include "DFACore.h"
#include "DebugJson.h"


void DFACore::getNextLine(int point) {
    int i = point;
    while(i < data.length()) {
        if (data[i] == '\n') break;
        ++i;
    }
    estring substr = data.substr(point, i-point);
    nowline.clear();
    nowline = substr.to_utf8();
}



void DFACore::Init(DFA* _dfa, EquivalenceClass* _pEClass) {
   dfa = _dfa; pEClass = _pEClass;
   point = 0; row_point =1; line_point = 0;
   if (DebugMsg::isDebug()) DebugJson::getInst().clear();
}

Token* DFACore::Read() {
    DebugJson& dj = DebugJson::getInst();
    state = 0;
    tokendata.clear();

    if (t != NULL) delete t;
    t = new Token();
    echar_t nowdata, lastdata;
	lastdata = 0;
    while (point < data.length()) {
        nowdata = data[point];


        // for each word ,may get it Equal Class
        echar_t c = pEClass->getClass(nowdata);

        // test the next state
        int nextstate = dfa->nextState(state, c);
        if (DebugMsg::isDebug()) dj.addLine(line_point, row_point, state, nowdata);

        // if the state is stopped and the next is fault, get the token
        if (nextstate == -1) {
            int p = dfa->isStopState(state);
            if (p != -1) {
                if (p == 0) {
                    state = 0;
                    tokendata.clear();
                    continue;
                } else {
                    outdata.clear();
                    outdata = tokendata.to_utf8();
                    t->type = p;
                    t->pToken = outdata.c_str();
                    t->row_num = row_point;
                    t->col_num = line_point;
                    t->debug_line = nowline.c_str();
                    state = 0;
                    if (DebugMsg::isDebug()) dj.addLine(line_point, row_point, state, nowdata);
                    return t;
                }
            } else {
                printf("Token: %s\n", tokendata.to_utf8().c_str());
                printf("ERROR STATE %d row: %d line: %d \n",state, row_point,line_point);
                return t;
            }
        }
        state = nextstate;
        tokendata.push_back(nowdata);


        // make the right row number and line number
        if (lastdata == '\n') {
            ++row_point;
            line_point = 0;
            getNextLine(point+1);
        }
        ++point;
        ++line_point;
        lastdata = nowdata;
    }
    t->type = 0;// 0 is the error type
    return t;
}
