#include "DFACore.h"

Token* DFACore::Read() {
    state = 0;
    tokendata.clear();
    if (t != NULL) delete t;
    t = new Token();
    echar_t nowdata, lastdata;
    while (point < data.length()) {
        nowdata = data[point];
        // for each word ,may get it Equal Class
        echar_t c = pEClass->getClass(nowdata);

        // test the next state
        int nextstate = dfa->nextState(state, c);
        
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
                    state = 0;
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
        }
        ++point;
        ++line_point;
        lastdata = nowdata;
    }
    t->type = 0;// 0 is the error type
    return t;
}
