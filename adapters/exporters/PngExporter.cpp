#include "PngExporter.hpp"
#include <lodepng.h>

namespace qrgen::adapters::exporters {

void PngExporter::exportToFile(
    const qrgen::core::QrCode& qrCode,
    const std::string& filename,
    int pixelSize,
    int margin
) {
    auto bytes = exportToBytes(qrCode, pixelSize, margin);
    int totalSize = (qrCode.size * pixelSize) + (2 * margin);
    
    unsigned error = lodepng::encode(
        filename, 
        bytes.data(), 
        totalSize, 
        totalSize
    );
    
    if (error) {
        throw std::runtime_error("PNG export failed");
    }
}

}
