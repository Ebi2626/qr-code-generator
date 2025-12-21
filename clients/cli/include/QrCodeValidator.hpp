#include <expected>
#include <string>
#include <CliArgumentParser.hpp>
#include "../core/domain/QrCodeOptions.hpp"

namespace qrgen::cli
{
    enum class ValidationError
    {
        EmptyText,
        TextTooLong,
        OutputFileNameTooLong,
        InvalidOutputFormat,
        IncorrectErrorCorrectionLevel,
        InvalidVersion,
        InvalidMargin,
        InvalidOutputPath,
        InvalidSize
    };

    std::string_view errorMessage(ValidationError err)
    {
        using enum ValidationError;
        switch (err)
        {
        case EmptyText:
            return "Text to encode cannot be empty";
        case TextTooLong:
            return "Exceeded maximum text length - 2048";
        case OutputFileNameTooLong:
            return "Exceeded maximum output file name - 300";
        case InvalidOutputFormat:
            return "Invalid output format available options are: jpg, png, svg";
        case IncorrectErrorCorrectionLevel:
            return "Invalid error correction level, available options are: l, m, q, h";
        case InvalidVersion:
            return "Version must be in range 1-40";
        case InvalidMargin:
            return "QR Code margin must be 3-64";
        case InvalidOutputPath:
            return "Ścieżka wyjściowa jest niepoprawna lub niedostępna.";
        case InvalidSize:
            return "Size must be in range 1-100";
        }

        return "Nieznany błąd walidacji."; // safety fallback
    }

    class RawOptionsValidator
    {

    public:
        virtual ~RawOptionsValidator() = default;
        virtual std::expected<qrgen::core::Options, ValidationError> validateAndTransform(const RawOptions &rawOptions) = 0;
    };
}