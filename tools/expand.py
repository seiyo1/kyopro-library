#!/usr/bin/env python3
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path


INCLUDE_RE = re.compile(r'^\s*#\s*include\s*([<"])([^>"]+)[>"]')
DEFAULT_REPO_ROOT = Path(__file__).resolve().parents[1]


def is_relative_to(path: Path, base: Path) -> bool:
    try:
        path.relative_to(base)
        return True
    except ValueError:
        return False


def find_repo_root(path: Path) -> Path:
    script_path = Path(__file__).resolve()
    cur = path.resolve()
    if cur.is_file():
        cur = cur.parent
    while cur != cur.parent:
        if (
            (cur / "library").is_dir()
            and (cur / "tools" / "expand.py").resolve() == script_path
        ):
            return cur
        cur = cur.parent
    return DEFAULT_REPO_ROOT.resolve()


class Expander:
    def __init__(self, repo_root: Path):
        self.repo_root = repo_root.resolve()
        self.library_root = self.repo_root / "library"
        self.included: set[Path] = set()

    def resolve_local_include(self, name: str, current_file: Path) -> Path | None:
        candidates = [
            current_file.parent / name,
            self.repo_root / "library" / name,
        ]

        for path in candidates:
            path = path.resolve()
            if (
                path.exists()
                and path.is_file()
                and is_relative_to(path, self.library_root)
            ):
                return path
        return None

    def expand_file(self, path: Path, is_entry: bool = False) -> list[str]:
        path = path.resolve()
        if not is_entry:
            if path in self.included:
                return []
            self.included.add(path)

        out: list[str] = []
        for line in path.read_text().splitlines():
            if not is_entry and line.strip() == "#pragma once":
                continue

            match = INCLUDE_RE.match(line)
            if not match:
                out.append(line)
                continue

            _, name = match.groups()

            include_path = self.resolve_local_include(name, path)
            if include_path is None:
                out.append(line)
                continue

            if include_path in self.included:
                continue

            out.append(f"// begin: {include_path.relative_to(self.repo_root)}")
            out.extend(self.expand_file(include_path))
            out.append(f"// end: {include_path.relative_to(self.repo_root)}")

        return out


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Expand local C++ #include directives into one submission file."
    )
    parser.add_argument("source", type=Path, help="Entry C++ source file")
    parser.add_argument(
        "-o", "--output", type=Path, help="Write expanded source to this file"
    )
    parser.add_argument(
        "--root",
        type=Path,
        help="Repository root. Defaults to this kyopro-library repository.",
    )
    args = parser.parse_args()

    source = args.source.resolve()
    if not source.exists():
        print(f"expand.py: source not found: {source}", file=sys.stderr)
        return 1

    repo_root = args.root.resolve() if args.root else find_repo_root(source)
    expanded = "\n".join(Expander(repo_root).expand_file(source, is_entry=True)) + "\n"

    if args.output:
        args.output.write_text(expanded)
    else:
        sys.stdout.write(expanded)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
