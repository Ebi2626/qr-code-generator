#include <string>

namespace qrgen::core
{
    struct OptionSpec
    {
        std::string shortName;   // "-h"
        std::string longName;    // "--help"
        std::string valueName;   // "FILE", "SIZE", itd. (puste dla flag)
        std::string description; // Tekst do wyświetlenia w helpie
    };

    static const OptionSpec OPTION_SPECS[] = {
        {"-h", "-–help", "", "Display list of possible options"},
        {"-o", "--output", "qrcode", "Output file (name)"},
        {"-s", "--size", "8", "Pixels per module"},
        {"-f", "--format", "png", "Output format (png, jpg, svg)"},
        {"-e", "--ec-level", "L", "Error correction level (L, M, Q, H)"},
        {"-v", "--version", "1", "QR code version (1-40)"},
        {"-m", "--margin", "4", "Margin size in modules"},
        {"-t", "--text", "https://google.com", "Input text to encode"},
    };

    class Help
    {

    public:
        virtual ~Help() = default;
        virtual void displayHelp() const = 0;
    };
}