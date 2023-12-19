template <typename... Ts> // (7)
struct Overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

#define STRICT(type, id_name) std::same_as<type> auto id_name
