#include "../include/CliArgumentParser.hpp"
#include <span>
#include <iostream>
#include <charconv>
#include <optional>

namespace qrgen::cli
{
    namespace
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
    }

    class CliArgumentParser
    {

        std::optional<int> parseInt(std::string_view sv)
        {
            int value;
            auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
            if (ec == std::errc() && ptr == sv.data() + sv.size())
                return value;
            return std::nullopt;
        }

        OptionType identifyOption(const std::string_view &arg)
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

    public:
        RawOptions parse(std::span<std::string_view> args)
        {
            RawOptions options;
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
                    options.helpRequested = true;
                    break;

                case OptionType::OUTPUT:
                    if (i + 1 < args.size())
                    {
                        options.output = args[++i];
                    }
                    break;

                case OptionType::SIZE:
                    if (i + 1 < args.size())
                    {
                        options.size = parseInt(args[++i]);
                    }
                    break;

                case OptionType::FORMAT:
                    if (i + 1 < args.size())
                    {
                        options.format = args[++i];
                    }
                    break;

                case OptionType::EC_LEVEL:
                    if (i + 1 < args.size())
                    {
                        options.ecLevel = parseInt(args[++i]);
                    }
                    break;

                case OptionType::VERSION:
                    if (i + 1 < args.size())
                    {
                        options.version = parseInt(args[++i]);
                    }
                    break;

                case OptionType::MARGIN:
                    if (i + 1 < args.size())
                    {
                        options.margin = parseInt(args[++i]);
                    }
                    break;

                case OptionType::TEXT:
                    if (i + 1 < args.size())
                    {
                        options.text = args[++i];
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
                options.text = text;
            }
            else if (options.text.empty())
            {
                throw std::invalid_argument("No input text provided for QR code generation.");
            }

            return options;
        }
    };
}