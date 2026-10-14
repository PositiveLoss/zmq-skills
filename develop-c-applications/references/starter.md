# Adapt the C application starter

Use assets/c-app as a dependency-free C11 composition example: a pure binary codec,
a CLI adapter, a semantic unit test target and target-scoped CMake configuration.
It is a fixture, not a production business application or a network service.
The CAPP wire format is independent of the ZeroMQ multipart example.

Compile without CMake where only a C compiler is available:

```sh
cc -std=c11 -Wall -Wextra -Werror -pedantic -Iassets/c-app/include assets/c-app/src/app.c assets/c-app/src/main.c -o capp
cc -std=c11 -Wall -Wextra -Werror -pedantic -Iassets/c-app/include assets/c-app/src/app.c assets/c-app/tests/test_app.c -o test_app
./test_app
./capp --help
./capp 'hello'
```

With a supported CMake toolchain:

```sh
cmake -S assets/c-app -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
cmake --install build --prefix /chosen/staging/directory
```

The codec returns a borrowed payload view; retain the source frame until the view
is no longer used. The encoder requires nonoverlapping input/output buffers.
Tests cover independent golden bytes, embedded NUL, empty payload, truncation,
length mismatch, oversize, version/magic rejection and unchanged outputs on errors.
For sanitizers use a separate supported build with -fsanitize=address,undefined
and link those flags as well. Do not claim speed from an instrumented binary.
