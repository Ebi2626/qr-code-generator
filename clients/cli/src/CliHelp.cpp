#include <Help.hpp>
#include <iostream>

namespace qrgen::cli
{
    class CliHelp
    {

    public:
        void displayHelp() const
        {
            std::cout << "Usage: qrgen [options]";
            std::cout << "Options:";
            for (const auto &opt : qrgen::core::OPTION_SPECS)
            {
                std::cout << opt.shortName << " ";
                std::cout << opt.longName << " ";
                std::cout << opt.valueName.empty() ? "" : " " + opt.valueName;
                std::cout << opt.description + "\n";
            }
        };
    };
}