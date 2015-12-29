#ifndef CHAR_SET_H
#define CHAR_SET_H


#include <map>
#include <string>
#include "estring.h"

/**
 * @brief 字符集中的一个区间标记
 */
struct cv{
	char type;
	unsigned short eclass;
	cv() {
		type = 0;
		eclass = 0;
	}
	cv(char _type,unsigned short _eclass) {
		type = _type;
		eclass = _eclass;
	}
	cv(const cv &p) {
		this->type = p.type;
		this->eclass = p.eclass;
	}
};


/**
 * @brief 一个UTF-16字符集
 * @details 使用区间描述的字符集
 */
class CharSet
{
public:
	CharSet();
	~CharSet();

	// copy constructor
	CharSet(const CharSet& copy);

	// make constructor
	CharSet(const estring& str);

	// 已弃用
	// void Combine(const CharSet& obj);

	bool operator==(const CharSet&);

	// all the char is saved in the balanced tree.
	std::map<echar_t, cv> charset; //to make the test,it should be private

	// insert method , type = 0 means a standalone char
	// type = 1 means the begin of a interval, type = 2 means the end of the interval.
	// void insert(echar_t p, echar_t q, unsigned short eclass);
	void insert(echar_t p, echar_t q);
	void insert(echar_t c);
	estring str;

	// make the set negate
	bool negate = false;

	unsigned short eclass_sum;

private:
	echar_t CharEscape(estring::iterator& i);
	int HexToDec(const char *s);
};

#endif // CHAR_SET_H
