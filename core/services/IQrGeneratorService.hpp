#pragma once

#include <QrCode.hpp>
#include <QrCodeOptions.hpp>
#include <memory>
#include <string>

namespace qrgen::core::services {

class QrGeneratorService {
public:
    virtual ~QrGeneratorService() = default;
    
    virtual std::unique_ptr<qrgen::core::QrCode> generateQrCode(
        const std::string& text,
        const qrgen::core::Options& options
    ) = 0;
    
    virtual void generateAndExport(
        const std::string& text,
        const qrgen::core::Options& options,
        const std::string& outputPath
    ) = 0;
};

}
