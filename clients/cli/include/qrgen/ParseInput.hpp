#pragma once
#include <string>
#include <vector>
#include "qrgen/QrGenerator.hpp"

namespace qrgen::cli {
    qrgen::core::Options parseInput(const std::vector<std::string>& args);
}