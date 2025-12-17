#pragma once

#include "qrgen/IQrEncoder.hpp"

namespace qrgen::infra {

class QrEncoderLibqrencode : public IQrEncoder {
public:
    qrgen::core::QrCode encode(
        const qrgen::core::Options& opt) override;
};
} 
