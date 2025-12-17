#pragma once
#include "qrgen/parseInput.hpp"
#include "qrgen/QrGenerator.hpp"
#include <iostream>
#include <regex>

namespace qrgen::cli
{
    enum class OptionType
    {
        HELP,
        OUTPUT,
        SIZE,
        FORMAT,
        EC_LEVEL,
        VERSION,
        MARGIN,
        TEXT,
        UNKNOWN
    };

    struct OptionDef
    {
        std::string shortFlag;   // "-h"
        std::string longFlag;    // "--help"
        std::string description; // "Description of the option"
        bool requiresValue;      // Information if the option needs a value
    };

    std::vector<OptionDef> availableOptions = {
        {"-h", "--help", "Display list of possible options", false},
        {"-o", "--output", "Output file (name)", false},
        {"-s", "--size", "Pixels per module", false},
        {"-f", "--format", "Output format (png, svg, etc.)", false},
        {"-e", "--ec-level", "Error correction level (L, M, Q, H)", false},
        {"-v", "--version", "QR code version (1-40)", false},
        {"-m", "--margin", "Margin size in modules", false},
        {"-t", "--text", "Input text to encode", true}};

    namespace
    {
        void displayMenu()
        {
            std::cout << "Available options:\n";
            for (const auto &option : availableOptions)
            {
                std::cout << "  " << option.shortFlag << ", " << option.longFlag
                          << ": " << option.description << "\n";
            }
        }

        OptionType identifyOption(const std::string &arg)
        {
            if (arg == "-h" || arg == "--help")
                return OptionType::HELP;
            if (arg == "-o" || arg == "--output")
                return OptionType::OUTPUT;
            if (arg == "-s" || arg == "--size")
                return OptionType::SIZE;
            if (arg == "-f" || arg == "--format")
                return OptionType::FORMAT;
            if (arg == "-e" || arg == "--ec-level")
                return OptionType::EC_LEVEL;
            if (arg == "-v" || arg == "--version")
                return OptionType::VERSION;
            if (arg == "-m" || arg == "--margin")
                return OptionType::MARGIN;
            if (arg == "-t" || arg == "--text")
                return OptionType::TEXT;
            return OptionType::UNKNOWN;
        }

        qrgen::core::OutputFormat parseFormat(const std::string &str)
        {
            if (str == "png" || str == "PNG")
                return qrgen::core::OutputFormat::PNG;
            if (str == "jpg" || str == "JPG")
                return qrgen::core::OutputFormat::JPG;
            if (str == "svg" || str == "SVG")
                return qrgen::core::OutputFormat::SVG;
            throw std::invalid_argument("Unknown format: " + str);
        }

        qrgen::core::ErrorCorrectionLevel parseEcLevel(const std::string &str)
        {
            if (str == "L" || str == "l")
                return qrgen::core::ErrorCorrectionLevel::L;
            if (str == "M" || str == "m")
                return qrgen::core::ErrorCorrectionLevel::M;
            if (str == "Q" || str == "q")
                return qrgen::core::ErrorCorrectionLevel::Q;
            if (str == "H" || str == "h")
                return qrgen::core::ErrorCorrectionLevel::H;
            throw std::invalid_argument("Invalid EC level: " + str);
        }

        std::string parseOutput(const std::string &str)
        {
            if (str.empty())
                return "qrcode.png";

            std::string result = str;

            result = std::regex_replace(result, std::regex(R"([<>:"/\\|?*])"), "");
            result = std::regex_replace(result, std::regex(R"(\s+)"), "_");
            result = std::regex_replace(result, std::regex(R"([\x00-\x1F])"), "");

            if (result.empty())
                return "qr_code";
            if (result.size() > 255)
                std::cout << "Warning: Output filename too long, truncating to 255 characters.\n";
            result = result.substr(0, 255);

            return result;
        }

        int parseSize(const int size)
        {
            if (size < 1 || size > 100)
            {
                throw std::out_of_range("Size must be between 1 and 100");
            }
            return size;
        }

        std::string parseText(const std::string &str)
        {
            if (str.size() < 1 || str.size() > 2048)
            {
                throw std::out_of_range("Text length should be between 1 and 2048 characters");
            }
            return str;
        }

    }

    qrgen::core::Options parseInput(const std::vector<std::string> &args)
    {
        qrgen::core::Options options;
        std::string text = "";
        bool hasText = false;

        for (size_t i = 1; i < args.size(); ++i)
        {
            const auto &arg = args[i];

            if (arg[0] != '-')
            {
                text = arg;
                continue;
            }

            switch (identifyOption(arg))
            {
            case OptionType::HELP:
                displayMenu();
                break;

            case OptionType::OUTPUT:
                if (i + 1 < args.size())
                {
                    options.output = parseOutput(args[++i]);
                }
                break;

            case OptionType::SIZE:
                if (i + 1 < args.size())
                {
                    options.size = parseSize(std::stoi(args[++i]));
                }
                break;

            case OptionType::FORMAT:
                if (i + 1 < args.size())
                {
                    options.format = parseFormat(args[++i]);
                }
                break;

            case OptionType::EC_LEVEL:
                if (i + 1 < args.size())
                {
                    options.ecLevel = parseEcLevel(args[++i]);
                }
                break;

            case OptionType::VERSION:
                if (i + 1 < args.size())
                {
                    options.version = qrgen::core::QrCodeVersion(std::stoi(args[++i]));
                }
                break;

            case OptionType::MARGIN:
                if (i + 1 < args.size())
                {
                    options.margin = qrgen::core::QrCodeMargin(std::stoi(args[++i]));
                }
                break;

            case OptionType::TEXT:
                if (i + 1 < args.size())
                {
                    options.text = parseText(args[++i]);
                    hasText = true;
                }
                break;

            case OptionType::UNKNOWN:
                std::cerr << "Unknown option: " << arg << "\n";
                break;
            }
        }

        if (!hasText && !text.empty())
        {
            options.text = parseText(text);
        }
        else if (options.text.empty())
        {
            throw std::invalid_argument("No input text provided for QR code generation.");
        }

        return options;
    }
}