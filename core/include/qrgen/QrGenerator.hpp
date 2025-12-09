#pragma once
#include "QrCode.hpp"
#include <string>

namespace qrgen::core {

struct Options {
    int version = 1;        // placeholder
};

class QrGenerator {
public:
    QrCode generate(const std::string& text, const Options& opt = {});
};

} // namespace qrgen::core
