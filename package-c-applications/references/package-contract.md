# Distribution checks

Preserve CMake/Meson/Make when already adopted. For a new starter use a target-scoped
build with a required C standard and extensions disabled where portable ISO C is
intended. Distinguish host generators from target binaries. Do not execute a cross
target during configure without an appropriate emulator/runner.

Specify executable, resources, default config, mutable data and user settings
locations. Test missing/read-only locations and upgrades. Use staging destinations
for packaging and verify the installed artifact, not only a binary in build/.
On Linux inspect loader paths/RPATH and glibc baseline; on macOS inspect dylib
install names and signing requirements; on Windows inspect DLL/runtime resolution.
Do not copy developer machine paths into a release.

Choose static versus dynamic linking per dependency license, security update policy
and distribution needs. Static linking does not automatically make a fully portable
binary. Keep third-party notices and resolved dependency versions. Do not bundle
secrets, test credentials, caches or absolute build paths unnecessarily.

Keep debug symbols and crash diagnostics separate when appropriate. Produce
checksums and a dependency inventory for authorized release artifacts. Use reproducible
settings supported by the toolchain and compare repeat builds before claiming byte
reproducibility. Test clean-machine startup, --help/version, resource discovery,
configuration failure and bounded shutdown. Publishing remains within task authority.

Build reference: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html
