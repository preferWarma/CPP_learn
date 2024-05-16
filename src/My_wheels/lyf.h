#ifndef LYF_H
#define LYF_H

#include <cxxabi.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

using std::cout, std::cin, std::endl;
using std::string, std::vector, std::stringstream;
using std::size_t;
using std::regex, std::smatch, std::sregex_iterator;

#define typeof(x) lyf::type_class<decltype(x)>::get()	// 用于获取变量类型的快捷调用宏

namespace lyf {

	template<typename Helper>
	struct cvr_saver {};	// 用于保存变量的const/volatile/reference属性

	/* 采用模板参数而不是函数参数的方式获取变量类型
	获取param的类型的调用格式为lyf::type_class<decltype(param)>::get() */
	template<typename T>
	class type_class {
	public:
		// 获取变量类型(依赖于typeid关键字)
		static string get() {
			string all_realName = string{ abi::__cxa_demangle(typeid(cvr_saver<T>).name(), nullptr, nullptr, nullptr) };	// 包含cuv_saver结构体的全名
			auto pos1 = all_realName.find_first_of('<') + 1;	// 第一个'<'后的位置
			auto pos2 = all_realName.find_last_of('>');	// 最后一个'>'的位置
			string realName = all_realName.substr(pos1, pos2 - pos1);	// 去掉干扰信息
			return realName;
		}
	};	// class type_class

	namespace StringTool {
		/// @brief 仿python的split函数, 分隔符为char
		/// @param str 要分隔的字符串
		/// @param delim 分隔符
		/// @return 分隔后的字符串数组, 以vector<string>形式返回
		vector<string> split(const string& str, const char delim) {
			stringstream ss(str);
			string s;
			vector<string> res;
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
		vector<string> split(const string& str, const string& delim) {
			size_t pos1 = 0;
			size_t pos2 = str.find_first_of(delim, pos1);	// 查找第一个分隔符的位置
			vector<string> res;
			while (string::npos != pos2) {
				res.push_back(str.substr(pos1, pos2 - pos1));
				pos1 = pos2 + delim.size();
				pos2 = str.find(delim, pos1);
			}
			if (pos1 != str.size())
				res.push_back(str.substr(pos1));
			return res;
		}

		/// @brief 以正则表达式匹配字符串
		/// @param str 要匹配的字符串
		/// @param pattern 要匹配的正则表达式
		/// @return 匹配后的字符串数组, 以vector<string>形式返回
		vector<string> regex_match(const string& str, const string& pattern) {
			regex m_pattern{ pattern };
			auto word_begin = sregex_iterator(str.begin(), str.end(), m_pattern);
			auto word_end = sregex_iterator();
			vector<string> res;
			for (auto i = word_begin; i != word_end; ++i) {
				smatch match = *i;
				res.emplace_back(match.str());
			}
			return res;
		}

		/// @brief 替换字符串中的第一个指定子串
		/// @param str 要替换的字符串
		/// @param old_value 要替换的子串
		/// @param new_value 替换后的子串
		/// @return 替换后的字符串
		string replace_first(const string& str, const string& old_value, const string& new_value) {
			string res = str;
			auto pos = res.find(old_value);
			if (pos != string::npos) {
				return res.replace(pos, old_value.length(), new_value);
			}
			else return str;
		}

		/// @brief 替换字符串中的所有指定子串
		/// @param str 要替换的字符串
		/// @param old_value 要替换的子串
		/// @param new_value 替换后的子串
		/// @return 替换后的字符串
		string replace_all(const string& str, const string& old_value, const string& new_value) {
			string res = str;
			for (size_t pos = 0; pos != string::npos; pos += new_value.length()) {
				pos = res.find(old_value, pos);
				if (pos != string::npos) {
					res.replace(pos, old_value.length(), new_value);
				}
				else break;
			}
			return res;
		}

		/// @brief 替换字符串中的最后一个指定子串
		/// @param str 要替换的字符串
		/// @param old_value 要替换的子串
		/// @param new_value 替换后的子串
		/// @return 替换后的字符串
		string replace_last(const string& str, const string& old_value, const string& new_value) {
			string res = str;
			auto pos = res.rfind(old_value);
			if (pos != string::npos) {
				return res.replace(pos, old_value.length(), new_value);
			}
			else return str;
		}

		/// @brief 判断字符串是否以指定前缀开头
		/// @param str 要判断的字符串
		/// @param prefix 前缀字符串
		/// @return 是否以指定前缀开头
		bool begin_with(const string& str, const string& prefix) {
			for (size_t i = 0; i < prefix.size(); ++i) {
				if (str[i] != prefix[i]) return false;
			}
			return true;
		}

		/// @brief 判断字符串是否以指定后缀结尾
		/// @param str 要判断的字符串
		/// @param suffix 后缀字符串
		/// @return 是否以指定后缀结尾
		bool end_with(const string& str, const string& suffix) {
			size_t str_len = str.size();
			size_t suffix_len = suffix.size();
			if (str_len < suffix_len) return false;
			for (size_t i = 0; i < suffix_len; ++i) {
				if (str[str_len - suffix_len + i] != suffix[i]) return false;
			}
			return true;
		}
	};	// namespace StringTool

	namespace PrintTool {
#if __cplusplus >= 201703L	// C++17以上才编译
		/// @brief 用于print_args的分隔符, 默认为空格, 单次使用, 调用后会被重置, 可以通过设置delimIsPersist为true使其持久化
		static string printDelim{ " " };
		/// @brief 分隔符是否持久化, 默认不持久化
		static bool delimIsPersist{ false };

		/// @brief 形参包遍历打印元素(C++17以后)
		template<typename T, typename ...Args>
		void print_args(T&& v, Args&&... args) {
			cout << v << printDelim;
			if constexpr (sizeof...(args) > 0) {
				print_args(std::forward<Args>(args)...);
			}
			else {
				cout << endl;
				if (!delimIsPersist)
					printDelim = " ";	// 恢复默认分隔符
			}
		}
#endif

		/// @brief 以迭代器方式遍历容器元素
		/// @param v 要遍历的容器
		/// @param delim 每个元素之间的分隔符
		template<typename T>
		void print_container(const T& v, const string& delim = " ") {
			for (const auto& i : v) {
				cout << i << delim;
			}
			cout << endl;
		}
	};	// namespace PrintTool

	template<class T1, class T2>
	auto max(T1&& a, T2&& b) {
		return a > b ? std::forward<T1>(a) : std::forward<T2>(b);
	}

	template<class T, class... Args>
	auto max(T&& a, Args&&... args) {
		return max(std::forward<T>(a), max(std::forward<Args>(args)...));
	}

	template<class T1, class T2>
	auto min(T1&& a, T2&& b) {
		return a < b ? std::forward<T1>(a) : std::forward<T2>(b);
	}

	template<class T, class... Args>
	auto min(T&& a, Args&&... args) {
		return min(std::forward<T>(a), min(std::forward<Args>(args)...));
	}

	/// @brief 基于迭代器的范围比较模板函数
	/// @param first 第一个迭代器(包含)
	/// @param last 最后一个迭代器(不包含)
	/// @param comp 比较函数
	/// @return 范围内按照比较函数比较后的最大值
	template<class Iterator, class Compare>
	auto range_compare(Iterator first, Iterator last, Compare comp = Compare()) -> typename std::iterator_traits<Iterator>::value_type {
		if (first == last) {
			throw std::invalid_argument("Range cannot be empty");
		}
		auto maxValue = *first;
		for (Iterator it = std::next(first); it != last; ++it) {
			if (comp(maxValue, *it)) {
				maxValue = *it;
			}
		}
		return maxValue;
	}

	/// @brief 基于迭代器的范围最大值模板函数
	/// @param first 第一个迭代器(包含)
	/// @param last 最后一个迭代器(不包含)
	/// @return 范围内的最大值
	template<class Iterator>
	auto range_max(Iterator first, Iterator last) {
		return range_compare(first, last, std::less<typename std::iterator_traits<Iterator>::value_type>());
	}

	/// @brief 基于迭代器的范围最小值模板函数
	/// @param first 第一个迭代器(包含)
	/// @param last 最后一个迭代器(不包含)
	/// @return 范围内的最小值
	template<class Iterator>
	auto range_min(Iterator first, Iterator last) {
		return range_compare(first, last, std::greater<typename std::iterator_traits<Iterator>::value_type>());
	}

	template <typename T>
	class Singleton {	// 泛型单例
	public:
		// 获取单例实例对象
		static T& GetInstance() {
			// 利用局部静态变量实现单例
			static T instance;
			return instance;
		}

		// 打印单例的地址
		void printAdress() {
			cout << this << endl;
		}

		// 禁止外部拷贝或赋值
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	protected:
		// 禁止外部构造和析构
		Singleton() = default;
		~Singleton() = default;
	};
}

#endif // LYF_H