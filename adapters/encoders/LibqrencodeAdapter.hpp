#pragma once
#include <string>
#include <memory>

namespace qrgen::adapters::encoders
{
    class LibqrencodeAdapter
    {

        public:
        virtual ~LibqrencodeAdapter() = default;
        virtual std::unique_ptr<domain::QrCode> encode (
            const std::string &text,
            const domain::QrCodeOptions &options) = 0;
    }

}