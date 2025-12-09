# Idea

Simple desktop app to generate custom static qr-codes in different styles and possibility to adjust qr-code style to our needs.

## Architecture

Application has been built with multilayer architecture to allow users to use it in both ways: as an CLI and as an Desktop app with GUI. The main structure of the code constists:
- Core - pure logic changing given string into qr-code
- Infrastructure - adapters to connect our `Core` to different clients
- Clients - our CLI and GUI logic

## Technology
Application has been prepared in C++ with Visual Studio 2022.

### Note
- In the ide there is configuration for `includePath` with two positions:
    - `"${workspaceFolder}/**"`,
    - `"${workspaceFolder}/core/include"`