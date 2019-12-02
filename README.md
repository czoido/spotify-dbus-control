# spotify-dbus-control
Basic example on how to consume dbus-asio to control spotify using dbus

## Compiling the example

```
mkdir build && cd build
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/dbus-control
```