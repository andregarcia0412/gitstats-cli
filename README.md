<h1 align="center">
  <img
    src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=55&duration=3000&pause=1000&color=58A6FF&center=true&vCenter=true&width=900&height=100&lines=GitStats+CLI"
    alt="Typing SVG"
  />
</h1>

<p align="center">
  <a href="https://isocpp.org/"><img alt="C++17" src="https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white"></a>
  <a href="https://www.gnu.org/software/make/"><img alt="Makefile build" src="https://img.shields.io/badge/build-Makefile-1f6feb?logo=gnu&logoColor=white"></a>
</p>

## Summary
GitStats CLI is a lightweight C++ tool that uses the GitHub GraphQL API to show user language distribution, user info, and repository info directly from the command line.

## Stack
- C++17
- libcurl (HTTP)
- nlohmann/json (header-only)
- Makefile build

## Table of Contents
- [Summary](#summary)
- [Stack](#stack)
- [Run Locally](#run-locally)
- [Build (Linux/macOS/Windows)](#build-linuxmacoswindows)
- [Usage](#usage)
- [Documentation](#documentation)

## Run Locally
**Prerequisites**
- C++17 compiler (g++)
- make
- libcurl development headers

**Build and run**
```bash
make
./bin/gitstats help
```

**Optional install**
```bash
make install
# After install
 gitstats help
```

## Build (Linux/macOS/Windows)
The Makefile builds to `bin/gitstats` (or `bin/gitstats.exe` on Windows) and provides install/uninstall targets.

**Linux/macOS**
```bash
make
make install
```

- Output: `bin/gitstats`
- Install dir: `~/.local/bin`

**Windows (MSYS2/MinGW or similar)**
```bash
make
make install
```

- Output: `bin/gitstats.exe`
- Install dir: `%USERPROFILE%/AppData/Local/Programs/gitstats`

**Clean build artifacts**
```bash
make clean
```

**Uninstall**
```bash
make uninstall
```

## Usage
```text
gitstats <command> [options]
```

**Commands**
```text
help                                Show this help message
config <option>                     Manage local config
user <option> <user>                GitHub user operations
repository <option> <owner> <repo>  GitHub repository operations
languages <user>                    Alias for: gitstats user --languages <user>
```

**User options**
```text
--languages, --langs <user>         Show top languages for a GitHub user
--info <user>                       Show GitHub user info
```

**Config options**
```text
--set-token <token>                 Set GitHub token in config file
--remove-token                      Remove token from config file
--list                              List config values
```

**Repository options**
```text
--info <owner> <repo>               Show GitHub repository info
```

**Examples**
```bash
gitstats help
gitstats config --set-token ghp_xxxxx
gitstats config --list
gitstats config --remove-token
gitstats user --languages torvalds
gitstats user --info torvalds
gitstats repository --info torvalds linux
gitstats languages torvalds
```

**Notes**
- A GitHub token is required for GraphQL API calls.
- Config file location: `./.config/config.json`.
- Forked repositories are ignored.
- "Jupyter Notebook" language is excluded.

## Documentation
All documentation is available via the CLI help:
```bash
gitstats help
```

The help output includes the full command list, options, and examples.
