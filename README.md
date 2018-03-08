# Locales support for musl
Locale program for musl libc

This is ```/usr/bin/locale```, which works on musl libc (with limitations in musl itself).
To install, use ```cmake . && make && sudo make install``` on musl-capable distro.
English and Russian included, also .pot file.

## Build requirements:
 - musl (with developer tools)
 - gettext (with libintl and developer tools)
 - С compiler (gcc or clang recommended)
 - CMake
 - CMake backend provider (make or ninja)
 
 *For alpine, you can use this command:* ```apk add --update cmake make musl-dev gcc gettext-dev libintl```

## License

 - All translations and scripts uses [MIT](LICENSE.MIT)
 - Source files for `/usr/bin/locale` uses [LGPL](LICENSE)
