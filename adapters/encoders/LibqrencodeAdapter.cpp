#include "LibqrencodeAdapter.hpp"
#include <qrencode.h>
#include <memory>

namespace qrgen::adapters::encoders {

std::unique_ptr<qrgen::> LibqrencodeAdapter::encode(
    const std::string& text,
    const domain::QrCodeOptions& options
) {
    QRcode* raw = QRcode_encodeString(
        text.c_str(),
        options.version,
        mapErrorCorrectionLevel(options.ecLevel),
        QR_MODE_8,
        1
    );
    
    if (!raw) {
        throw std::runtime_error("QR encoding failed");
    }
    
    auto qrCode = std::make_unique<domain::QrCode>();
    qrCode->size = raw->width;
    qrCode->modules.resize(qrCode->size * qrCode->size);
    
    for (int i = 0; i < qrCode->size * qrCode->size; ++i) {
        qrCode->modules[i] = (raw->data[i] & 0x1) != 0;
    }
    
    QRcode_free(raw);
    return qrCode;
}

}
