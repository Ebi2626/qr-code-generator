#pragma once
#include "QrCode.hpp"
#include "QrCodeOptions.hpp"
#include <memory>

namespace qrgen::core::ports {

class IQrEncoder {
public:
    virtual ~IQrEncoder() = default;
    
    virtual std::unique_ptr<qrgen::core::QrCode> encode(
        const std::string& text,
        const qrgen::core::Options& options
    ) = 0;
};

}
