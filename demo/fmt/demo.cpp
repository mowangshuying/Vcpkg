#include <fmt/core.h>
#include <fmt/color.h>

#include <vector>

int main()
{
    fmt::print("Hello, World!\n");
    fmt::print("The answer is {}\n", 42);
    fmt::print("The answer is {:.2f}", 1.123456789);

    std::string s = fmt::format("I'd rather be {1} than {0}.", "right", "happy");


    // std::vector<int> v = {1, 2, 3};
    // fmt::print("{}\n", v);

    fmt::print("info\n");
    fmt::print( fg(fmt::color::green), "success\n");
    fmt::print( fg(fmt::color::orange) | fmt::emphasis::underline, "warning\n");
    fmt::print( fg(fmt::color::red) | fmt::emphasis::bold | fmt::emphasis::underline, "error\n");
    return 0;
}