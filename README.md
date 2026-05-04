# fnd

A small helper utility for DNF package management system

---

## Compilation

```bash
make build
```

## Commands

### `fnd update`

Runs the full update workflow:

- Checks for available updates via `dnf check-update`
- Prompts for an online or offline update
  - **online** — applies updates immediately
  - **offline** — stages updates to be applied on next reboot (recommended for kernel, libc, systemd, mesa)
- Clears the DNF package cache
- Removes orphaned packages via `dnf autoremove`
- If an offline update was staged, prompts to reboot and apply

### `fnd package`

Shows available options for package analysis.

### `fnd package <flag> <package>`

Runs package analysis. Available flags:

| Flag | Description |
|------|-------------|
| `-i` | Files installed by the package |
| `-m` | Package metadata |
| `-d` | Dependencies the package requires to run |
| `-r` | Packages that require this package |
| `-o` | Package that owns a given file |

**Example:**

```bash
fnd package -d bash
fnd package -o /usr/bin/ls
```
