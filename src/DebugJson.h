#ifndef DEBUG_JSON_H
#define DEBUG_JSON_H

#include "DebugMsg.h"
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>
#include <string>
#include <vector>

class LexLine {
public:
    LexLine(int l, int r, int s, int n) {
        col = l; row = r; status = s; next = n;
    }

    int col;
    int row;
    int status;
    int next;

private:
    // 串行化
    friend class cereal::access;

    template<class Archive>
    void serialize(Archive &ar) {
        ar( CEREAL_NVP(col),
            CEREAL_NVP(row),
            CEREAL_NVP(status),
            CEREAL_NVP(next));
    }
};


class DebugJson {
public:
    void addRegex(std::string name, std::string str) {
        rnames.push_back(name);
        regexs.push_back(str);
    }
    void addLine(int l, int r, int s, int n) {
        lines.push_back(LexLine(l,r,s,n));
    }
    void save() {
        if (DebugMsg::isDebug()) {
            {
        	    cereal::JSONOutputArchive oarchive(DebugMsg::lex_save());
        	    oarchive(
                    cereal::make_nvp("lex", *this));
            } // 通过让oarchive提前析构，为文件输出流添加结尾
    		DebugMsg::lex_save_close(); // 一定要确保JSONOutput输出完后再close
        }
    }
    void clear() {
        rnames.clear();
        regexs.clear();
        lines.clear();
    }

    static DebugJson& getInst() {
        static DebugJson inst;
        return inst;
    }
private:
    std::vector<std::string> rnames;
    std::vector<std::string> regexs;
    std::vector<LexLine> lines;

    // 串行化
    friend class cereal::access;

    template<class Archive>
    void serialize(Archive &ar)
    {
        // serialize things by passing them to the archive
        ar( CEREAL_NVP(rnames),
            CEREAL_NVP(regexs),
            CEREAL_NVP(lines) );
    }
};



#endif /* end of include guard: DEBUG_JSON_H */
