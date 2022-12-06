#pragma once

#include "ClassFactory.h"

using std::string;

// 注册类的宏
#define REGISTER_CLASS(className) 			\
	Object * createObject##className() { 	\
		Object * obj = new className();		\
		obj->set_class_name(#className);		\
		return obj;							\
	}										\
	ClassRegister classRegister##className(#className, createObject##className)

// 注册字段的宏
#define REGISTER_CLASS_FIELD(className, fieldName, fieldType) \
    className className##fieldName; \
    ClassRegister classRegister##className##fieldName(#className, #fieldName, #fieldType, (size_t)(&(className##fieldName.fieldName)) - (size_t)(&className##fieldName))




namespace lyf {
	namespace reflect {

		class ClassRegister {
		public:
			ClassRegister(const string& className, create_object method) {
				ClassFactory::Instance()->register_class(className, method);
			}

			ClassRegister(const string& className, const string& fieldName, const string& fieldType, size_t offset) {
				ClassFactory::Instance()->register_class_field(className, fieldName, fieldType, offset);
			}
		};

	}
}
