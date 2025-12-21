#pragma once
#include <string>
#include <vector>
#include "QrCode.hpp"

namespace qrgen::core::ports {

class IQrExporter {
public:
    virtual ~IQrExporter() = default;
    
    virtual std::vector<uint8_t> exportToBytes(
        const qrgen::core::QrCode& qrCode,
        int pixelSize,
        int margin
    ) = 0;
    
    virtual void exportToFile(
        const qrgen::core::QrCode& qrCode,
        const std::string& filename,
        int pixelSize,
        int margin
    ) = 0;
};

}
