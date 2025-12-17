#pragma once
#include <stdexcept>

namespace qrgen::core {
    class QrCodeMargin {
    private:
        int value;
    
    public:
        explicit QrCodeMargin(int v = 4) {
            if (v < 3 || v > 64) {
                throw std::out_of_range("QR Code margin must be 3-64");
            }
            value = v;
        }
        
        int get() const { return value; }
    };
}