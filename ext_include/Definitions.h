#ifndef BC_DEFINITIONS_H
#define BC_DEFINITIONS_H

#include <type_traits>

namespace bc {
    using integer_t = int;

    template <integer_t value>
    using integer_constant = std::integral_constant<integer_t, value>;

    namespace arrays {
        template <typename... Types>
        struct type_pack {};

        template <std::size_t idx, typename Type>
        struct get_impl;

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
    }

    namespace operators {

        template <typename Lhs, typename Rhs>
        struct add : add<integer_constant<Lhs::value>, integer_constant<Rhs::value>> {};

        template <integer_t Lhs, integer_t Rhs>
        struct add<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs + Rhs> {};


        template <typename Lhs, typename Rhs>
        struct minus : minus<integer_constant<Lhs::value>, integer_constant<Rhs::value>> {};

        template <integer_t Lhs, integer_t Rhs>
        struct minus<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs - Rhs> {};


        template <typename Lhs, typename Rhs>
        struct multiply : multiply<integer_constant<Lhs::value>, integer_constant<Rhs::value>> {};

        template <integer_t Lhs, integer_t Rhs>
        struct multiply<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs * Rhs> {};


        template <typename Lhs, typename Rhs>
        struct divide : divide<integer_constant<Lhs::value>, integer_constant<Rhs::value>> {};

        template <integer_t Lhs, integer_t Rhs>
        struct divide<integer_constant<Lhs>, integer_constant<Rhs>> : integer_constant<Lhs / Rhs> {};
    }
}

#endif //BC_DEFINITIONS_H
