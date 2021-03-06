#include <memory>
#include <string>
#include <iostream>
#include "allocator.h"
#include "allocator_traits.h"

int main()
{
    using namespace cyy;
    cyy::Allocator<int> a1;   // int 的默认分配器
    int* a = Allocator_traits<decltype(a1)>::allocate(a1, 1) ;  // 一个 int 的空间
    Allocator_traits<decltype(a1)>::construct(a1, a, 7);
    // a1.construct(a, 7);       // 构造 int
    std::cout << a[0] << '\n';
    Allocator_traits<decltype(a1)>::deallocate(a1, a, 1);
    // a1.deallocate(a, 1);      // 解分配一个 int 的空间
 
    // string 的默认分配器
    cyy::Allocator<std::string> a2;
 
    // 同上，但以 a1 的重绑定获取
    decltype(a1)::rebind<std::string>::other a2_1;
 
    // 同上，但通过 Allocator_traits 由类型 a1 的重绑定获取
    cyy::Allocator_traits<decltype(a1)>::rebind_alloc<std::string> a2_2;

    std::string* s = Allocator_traits<decltype(a2)>::allocate(a2, 2);
    // std::string* s = a2.allocate(2); // 2 个 string 的空间
    
    Allocator_traits<decltype(a2)>::construct(a2, s, "foo");
    Allocator_traits<decltype(a2)>::construct(a2, s+1, "bar");
    // a2.construct(s, "foo");
    // a2.construct(s + 1, "bar");
 
    std::cout << s[0] << ' ' << s[1] << '\n';

    Allocator_traits<decltype(a2)>::destroy(a2, s);
    Allocator_traits<decltype(a2)>::destroy(a2, s+1);
    Allocator_traits<decltype(a2)>::deallocate(a2, s, 2);

    // a2.destroy(s);
    // a2.destroy(s + 1);
    // a2.deallocate(s, 2);
}