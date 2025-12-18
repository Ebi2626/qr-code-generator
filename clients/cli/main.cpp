#include <memory>
#include <string>
#include <span>
#include <qrgen/ports/IQrGeneratorService.hpp>
#include <qrgen/services/QrGeneratorService.hpp>
#include <adapters/LibqrencodeAdapter.hpp>
#include <adapters/PngExporter.hpp>
#include "CliArgumentParser.hpp"

int main(int argc, char *argv[])
{
    auto encoder = std::make_shared<qrgen::adapters::LibqrencodeAdapter>();
    auto exporter = std::make_shared<qrgen::adapters::PngExporter>();

    auto service = std::make_shared<qrgen::core::services::QrGeneratorService>(
        encoder,
        exporter);

    auto args = std::span<std::string_view>{argv, static_cast<size_t>(argc)};

    CliArgumentParser parser;
    auto options = parser.parse(args);

    service->generateAndExport(
        options.text,
        options,
        options.outputPath);

    return 0;
}
