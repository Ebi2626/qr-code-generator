#pragma once

#include "qrgen/QrCode.hpp"
#include "qrgen/QrGenerator.hpp"
#include <string>

namespace qrgen::infra
{

    class IQrEncoder
    {
    public:
        virtual ~IQrEncoder() = default;

        virtual qrgen::core::QrCode encode(
            const qrgen::core::Options &opt) = 0;
    };

}
