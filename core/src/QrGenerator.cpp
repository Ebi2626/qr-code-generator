#include "qrgen/QrGenerator.hpp"

/* 
* Reprezentuje warstwę logiki biznesowej
* Powinna zawierać główne reguły biznesowe i logikę aplikacji
* Powinna przekazywać do adapterów biblioteki znajdującej się w warstwie infrastruktury
* komendy do generowania kodów QR
* Nie powinna zawierać żadnych elementów interfejsu użytkownika ani dostępu do danych
*/

/*
Reguły do zaimplementowania:
- Generowanie kodu QR na podstawie podanego tekstu i opcji
- Obsługa różnych poziomów korekcji błędów
- Obsługa różnych wersji kodów QR
- Walidacja wejściowych danych tekstowych
- Zarządzanie pamięcią i zasobami związanymi z generowaniem kodów QR
- Optymalizacja wydajności generowania kodów QR
*/

namespace qrgen::core {

QrCode QrGenerator::generate(const std::string& text, const Options&) {
    const int n = 21; // przykładowy rozmiar dla wersji 1
    QrCode qr{n, std::vector<bool>(n * n, false)};

    // placeholder: zakoloruj przekątną żeby było widać, że coś działa
    for (int i = 0; i < n; ++i) {
        qr.modules[i * n + i] = true;
    }
    return qr;
}

} // namespace qrgen::core
