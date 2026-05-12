# fnd

utility for DNF package management

---

## Compilation

```bash
make build   ( to produce the executable)
make clean   ( to delete  the executable)
make rebuild ( to delete  and reproduce the executable)
```

## Commands

### `fnd update`

Runs the full update flow:

- Checks for available updates via 
- Prompts for an local or offline update
  - **local** — local updating preforms transactions while the system is up
  - **offline** — offline updating requires a reboot, which then boots into upgrade.target and preforms transactions, (recommended for kernel, libc, systemd, drivers)
- Clears the DNF package cache only after the fourth system update
- Removes orphaned packages
- If an offline update was staged, prompts to reboot and apply (it doesn't have to be applied immeditely)

### `fnd package`

Shows available options for package analysis.

### `fnd package <flag> <package>`

Runs package analysis. Available flags:

| Flag | Description |
|------|-------------|
| `-f` | Files installed by the package |
| `-m` | Package metadata |
| `-d` | Dependencies the package requires to run |
| `-r` | Packages that require this package |
| `-o` | Package that owns a given file |

checks if package is installed, if it queries using rpm otherwise it uses dnf

**Example:**

```bash
fnd package -d bash // returns packages bash needs, example output: libc.so.6, rpmlib, rtld(GNU_HASH) 	
fnd package -o /usr/bin/ls // returns coreutils-9.10-3.fc44.x86_64 as the owner 
```
