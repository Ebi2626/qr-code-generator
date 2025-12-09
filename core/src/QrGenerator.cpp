#include "QrGenerator.hpp"

namespace qrgen::core {

QrCode QrGenerator::generate(const std::string& text, const Options&) {
    const int n = 21; // przykładowy rozmiar dla wersji 1
    QrCode qr{n, std::vector<bool>(n * n, false)};

    // placeholder: zakoloruj przekątną żeby było widać, że coś działa
    for (int i = 0; i < n; ++i) {
        qr.modules[i * n + i] = true;
    }
    return qr;
}

} // namespace qrgen::core
