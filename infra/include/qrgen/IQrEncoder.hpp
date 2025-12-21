#pragma once

#include <QrCode.hpp>
#include <QrGenerator.hpp>
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
