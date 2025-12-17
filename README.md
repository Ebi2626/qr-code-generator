# qr-code-generator
Simple app to generate QR-Codes.

## Prerequisties
To build project you will need Cmake and MSVC. Before building there is need to download dependencies via vcpkg: `vcpkg install libqrencode`

## Building
To build project .exe files there are two required steps:
- configure building files: call `cmake -S . -B build`
- build the exe file: call `cmake --build .`

## Run CLI
To run cli we have to simply call `.exe` file from terminal: `build\clients\cli\Debug\qrgen-cli.exe`