#ifndef GRAPHVIZ_PRINTER_HPP
#define GRAPHVIZ_PRINTER_HPP

#include <ostream>
#include "DFA.h"
#include "DebugMsg.h"

class GraphvizPrinter {
public:
    static void print(DFA* dfa) {
        if (!DebugMsg::isDebug()) return;
        std::ostream& os = DebugMsg::lex_graphviz();
        os << "digraph G {" << endl;
        for (int i = 0; i < dfa->getStateSum(); ++i) {
            for (int j = 1; j<=dfa->getEClass()->getSum(); ++j) {
                int next = dfa->nextState(i, j);
                os << "\"#" << i << "\" -> \"" << "#"
                   << next << "\"[label=\"" << j << "\"]" << endl;
            }
        }
        os << "}" << endl;
        DebugMsg::lex_graphviz_close();
    }


};


#endif /* end of include guard: GRAPHVIZ_PRINTER_HPP */
