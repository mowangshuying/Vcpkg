#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main()
{
    json j;
    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["list"] = { 1, 0, 2 };
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    std::cout << "pi:" << j.at("pi") << "\n";
    std::cout << "happy:" << j.at("happy") << "\n";
    std::cout << "name:" << j.at("name") << "\n";
    std::cout << "nothing:" << j.at("nothing") << "\n";
    std::cout << "everything:" << j.at("answer").at("everything") << "\n";
    //std::cout << "list:" << j.at("list") << "\n";

    std::cout << "object.currency:" << j.at("object").at("currency") << "\n";

    // json to str;
    std::cout << "json to str:" <<j.dump() << "\n";

    auto pj = json::parse(j.dump());
    std::cout << "pj.pi:" << pj.at("pi") << "\n";
}