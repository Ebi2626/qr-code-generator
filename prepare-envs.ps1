# Ustawia zmienne srodowiskowe VCPKG_ROOT i CMAKE_TOOLCHAIN_FILE jako trwale (User).

# --- 1. Konfiguracja Sciezek (KONIECZNIE Zmien Ponizsza Sciezke!) ---
# Upewnij sie, ze ta sciezka WSKAZUJE na katalog glowny Twojego vcpkg
$VCPKG_ROOT_PATH = "D:\dev\vcpkg" 

# Sciezka do pliku toolchain vcpkg (automatycznie konstruowana)
$TOOLCHAIN_FILE_PATH = "$VCPKG_ROOT_PATH\scripts\buildsystems\vcpkg.cmake"


# --- 2. Sprawdzenie, czy katalog vcpkg istnieje ---
Write-Host "Weryfikacja sciezki VCPKG_ROOT..."
if (-not (Test-Path -Path $VCPKG_ROOT_PATH -PathType Container)) {
    Write-Error "Blad: Katalog VCPKG_ROOT nie istnieje pod sciezka: '$VCPKG_ROOT_PATH'. Zmien sciezke w skrypcie."
    exit 1
}


# --- 3. Ustawienie Zmiennej Srodowiskowej VCPKG_ROOT (na poziomie Uzytkownika) ---

Write-Host "Ustawianie zmiennej VCPKG_ROOT na poziomie Uzytkownika..."

[Environment]::SetEnvironmentVariable("VCPKG_ROOT", $VCPKG_ROOT_PATH, "User")

Write-Host "VCPKG_ROOT ustawiono na: $VCPKG_ROOT_PATH"


# --- 4. Ustawienie Zmiennej Srodowiskowej CMAKE_TOOLCHAIN_FILE (na poziomie Uzytkownika) ---

Write-Host "Ustawianie zmiennej CMAKE_TOOLCHAIN_FILE na poziomie Uzytkownika..."

[Environment]::SetEnvironmentVariable("CMAKE_TOOLCHAIN_FILE", $TOOLCHAIN_FILE_PATH, "User")

Write-Host "CMAKE_TOOLCHAIN_FILE ustawiono na: $TOOLCHAIN_FILE_PATH"

Write-Host ""
Write-Host "### Konfiguracja zakonczona pomyslnie! ###"
Write-Host "Aby zmiany weszly w zycie, MUSISZ ponownie uruchomic terminale i IDE."