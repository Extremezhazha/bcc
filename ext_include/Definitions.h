#ifndef BC_DEFINITIONS_H
#define BC_DEFINITIONS_H

#include <iostream>
#include <type_traits>

namespace bc {
    using integer_t = int;

    template <integer_t value>
    using integer_constant = std::integral_constant<integer_t, value>;

    namespace arrays {
        template <typename... Types>
        struct type_pack {
            using type = type_pack;
        };

        template <std::size_t idx, typename Type>
        struct get_impl : get_impl<idx, typename Type::type> {};

        template <std::size_t idx, typename First, typename... Rest>
        struct get_impl<idx, type_pack<First, Rest...>> : get_impl<idx - 1, type_pack<Rest...>> {};

        template <typename First, typename... Rest>
        struct get_impl<0, type_pack<First, Rest...>> {
            using type = First;
        };

        template <std::size_t idx, typename Type>
        using get = typename get_impl<idx, Type>::type;

        template <typename Lhs, typename Rhs>
        struct concat_impl;

        template <typename... LhsTypes, typename... RhsTypes>
        struct concat_impl<type_pack<LhsTypes...>, type_pack<RhsTypes...>> {
            using type = type_pack<LhsTypes..., RhsTypes...>;
        };

        template <typename Lhs, typename Rhs>
        using concat = typename concat_impl<Lhs, Rhs>::type;

        template <typename Arr, integer_t Factor, typename = void>
        struct multiply_impl;

        template <typename... ArrTypes>
        struct multiply_impl<type_pack<ArrTypes...>, 0> {
            using type = type_pack<>;
        };

        template <typename... ArrTypes, integer_t Factor>
        struct multiply_impl<type_pack<ArrTypes...>, Factor, std::enable_if_t<(Factor > 0)>> :
                concat_impl<type_pack<ArrTypes...>, typename multiply_impl<type_pack<ArrTypes...>, Factor - 1>::type> {};

        template <typename Lhs, integer_t Factor>
        using multiply = typename multiply_impl<Lhs, Factor>::type;
    }

    namespace operators {

        template <typename Lhs, typename Rhs>
        struct add : add<typename Lhs::type, typename Rhs::type> {};

        template <integer_t Lhs, integer_t Rhs>
        struct add<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs + Rhs> {};

        template <typename... LhsTypes, typename...RhsTypes>
        struct add<arrays::type_pack<LhsTypes...>, arrays::type_pack<RhsTypes...>> : arrays::concat<arrays::type_pack<LhsTypes...>, arrays::type_pack<RhsTypes...>> {};


        template <typename Lhs, typename Rhs>
        struct minus : minus<typename Lhs::type, typename Rhs::type> {};

        template <integer_t Lhs, integer_t Rhs>
        struct minus<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs - Rhs> {};


        template <typename Lhs, typename Rhs>
        struct multiply : multiply<typename Lhs::type, typename Rhs::type> {};

        template <integer_t Lhs, integer_t Rhs>
        struct multiply<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs * Rhs> {};

        template <typename... LhsTypes, integer_t Rhs>
        struct multiply<arrays::type_pack<LhsTypes...>, integer_constant<Rhs>> : arrays::multiply<arrays::type_pack<LhsTypes...>, Rhs> {};


        template <typename Lhs, typename Rhs>
        struct divide : divide<typename Lhs::type, typename Rhs::type> {};

        template <integer_t Lhs, integer_t Rhs>
        struct divide<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs / Rhs> {};
    }

    namespace utils {

        template <typename Type>
        struct printer{
            template <typename U> friend std::ostream&
            operator<<(std::ostream & lhs, const printer<U> & rhs);

            template <integer_t val> friend std::ostream&
            operator<<(std::ostream & lhs, const printer<integer_constant<val>> & rhs);

            template <typename... Types> friend std::ostream&
            operator<<(std::ostream & lhs, const printer<arrays::type_pack<Types...>> & rhs);
        };

        namespace impl {
            std::ostream & list_print(std::ostream & lhs, printer<arrays::type_pack<>> const & rhs) { return lhs; }

            template <typename Type>
            std::ostream & list_print(std::ostream & lhs, printer<Type> const & rhs) { return lhs << rhs; }

            template <typename Type>
            std::ostream & list_print(std::ostream & lhs, printer<arrays::type_pack<Type>> const & rhs) { return lhs << printer<Type>{}; }

            template <typename First, typename... Rest>
            std::ostream & list_print(std::ostream & ostream, printer<arrays::type_pack<First, Rest...>> const &) {
                return list_print(ostream << printer<First>{} << ", ", printer<arrays::type_pack<Rest...>>{});
            }
        }

        template <typename U>
        std::ostream&
        operator<<(std::ostream & lhs, printer<U> const & rhs) {
            return lhs << printer<typename U::type>{};
        }

        template <integer_t val>
        std::ostream&
        operator<<(std::ostream & lhs, printer<integer_constant<val>> const & rhs) {
            return lhs << val;
        }

        template <typename... Types>
        std::ostream&
        operator<<(std::ostream & lhs, printer<arrays::type_pack<Types...>> const & rhs) {
            return impl::list_print(lhs << "[", rhs) << "]";
        }

    }
}

#endif //BC_DEFINITIONS_H
