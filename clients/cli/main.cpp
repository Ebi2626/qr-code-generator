#include <memory>
#include <string>
#include <span>
#include <IQrGeneratorService.hpp>
#include <QrGeneratorService.hpp>
#include <LibqrencodeAdapter.hpp>
#include <PngExporter.hpp>
#include "CliArgumentParser.hpp"
#include "QrCodeValidator.hpp"
#include "Help.hpp"
#include "CliHelp.hpp"

int main(int argc, char *argv[])
{
    auto encoder = std::make_shared<qrgen::adapters::LibqrencodeAdapter>();
    auto exporter = std::make_shared<qrgen::adapters::PngExporter>();

    auto service = std::make_shared<qrgen::core::services::QrGeneratorService>(
        encoder,
        exporter);

    std::unique_ptr<Help> help; 
    help = std::make_unique<CliHelp>();

    auto args = std::span<std::string_view>{argv, static_cast<size_t>(argc)};

    CliArgumentParser parser;
    auto rawOptions = parser.parse(args);

    if(rawOptions.helpRequested) {
        help->displayHelp();
    }

    QrCodeValidator validator;
    auto options = validator.validate(rawOptions);

    service->generateAndExport(
        options.text,
        options,
        options.outputPath);

    return 0;
}
