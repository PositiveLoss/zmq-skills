# CLI contract

Keep stdout machine-readable when piped; use stderr for diagnostics. Define stable
exit codes and report write failures. Do not concatenate user input into shell
commands; use argument-vector process APIs. Treat argv encoding, file paths and
terminal Unicode as platform concerns rather than assuming all bytes are UTF-8.

For integer parsing reject partial conversions, range overflow, negative values
for unsigned settings and unexpected whitespace; check errno/end pointers where
using strto* and bound the accepted domain. Use explicit lengths for binary stdin.
Never use strlen on a binary input buffer. Check fread/fwrite partial results,
ferror and EOF distinctly. Define behavior for closed pipes; handle SIGPIPE in a
POSIX adapter rather than putting it in a portable domain module.

Specify precedence: defaults, configuration, environment, command-line overrides.
Validate configuration syntax and schema, redact secrets, and bound input size.
Do not invent a configuration framework if a small explicit schema suffices.
Keep atomic replacement/durability requirements in the filesystem adapter.

For large streaming inputs use bounded chunks and a resumable parser. Test an
operand beginning with '-' via --, missing argument, repeated options and out-of-range
values. Keep help/version fast and side-effect-free. Treat completion/color as
optional interfaces whose terminal assumptions need their own tests.
