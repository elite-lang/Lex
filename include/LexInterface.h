/* 
* @Author: sxf
* @Date:   2015-01-01 23:48:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-29 20:39:33
*/

#ifndef LEX_INTERFACE_H
#define LEX_INTERFACE_H

//it's a token for return
struct Token
{
	const char* pToken;
	int type;
    int col_num;
	int row_num;
    const char* debug_line;
};

/**
 * @brief Lex的关键接口
 * @details Lex的接口负责获取下一个Token，查询Rule，初始化Lex等任务，是最为核心的和外部模块的交互接口
 */
class LexInterface 
{
public:
	/// @brief 从输入流读取下一个字符， 无需释放资源，再下一次Read时，自动释放上个资源
    virtual Token* Read() = 0;

    /// @brief 对应每个规则，询问其名称是什么，为了在语法定义中和对应的id关联
    virtual const char* getRule(int id) = 0;
    
    /// @brief 初始化整个词法系统，并设置当前输入字符流，可以设置为NULL
    virtual void Init(const char* pData) = 0;

    /// @brief 不再初始化系统，只是简单的重设置输入字符流
    virtual void setData(const char* pData) = 0;

    /// @brief 获取总共有多少个词法规则
    virtual int getRuleSize() = 0;
};

#endif // LEX_INTERFACE_H

