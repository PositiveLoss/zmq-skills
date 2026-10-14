# Desktop lifecycle

Use the project's existing toolkit. For a new C UI consider GTK only after checking
target OS integration, distribution size, accessibility and required API baseline.
Do not infer native appearance or deployment compatibility from a successful Linux
build. GTK major versions have distinct APIs; verify the pinned baseline.

Keep application/domain state outside widgets; represent loading, ready, failure
and cancellation explicitly. Most GTK operations belong on its designated main
thread. Marshal background results through the supported main-context path; do
not treat generic GLib thread support as permission to mutate GTK widgets anywhere.
Bound pending work and retained result bytes so a responsive UI cannot accumulate
an unlimited backlog.

Track callback closures, GObject references, signal connections, timer/source IDs,
and borrowed widget pointers. On window disposal cancel/detach sources and prevent
late results from touching dead views. Keep owned result state until its completion
has been observed. Avoid callbacks whose retained parent reference forms a cycle.
Inspect transfer/ownership annotations of each API rather than universally unrefing
every returned pointer.

Provide keyboard actions, focus order, readable errors and accessibility names.
Define binary/text/file-path encoding at adapters. Persist settings with explicit
schema and error handling; do not block the UI on database or network operations.
Test core logic headlessly and report manual/automated UI checks separately.

Primary sources:
- https://docs.gtk.org/gtk4/
- https://docs.gtk.org/glib/threads.html
