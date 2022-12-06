#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "Object.h"
#include "ClassField.h"

namespace lyf {
	
	namespace reflect {

		using create_object = Object * (*)();	// 定义指针类型
		using std::string;

		class ClassFactory {
		public:
			static ClassFactory* Instance() {	// 单例模式
				static ClassFactory* instance = new ClassFactory();
				return instance;
			}

			void register_class(const std::string& className, create_object method) {	// 注册
				m_map[className] = method;
			}

			Object* create_class(const std::string& className) {
				auto it = m_map.find(className);
				if (it == m_map.end()) {
					return nullptr;
				}
				else {
					return it->second();
				}
			}

			void register_class_field(const std::string& className, const string& fieldName, const string& fieldType, size_t offset) {	// 注册
				m_fieldMap[className].emplace_back(fieldName, fieldType, offset);
			}



			int get_field_count(const string& className) {	// 获取该类的字段数量
				return m_fieldMap[className].size();
			}

			ClassField* get_field(const string& className, int pos) {	// 获取该类的第pos个字段
				if (pos < 0 || pos >= get_field_count(className)) {
					return nullptr;
				}
				return &m_fieldMap[className][pos];
			}

			ClassField* get_field(const string& className, const string& fieldName) {	// 获取该类的名为fieldName的字段
				int pos = 0;
				for (auto i : m_fieldMap[className]) {
					if (i.get_name() == fieldName) {
						return &m_fieldMap[className][pos];
					}
					pos++;
				}
				return nullptr;
			}

		private:
			std::unordered_map<std::string, create_object> m_map;	// 保存类名和创建对象的函数指针的映射
			std::unordered_map<std::string, std::vector<ClassField>> m_fieldMap;	// 保存类名和字段的映射

			ClassFactory() = default;
			~ClassFactory() = default;

		};	// class ClassFactory

		int Object::get_field_count() {
			return ClassFactory::Instance()->get_field_count(m_className);
		}

		ClassField* Object::get_field(int pos) {
			return ClassFactory::Instance()->get_field(m_className, pos);
		}

		ClassField* Object::get_field(const string& fieldName) {
			return ClassFactory::Instance()->get_field(m_className, fieldName);
		}

	}	// namespace reflect
}	// namespace lyf