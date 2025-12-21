#pragma once

#include <QrCodeVersion.hpp>
#include <QrCodeMargin.hpp>

namespace qrgen::core {
    enum class OutputFormat
    {
        PNG,
        JPG,
        SVG
    };

    enum class ErrorCorrectionLevel
    {
        L = 0,
        M = 1,
        Q = 2,
        H = 3
    };

    struct Options
    {
        std::string text = "";
        std::string output = "qrcode.png";
        int size = 8;
        OutputFormat format = OutputFormat::PNG;
        ErrorCorrectionLevel ecLevel = ErrorCorrectionLevel::L;
        QrCodeVersion version = QrCodeVersion(1);
        QrCodeMargin margin = QrCodeMargin(4);
    };

}