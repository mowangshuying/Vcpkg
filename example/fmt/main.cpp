#include <fmt/core.h>
#include <fmt/color.h>

int main()
{
    fmt::print("info\n");
    fmt::print( fg(fmt::color::green), "success\n");
    fmt::print( fg(fmt::color::orange) | fmt::emphasis::underline, "warning\n");
    fmt::print( fg(fmt::color::red) | fmt::emphasis::bold | fmt::emphasis::underline, "error\n");
    return 0;
}