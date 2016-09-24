# KRunner IDN Converter

A small Krunner plugin (Plasma 5) for converting domain names between IDN and ACE formats.

## Usage

Open Krunner and enter a domain name - IDN and ACE formats of it will be shown in the search results:

![Demo1](https://raw.githubusercontent.com/laimoncijus/krunner-idnconverter/master/img/demo1.png)
![Demo2](https://raw.githubusercontent.com/laimoncijus/krunner-idnconverter/master/img/demo2.png)

Hitting ENTER will copy the selected format to the clipboard.

## Installation

Make sure you have the [ICU library](http://www.icu-project.org/) installed on your machine.

Run the build script: `build.sh`

On success - run the `install.sh` to install the plugin (you'll be asked for a password to install it on the system).

Restart the Krunner: `kquitapp5 krunner && krunner &`

Make sure the new plugin is enabled in Krunner settings and you're ready to go!

## License

The Krunner IDN Converter is licensed under the [MIT license](LICENSE).
