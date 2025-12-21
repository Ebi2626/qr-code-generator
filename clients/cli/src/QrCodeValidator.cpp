#include <QrCodeValidator.hpp>
#include <expected>
#include <regex>

namespace qrgen::cli
{
    const std::string DEFAULT_QR_CODE_FILE_NAME = "qrcode.png";
    const int DEFAULT_SIZE = 8;
    const qrgen::core::OutputFormat DEFAULT_OUTPUT_FORMAT = qrgen::core::OutputFormat::PNG;
    const qrgen::core::ErrorCorrectionLevel DEFAULT_EC_LEVEL = qrgen::core::ErrorCorrectionLevel::L;
    const qrgen::core::QrCodeVersion DEFAULT_VERSION = qrgen::core::QrCodeVersion(1);
    const qrgen::core::QrCodeMargin DEFAULT_MARGIN = qrgen::core::QrCodeMargin(4);

    class RawOptionsValidator
    {
        std::string trimAndSanitizeText(const std::string &text)
        {
            std::string result;
            result = std::regex_replace(result, std::regex(R"([<>:"/\\|?*])"), "");
            result = std::regex_replace(result, std::regex(R"(\s+)"), "_");
            result = std::regex_replace(result, std::regex(R"([\x00-\x1F])"), "");
            return result;
        }

        std::expected<std::string, ValidationError> validateInputText(const std::string &text)
        {
            std::string sanitizedText = trimAndSanitizeText(text);

            if (sanitizedText.empty())
            {
                return std::unexpected(ValidationError::EmptyText);
            }

            if (sanitizedText.length() > 2048)
            {
                return std::unexpected(ValidationError::TextTooLong);
            }

            return sanitizedText;
        }

        std::expected<std::string, ValidationError> validateOutputFileName(const std::optional<std::string> &output)
        {
            if (!output)
            {
                return DEFAULT_QR_CODE_FILE_NAME;
            }
            else
            {
                std::string text = *output;
                std::string sanitizedText = trimAndSanitizeText(text);

                if (sanitizedText.length() == 0)
                {
                    return DEFAULT_QR_CODE_FILE_NAME;
                }
                if (sanitizedText.length() > 200)
                {
                    return std::unexpected(ValidationError::OutputFileNameTooLong);
                }

                return sanitizedText;
            }
        }

        std::expected<int, ValidationError> validateSize(const std::optional<int> size)
        {
            if (!size)
            {
                return DEFAULT_SIZE;
            }

            int userSize = *size;

            if (userSize < 1 || userSize > 100)
            {
                return std::unexpected(ValidationError::InvalidSize);
            }
            return userSize;
        }

        std::expected<qrgen::core::OutputFormat, ValidationError> validateOutputFormat(const std::optional<std::string> &outputFormat)
        {
            if (!outputFormat)
            {
                return DEFAULT_OUTPUT_FORMAT;
            }

            std::string userOutputFormat = *outputFormat;

            if (userOutputFormat == "png" || userOutputFormat == "PNG")
                return qrgen::core::OutputFormat::PNG;
            if (userOutputFormat == "jpg" || userOutputFormat == "JPG")
                return qrgen::core::OutputFormat::JPG;
            if (userOutputFormat == "svg" || userOutputFormat == "SVG")
                return qrgen::core::OutputFormat::SVG;
            return std::unexpected(ValidationError::InvalidOutputFormat);
        }

        std::expected<qrgen::core::ErrorCorrectionLevel, ValidationError> validateErrorCorrectionLevel(const std::optional<std::string> &ecLevel)
        {
            if (!ecLevel)
            {
                return DEFAULT_EC_LEVEL;
            }

            std::string userEcLevel = *ecLevel;

            if (userEcLevel == "L" || userEcLevel == "l")
                return qrgen::core::ErrorCorrectionLevel::L;
            if (userEcLevel == "M" || userEcLevel == "m")
                return qrgen::core::ErrorCorrectionLevel::M;
            if (userEcLevel == "Q" || userEcLevel == "q")
                return qrgen::core::ErrorCorrectionLevel::Q;
            if (userEcLevel == "H" || userEcLevel == "h")
                return qrgen::core::ErrorCorrectionLevel::H;
            return std::unexpected(ValidationError::IncorrectErrorCorrectionLevel);
        }

        std::expected<qrgen::core::QrCodeVersion, ValidationError> validateVersion(std::optional<int> version)
        {
            if (!version)
                return DEFAULT_VERSION;

            int userVersion = *version;

            if (userVersion < 0 || userVersion > 40)
            {
                return std::unexpected(ValidationError::InvalidVersion);
            }

            return qrgen::core::QrCodeVersion(userVersion);
        }

        std::expected<qrgen::core::QrCodeMargin, ValidationError> validateMargin(std::optional<int> margin)
        {
            if (!margin)
                return DEFAULT_MARGIN;

            int userMargin = *margin;

            if (userMargin < 3 || userMargin > 64)
            {
                return std::unexpected(ValidationError::InvalidMargin);
            }

            return qrgen::core::QrCodeMargin(userMargin);
        }

    public:
        std::expected<qrgen::core::Options, ValidationError> validateAndTransform(const RawOptions &rawOptions)
        {
            qrgen::core::Options options;

            auto inputText = validateInputText(rawOptions.text);
            if (!inputText)
                return std::unexpected(inputText.error());

            options.text = *inputText;

            auto outputFileName = validateOutputFileName(rawOptions.output);
            if (!outputFileName)
                return std::unexpected(outputFileName.error());

            options.output = *outputFileName;

            auto size = validateSize(rawOptions.size);
            if (!size)
                return std::unexpected(size.error());

            options.size = *size;

            auto outputFormat = validateOutputFormat(rawOptions.format);
            if (!outputFormat)
                return std::unexpected(outputFormat.error());

            options.format = *outputFormat;

            auto ecLevel = validateErrorCorrectionLevel(rawOptions.ecLevel);
            if (!ecLevel)
                return std::unexpected(ecLevel.error());

            options.ecLevel = *ecLevel;

            auto version = validateVersion(rawOptions.version);
            if (!version)
                return std::unexpected(version.error());

            options.version = *version;

            auto margin = validateMargin(rawOptions.margin);
            if (!margin)
                return std::unexpected(margin.error());

            options.margin = *margin;

            return options;
        }
    };
}