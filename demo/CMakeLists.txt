add_executable(fmtdemo fmt/demo.cpp)
target_link_libraries(fmtdemo PRIVATE fmt::fmt)

add_executable(spdlogdemo spdlog/demo.cpp)
target_link_libraries(spdlogdemo PRIVATE spdlog::spdlog)

add_executable(jsondemo json/demo.cpp)
target_link_libraries(jsondemo PRIVATE nlohmann_json::nlohmann_json)