#pragma once	// 防止重复包含

#include <typeinfo>
#include <cxxabi.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

# define Get_Type(x) lyf::type_class<decltype(x)>::get()	// 用于获取变量类型的快捷调用宏

namespace lyf {

	template<typename Helper>
	struct cvr_saver {};	// 用于保存变量的const/volatile/reference属性

	/* 采用模板参数而不是函数参数的方式获取变量类型
	获取param的类型的调用格式为lyf::type_class<decltype(param)>::get() */
	template<typename T>
	class type_class {
	public:
		// 获取变量类型(依赖于typeid关键字)
		static std::string get() {
			std::string all_realName = std::string{abi::__cxa_demangle(typeid(cvr_saver<T>).name(), nullptr, nullptr, nullptr)};	// 包含cuv_saver结构体的全名
			int pos1 = all_realName.find_first_of('<') + 1;	// 第一个'<'后的位置
			int pos2 = all_realName.find_last_of('>');	// 最后一个'>'的位置
			std::string realName = all_realName.substr(pos1, pos2 - pos1);	// 去掉干扰信息
			return realName;
		}
	};

	/// @brief 仿python的split函数, 分隔符为char
	/// @param str 要分隔的字符串
	/// @param delim 分隔符
	/// @return 分隔后的字符串数组, 以vector<string>形式返回
	std::vector<std::string> split(const std::string& str, const char delim) {
		std::stringstream ss(str);
		std::string s;
		std::vector<std::string> res;
		res.clear();
		while (getline(ss, s, delim)) {
			res.push_back(s);
		}
		return res;
	}

	/// @brief 仿python的split函数, 分隔符为string
	/// @param str 要分隔的字符串
	/// @param delim 分隔符
	/// @return 分隔后的字符串数组, 以vector<string>形式返回
	std::vector<std::string> split(const std::string& str, const std::string& delim) {
		std::string::size_type pos1, pos2;
		pos1 = 0;
		pos2 = str.find_first_of(delim, pos1);	// 查找第一个分隔符的位置
		std::vector<std::string> res;
		while (std::string::npos != pos2) {
			res.push_back(str.substr(pos1, pos2 - pos1));
			pos1 = pos2 + delim.size();
			pos2 = str.find(delim, pos1);
		}
		if (pos1 != str.size())
			res.push_back(str.substr(pos1));
		return res;
	}

}