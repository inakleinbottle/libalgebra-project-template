#include <memory>
#include <vector>
#include <string>
#include <iosfwd>

#include <libalgebra/libalgebra.h>
#include <libalgebra/alg_types.h>

namespace alghelp {
/**
 * @brief Base class for examples using a libalgebra environment
 */
class LibalgebraExample {
public:
    virtual ~LibalgebraExample() = default;

    virtual std::string name() const noexcept = 0;
    virtual unsigned width() const noexcept = 0;
    virtual unsigned depth() const noexcept = 0;
    virtual std::string ctype() const noexcept = 0;

    bool run_if_matches(const std::string& rname, unsigned rwidth = 0, unsigned rdepth = 0,
            const std::string& rctype = std::string());

    virtual void run() = 0;
};

template<unsigned Width, unsigned Depth, coefficient_t CType = coefficient_t::DPReal>
class LibalgebraExampleImpl :
        public LibalgebraExample,
        public alg_types<Depth, Width, CType> {


public:

    using my_alg_types = alg_types<Depth, Width, CType>;
    using TKEY = typename my_alg_types::TENSOR::KEY;
    using LKEY = typename my_alg_types::LIE::KEY;

    typename my_alg_types::MAPS maps;
    typename my_alg_types::CBH cbh;

    template <typename... Args>
    TKEY tensor_key(Args... args) const noexcept
    {
        return { alg::LET(args)... };
    }

    template <typename Left, typename Right>
    LKEY lie_key(Left left, Right right) const
    {
        const alg::hall_basis<Width, Depth> hall_set;
        return hall_set[{LKEY(left),
LKEY(right)}];
    }

    template <typename Letter>
    LKEY lie_key(Letter letter) const
    {
        const alg::hall_basis<Width, Depth> hall_set;
        return hall_set.keyofletter(alg::LET(letter));
    }

    template <typename F>
    typename my_alg_types::TENSOR tensor_from(F fn) const
    {
        const auto& tbasis = my_alg_types::TENSOR::basis;

        typename my_alg_types::TENSOR result;
        for (auto key : tbasis.iterate_keys()) {
            result.add_scal_prod(key, fn(key));
        }
        return result;
    }

    template <typename F>
    typename my_alg_types::LIE lie_from(F fn) const
    {
        const auto& lbasis = my_alg_types::LIE::basis;

        typename my_alg_types::LIE result;
        for (auto key : lbasis.iterate_keys()) {
            result.add_scal_prod(key, fn(key));
        }
        return result;
    }



};

std::vector<std::unique_ptr<LibalgebraExample>>& get_example_list() noexcept;

template<typename Example>
class LibalgebraExampleRegistrationHelper {
public:

    LibalgebraExampleRegistrationHelper()
    {
        auto& examples = get_example_list();
        examples.push_back(std::unique_ptr<LibalgebraExample>(new Example));
    }

};

template <typename T>
void show_impl(const char* name, const T& arg)
{
    std::cout << name << ": " << arg << '\n';
}






} // namespace alghelp

#define LIBALGEBRA_EXAMPLE(NAME, WIDTH, DEPTH, CTYPE)                   \
    class LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE :      \
        public alghelp::LibalgebraExampleImpl<WIDTH, DEPTH, CTYPE>      \
    {                                                                   \
    public:                                                             \
        std::string name() const noexcept override;                     \
        unsigned width() const noexcept override;                       \
        unsigned depth() const noexcept override;                       \
        std::string ctype() const noexcept override;                    \
        void run() override;                                            \
    };                                                                  \
                                                                        \
    std::string LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE::name() const noexcept \
    {                                                                   \
        return std::string(#NAME);\
    }                                                                   \
    unsigned LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE::width() const noexcept   \
    {                                                                   \
        return WIDTH;                                                                  \
    }\
    unsigned LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE::depth() const noexcept   \
    {                                                                   \
        return DEPTH;                                                                  \
    }\
    std::string LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE::ctype() const noexcept \
    {                                                                   \
        return std::string(#CTYPE);                                                                  \
    }\
                                                                        \
    static alghelp::LibalgebraExampleRegistrationHelper<                       \
        LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE>         \
        example_registration_##NAME##_##WIDTH##_##DEPTH##_##CTYPE;      \
                                                                        \
    void LibalgebraExample_##NAME##_##WIDTH##_##DEPTH##_##CTYPE::run()  \


#define SHOW(ARG) alghelp::show_impl(#ARG, ARG)
