---
name: package-c-applications
description: "Build and package standalone C applications for their supported platforms. Use for executable installation, native library discovery, cross toolchains, runtime dependencies, symbol/debug artifacts, packaging metadata and clean-machine smoke tests."
---

# Package C Applications

1. Inspect target platforms/architectures, distribution model and minimum compiler/OS/library baselines. Read [application-contract.md](references/application-contract.md).
2. Read [package-contract.md](references/package-contract.md). Define install layout, runtime dependency and licensing policy before changing the build.
3. Build release/debug variants with target-scoped flags, proper cross toolchains and explicit dependency discovery. Preserve source/runtime compatibility.
4. Stage installation in an empty prefix and run the installed application outside its source/build tree. Test native dependency resolution on each claimed target.
5. Deliver reproducible build/install commands, checksums/artifacts when authorized, symbol files, dependency versions and remaining platform gaps.
