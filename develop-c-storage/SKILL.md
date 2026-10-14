---
name: develop-c-storage
description: "Develop persistence for C applications using SQLite or an existing native database client such as libpq. Use for prepared statements, connection/statement ownership, transactions, migrations, durability, busy/retry policy and application idempotency."
---

# C Storage Applications

1. Inspect storage type, concurrency, durability, failure/recovery and migration requirements. Read [application-contract.md](references/application-contract.md).
2. Read [storage-contract.md](references/storage-contract.md). Define connection owners, statement lifetimes, transaction boundaries and schema/version policy.
3. Implement parameterized queries and explicit commit/rollback outcomes. Move blocking database work off latency-sensitive loops with bounded admission.
4. Add applicable crash/busy/disk-full/schema migration and replay tests; distinguish a mocked database test from native integration.
5. Deliver the schema, ownership/error contract, migration/recovery procedure, resolved client dependencies and actual database evidence.
