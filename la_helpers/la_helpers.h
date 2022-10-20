#include <memory>
#include <vector>
#include <string>

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
