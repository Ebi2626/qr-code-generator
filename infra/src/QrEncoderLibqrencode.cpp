#include "qrgen/QrEncoderLibqrencode.hpp"
#include <qrencode.h> // z libqrencode
#include <stdexcept>
#include <lodepng.h>
#include <vector>

/*
 * Reprezentuje warstwę infrastruktury
 * Powinna zawierać implementacje interfejsów z warstwy core
 * Powinna korzystać z bibliotek zewnętrznych (np. libqrencode) do realizacji funkcji generowania kodów QR
 * Nie powinna zawierać żadnych elementów logiki biznesowej ani dostępu do danych
 */

namespace qrgen::infra
{

    // pomocnicza funkcja do mapowania poziomu ECC z Options na QRecLevel
    static QRecLevel to_rec_level(const qrgen::core::ErrorCorrectionLevel &ecLevel)
    {
        switch (ecLevel)
        {
        case qrgen::core::ErrorCorrectionLevel::L:
            return QR_ECLEVEL_L;
        case qrgen::core::ErrorCorrectionLevel::M:
            return QR_ECLEVEL_M;
        case qrgen::core::ErrorCorrectionLevel::Q:
            return QR_ECLEVEL_Q;
        case qrgen::core::ErrorCorrectionLevel::H:
            return QR_ECLEVEL_H;
        default:
            return QR_ECLEVEL_M;
        }
    }

    void saveToPng(
        const QRcode *raw,
        const qrgen::core::Options &opt)
    {
        int pixelSize = opt.size;
        int margin = opt.margin.get() * pixelSize;
        int width = (raw->width * pixelSize) + (2 * margin);

        std::vector<unsigned char> image(width * width * 4);

        for (int y = 0; y < width; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int moduleX = (x - margin) / pixelSize;
                int moduleY = (y - margin) / pixelSize;

                bool isModule = (moduleX >= 0 && moduleX < raw->width &&
                                 moduleY >= 0 && moduleY < raw->width &&
                                 (raw->data[moduleY * raw->width + moduleX] & 0x1) != 0);

                int idx = (y * width + x) * 4;
                unsigned char color = isModule ? 0 : 255;
                image[idx] = color;     // R
                image[idx + 1] = color; // G
                image[idx + 2] = color; // B
                image[idx + 3] = 255;   // A
            }
        }

        unsigned error = lodepng::encode(opt.output, image, width, width);
        if (error)
        {
            throw std::runtime_error("PNG encode error: " + std::string(lodepng_error_text(error)));
        }
    }
    qrgen::core::QrCode QrEncoderLibqrencode::encode(
        const qrgen::core::Options &opt)
    {

        QRcode *raw = QRcode_encodeString(
            opt.text.c_str(),
            opt.version.get(),
            to_rec_level(opt.ecLevel),
            QR_MODE_8,
            1);

        if (!raw)
        {
            throw std::runtime_error("libqrencode: QRcode_encodeString failed");
        }

         saveToPng(raw, opt);

        qrgen::core::QrCode qr;
        qr.size = raw->width;
        qr.modules.resize(qr.size * qr.size);

        // raw->data ma width*width bajtów, każdy bit 0/1 opisuje moduł.[web:186][web:225]
        for (int y = 0; y < qr.size; ++y)
        {
            for (int x = 0; x < qr.size; ++x)
            {
                int index = y * qr.size + x;
                unsigned char v = raw->data[index];
                qr.modules[index] = (v & 0x1) != 0;
            }
        }

       

        QRcode_free(raw);
        return qr;
    };

} // namespace qrgen::infra
