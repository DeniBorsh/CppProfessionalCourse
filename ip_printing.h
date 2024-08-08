#include <iostream>
#include <tuple>

namespace contaro {

// ----------------- is_iterable -------------------------

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T&>())),
                                  decltype(std::end(std::declval<T&>()))
                                 >
                  > : std::true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

// -------------------------------------------------------



template<typename T, typename std::enable_if<std::is_integral_v<T>>::type* = {}>
void print_ip(T raw_ip) {
    size_t size = sizeof(T);
    for(int i = size - 1; i >= 0; --i) {
        if (i != size - 1) std::cout << ".";
        std::cout << (uint16_t)(uint8_t)(raw_ip >> i*8);
    }
    std::cout << std::endl;
}

template<typename T, typename std::enable_if<is_iterable_v<T>>::type* = {}>
void print_ip(T&& raw_ip) {
    for (auto it = std::begin(raw_ip); it != std::end(raw_ip); ++it) {
        if (it != std::begin(raw_ip)) std::cout << ".";
        std::cout << *it;
    }
    std::cout << std::endl;
}

template <typename... T>
void print_ip(std::tuple<T...>&& raw_ip) {
    static_assert(std::conjunction<std::is_same<T, typename std::tuple_element<0, std::tuple<T...>>::type>...>::value,
                  "All types in the tuple must be the same");
    std::apply([](const T&... args) { ((std::cout << args << '.'), ...); }, raw_ip);

    std::cout << "\b \n";
}
void print_ip(std::string&& raw_ip) {
    std::cout << raw_ip << std::endl;
}

void print_ip(const char* raw_ip) {
    std::cout << raw_ip << std::endl;
}

}