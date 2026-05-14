# fnd

utility for DNF

---

## Compilation

```bash
make build   # (to produce the executable)
make clean   # (to delete  the executable)
make rebuild # (to delete  and reproduce the executable)
```

## Commands

```bash
fbd update
```

Runs the full update flow:

- Checks for available updates 
- Prompts for a local or an offline update
  - **local** — local updating preforms transactions while the system is up
  - **offline** — offline updating requires a reboot, which then boots into upgrade.target and preforms the transactions (recommended for kernel, libc, systemd and drivers)
- Clears the DNF package cache only after the fourth full system update 
- Removes orphaned packages
- If an offline update was staged, prompts to reboot and apply (it doesn't have to be applied immeditely)

---

```bash
fnd package <flag> <package>
```

## Available flags:


| Flag | Description |
|------|-------------|
| `-f` | Files this package installs |
| `-m` | Package metadata |
| `-d` | Dependencies the package requires to run |
| `-r` | Packages that require it |
| `-o` | Package that owns a given file |


**The system first checks if the package is installed, if it is, it queries using rpm otherwise it uses dnf**

---

**Example:**

```bash
fnd package -d bash # returns packages bash needs, example output: libc.so.6, rpmlib, rtld	
fnd package -o /usr/bin/ls # returns coreutils-9 as the owner 
```
