#pragma once
#include <nlohmann/json.hpp>
#include <string>

typedef nlohmann::json Config;

Config load_config(std::string path);