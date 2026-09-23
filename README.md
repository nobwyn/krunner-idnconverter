# Krunner IDN Converter

A small KRunner plugin (Plasma 6) for converting domain names between IDN and ACE formats.

## Usage

Open Krunner and enter a domain name - IDN and ACE formats of it will be shown in the search results:

![Demo1](https://raw.githubusercontent.com/nobwyn/krunner-idnconverter/master/img/demo1.png)
![Demo2](https://raw.githubusercontent.com/nobwyn/krunner-idnconverter/master/img/demo2.png)

Hitting ENTER will copy the selected format to the clipboard.

## Installation

Requirements: CMake, Extra CMake Modules, Qt 6, KDE Frameworks 6 (KRunner, KI18n) and the [ICU library](https://icu.unicode.org/).

Build and install:

```sh
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
cmake --build build
sudo cmake --install build
```

Run the tests (optional): `ctest --test-dir build`

Restart KRunner: `kquitapp6 krunner`. It starts again the next time you open it.

Make sure the new plugin is enabled in the KRunner settings and you're ready to go!

## License

The Krunner IDN Converter is licensed under the [MIT license](LICENSE).
