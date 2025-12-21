#include <Help.hpp>
#include <iostream>

namespace qrgen::cli
{

    class CliHelp : public Help
    {

    public:
        void displayHelp() const override;
    };
}