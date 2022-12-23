#include <iostream>
#include <tuple>

using namespace std;

template<typename E>
constexpr auto toUType(E enumerator) noexcept {
	return static_cast<std::underlying_type_t<E>>(enumerator);
}

using UserInfor = std::tuple<std::string,	// name
	std::string,	// email
	std::size_t>;	// age

int main() {
	enum class UserInfoFields { name, email, age };
	UserInfor userInfo {"John", "123@qq.com", 18};
	auto name = std::get<toUType(UserInfoFields::name)>(userInfo);
	cout << name << endl;
	return 0;
}