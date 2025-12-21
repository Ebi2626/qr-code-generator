#pragma once

#include <string>
#include <optional>
#include <span>

struct RawOptions
{
    std::optional<std::string> output;
    std::optional<int> size;
    std::optional<std::string> format;
    std::optional<std::string> ecLevel;
    std::optional<int> version;
    std::optional<int> margin;
    std::string text;
    std::optional<bool> helpRequested = false;
};

namespace qrgen::cli
{

    class CliArgumentParser
    {

    public:
        virtual ~CliArgumentParser() = default;
        virtual RawOptions parse(std::span<std::string_view> args) = 0;
    };
}