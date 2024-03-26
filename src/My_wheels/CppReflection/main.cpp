#include <iostream>

#include "reflect.hpp"

using namespace std;

class Foo {
public:
    void PassByValue(string s) const {
        cout << "Foo::PassByValue(`" << s << "`)" << endl;
    }

    void PassByConstRef(const string& s) const {
        cout << "Foo::PassByConstRef(const `" << s << "` &)" << endl;
    }

    // 将两个字符串拼接并返回结果
    string Concat(const string& head, const string& tail) {
        auto res = head + tail;
        return res;
    }

    // 创建一个指向浮点数的 shared_ptr
    shared_ptr<float> MakeFloatPtr(float i) {
        return make_shared<float>(i);
    }

    // 将该类设置为可反射
    static void MakeReflectable() {
        // 将类 Foo 添加到反射系统中
        reflect::AddClass<Foo>("Foo")
            .AddMemberVar("name", &Foo::name)
            .AddMemberVar("x_", &Foo::x_)
            .AddMemberFunc("PassByValue", &Foo::PassByValue)
            .AddMemberFunc("PassByConstRef", &Foo::PassByConstRef)
            .AddMemberFunc("Concat", &Foo::Concat)
            .AddMemberFunc("MakeFloatPtr", &Foo::MakeFloatPtr);
    }

    // 返回私有变量 x_
    int x() const { return x_; }

    // 类的名称
    string name;

private:
    // 私有变量 x_
    int x_{ 0 };
};

// 测试成员函数
void TestMemberFunction() {
    cout << ">>> TestMemberFunction" << endl;

    // 引入 reflect::details 命名空间
    using namespace reflect::details;

    Foo f;
    string hello_s{ "hello" };
    string world_s{ " world" };

    MemberFunction foo_pass_by_val{ &Foo::PassByValue };
    foo_pass_by_val.Invoke(f, hello_s);

    MemberFunction foo_pass_by_cref{ &Foo::PassByConstRef };
    foo_pass_by_cref.Invoke(f, cref(hello_s));  // 使用 const 引用

    MemberFunction foo_concat{ &Foo::Concat };
    auto res = foo_concat.Invoke(f, cref(hello_s), cref(world_s));
    cout << "Concat got: " << any_cast<string>(res) << endl;

    cout << "<<< TestMemberFunction OK\n" << endl;
}

// 测试成员变量
void TestMemberVariable() {
    cout << ">>> TestMemberVariable" << endl;

    // 引入 reflect::details 命名空间
    using namespace reflect::details;

    struct S {
        int a{ 0 };
        float b{ 0.0f };
    };

    MemberVariable s_a{ &S::a };
    MemberVariable s_b{ &S::b };
    S s{};
    s_a.SetValue(s, 42);
    s_b.SetValue(s, 123.4f);
    cout << "s.a=" << s_a.GetValue<int>(s) << " expected=" << s.a << endl;
    cout << "s.b=" << s_b.GetValue<float>(s) << " expected=" << s.b << endl;

    cout << "<<< TestMemberVariable OK\n" << endl;
}

// 测试 Foo 类
void TestFoo() {
    cout << ">>> TestFoo\n" << endl;

    Foo::MakeReflectable();
    auto foo_t = reflect::GetByName("Foo");

    // 打印成员变量
    for (const auto& mv : foo_t.member_vars()) {
        cout << "member var: " << mv.name() << endl;
    }
    cout << endl;

    // 打印成员函数
    for (const auto& mf : foo_t.member_funcs()) {
        cout << "member func: " << mf.name() << ", is_const=" << mf.is_const() << endl;
    }
    cout << endl;

    Foo f;

    // 测试成员变量
    auto name_var = foo_t.GetMemberVar("name");
    name_var.SetValue(f, string{ "taichi" });
    cout << "f.name=" << f.name << endl;

    auto x_var = foo_t.GetMemberVar("x_");
    x_var.SetValue(f, 42);
    cout << "f.x=" << f.x() << endl;

    // 测试成员函数
    auto foo_make_float_ptr = foo_t.GetMemberFunc("MakeFloatPtr");
    auto res = foo_make_float_ptr.Invoke(f, 123.4f);
    auto float_sptr = any_cast<shared_ptr<float>>(res);
    cout << "MakeFloatPtr res: " << *float_sptr << endl;

    string hello_s{ "hello" };
    string world_s{ " world" };

    auto foo_pass_by_val = foo_t.GetMemberFunc("PassByValue");
    foo_pass_by_val.Invoke(f, hello_s);

    auto foo_pass_by_cref = foo_t.GetMemberFunc("PassByConstRef");
    foo_pass_by_cref.Invoke(f, cref(hello_s));  // 使用 const 引用

    auto foo_concat = foo_t.GetMemberFunc("Concat");
    res = foo_concat.Invoke(f, cref(hello_s), cref(world_s));
    cout << "Concat got: " << any_cast<string>(res) << endl;

    cout << "<<< TestFoo OK\n" << endl;
}

int main() {
    TestFoo();
}
