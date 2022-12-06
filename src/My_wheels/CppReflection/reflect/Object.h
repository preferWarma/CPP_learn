#pragma once

#include <string>
#include <iostream>
#include "ClassFactory.h"
#include "ClassField.h"

using std::string;

namespace lyf {
	namespace reflect {

		class Object {
		public:
			Object() = default;
			virtual ~Object() = default;

			void set_class_name(const string& className) {	// 设置类名
				m_className = className;
			}

			const string& get_class_name() {	// 获取类名
				return m_className;
			}

			int get_field_count();	// 获取该类的字段数量
			ClassField* get_field(int pos);	// 获取该类的第pos个字段
			ClassField* get_field(const string& fieldName);	// 获取该类的名为fieldName的字段

			template<typename T>
			T& get(const string& fieldName) {	// 获取字段值
				auto offset = get_field(fieldName)->get_offset();
				return *reinterpret_cast<T*>(reinterpret_cast<intptr_t>(this) + offset);
			}

			template<typename T>
			void set(const string& fieldName, const T& value) {	// 设置字段值
				auto offset = get_field(fieldName)->get_offset();
				*reinterpret_cast<T*>(reinterpret_cast<intptr_t>(this) + offset) = value;
			}

			virtual void print() = 0;

		private:
			string m_className;

		};
	}
}