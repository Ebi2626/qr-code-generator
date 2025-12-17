#pragma once
#include <stdexcept>

namespace qrgen::core {
    class QrCodeVersion {
    private:
        int value;
    
    public:
        explicit QrCodeVersion(int v = 1) {
            if (v < 0 || v > 40) {
                throw std::out_of_range("QR Code version must be 0-40");
            }
            value = v;
        }
        
        int get() const { return value; }
    };
}