# A C++ library for serial ports that takes care of concurrency

## Contributors

* [Emil Fresk](https://www.github.com/korken89)

---

## License

Licensed under the Boost Software License 1.0, see LICENSE file for details.

---

Port of the serial pipe class form C#, dependent of the "serial" library.

* Header only library, copy `serialpipe.hpp` into your project.
* Simple to use, see example file.
* Dependency on https://github.com/wjwwood/serial
* Compile example: `g++ example.cpp -o test -std=c++14 -pthread -lserial`
