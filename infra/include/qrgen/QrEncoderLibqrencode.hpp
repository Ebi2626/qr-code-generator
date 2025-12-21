#pragma once

#include <IQrEncoder.hpp>

namespace qrgen::infra
{

    class QrEncoderLibqrencode : public qrgen::infra::IQrEncoder
    {
    public:
        qrgen::core::QrCode encode(
            const qrgen::core::Options &opt);
    };
}
