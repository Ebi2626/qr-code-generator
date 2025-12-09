#pragma once
#include <vector>
#include <string>

namespace qrgen::core {

struct QrCode {
    int size;                        // N x N
    std::vector<bool> modules;       // size*size, row-major

    bool at(int x, int y) const {
        return modules[y * size + x];
    }
};

} // namespace qrgen::core
