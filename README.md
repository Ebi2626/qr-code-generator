# qr-code-generator
Simple app to generate QR-Codes.

![Przykładowy QR](repo.png)

## Prerequisties
To build project you will need Cmake and MSVC. Before building there is need to download dependencies via vcpkg: `vcpkg install libqrencode lodepng`

## Building
To build project .exe files there are two required steps:
- configure building files: call `cmake -S . -B build`
- build the exe file: call `cmake --build .`

## Run CLI
To run cli we have to simply call `.exe` file from terminal: `build\clients\cli\Debug\qrgen-cli.exe https://edwinharmata.pl` <- this will return qr-code.png in current catalog to my website. Avialable CLI options are:
- `-h`, `--help` - display list of possible options
- `-o`, `--output` - Output file (name)
- `-s`, `--size` - Pixels per module
- `-f`, `--format` - Output format (png, svg, etc.)
- `-e`, `--ec-level` - Error correction level (L, M, Q, H)
- `-v`, `--version` - QR code version (1-40)
- `-m`, `--margin` - Margin size in modules
- `-t`, `--text` - Input text to encode

