#pragma once 
#include <lodepng.h>

namespace qrgen::adapters::exporters {

void PngExporter::exportToFile(
    const domain::QrCode& qrCode,
    const std::string& filename,
    int pixelSize,
    int margin
) = 0;

}
