#include <IQrGeneratorService.hpp>

namespace qrgen::core::services {

QrGeneratorService::QrGeneratorService(
    std::shared_ptr<ports::IQrEncoder> encoder,
    std::shared_ptr<ports::IQrExporter> exporter
) : encoder_(encoder), exporter_(exporter) {}

std::unique_ptr<domain::QrCode> QrGeneratorService::generateQrCode(
    const std::string& text,
    const domain::QrCodeOptions& options
) {
    validateInput(text, options);
    return encoder_->encode(text, options);
}

void QrGeneratorService::generateAndExport(
    const std::string& text,
    const domain::QrCodeOptions& options,
    const std::string& outputPath
) {
    auto qrCode = generateQrCode(text, options);
    exporter_->exportToFile(*qrCode, outputPath, options.pixelSize, options.margin);
}

}
