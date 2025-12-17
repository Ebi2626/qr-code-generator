#pragma once
#include "qrgen/QrEncoderLibqrencode.hpp"
#include <iostream>
#include "qrgen/parseInput.hpp"

/* Stanowi wejście do aplikacji i warstwę prezentacji  
* Wywołuje elementy z katalogu core - gdzie znajduje się logika biznesowa
* Powinna być cienkim wrapperem nad core
* Powinna udostępniać interfejs użytkownika (np. CLI, GUI, API itp.)
* Nie powinna wykonywać żadnych elementów logiki biznesowej ani dostępu do danych
* Powinna być odpowiedzialna za interakcję z użytkownikiem i prezentację
*/


int main(int argc, char* argv[]) {
    qrgen::infra::QrEncoderLibqrencode encoder;
    qrgen::core::Options opt{};

    std::vector<std::string> args(argv, argv + argc);
    qrgen::core::Options options = qrgen::cli::parseInput(args);
    encoder.encode(options);
}
