#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>

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
    std::cout  << j.dump() << "\n";

    auto pj = json::parse(j.dump());
    std::cout << "pj.pi:" << pj.at("pi") << "\n";

    json cj = { {"pi", 3.141}, {"happy", true}, {"name", "Niels"}, {"nothing", nullptr}, {"answer", {{"everything", 42}}}, {"list", {1, 0 ,2}}, {"object", {{"currency", "USD"}, {"value", 42.99}}} };
    std::cout <<  cj.dump() << "\n";

    std::vector<std::uint8_t> vBson = json::to_bson(cj);
    json fj = json::from_bson(vBson);

    // get;
    auto pi = cj["pi"].get<int>();
    std::cout << "pi:" << pi << std::endl;

    // stl oper;
    // std::cout << "stl oper demo:" << std::endl;

    json animalArray = {"cat", "dog"};
    animalArray.push_back("pig");
    animalArray.push_back("duck");

    std::cout << "array str:" << animalArray.dump() << std::endl;
    
    if (animalArray.is_array() && animalArray.size() > 0)
        std::cout << "array size:" << animalArray.size() << std::endl;

    std::cout << "animalArray lst:" << animalArray.at(animalArray.size() - 1) << std::endl;
}