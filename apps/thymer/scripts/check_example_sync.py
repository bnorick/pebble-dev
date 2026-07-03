#!/usr/bin/env python3

from pathlib import Path
import sys


REPO_ROOT = Path(__file__).resolve().parent.parent
CANONICAL_EXAMPLE_PATH = REPO_ROOT / "examples" / "full-config.toml"
TARGETS = [
  {
    "path": REPO_ROOT / "docs" / "cookbook" / "examples.md",
    "heading": "## Full example",
    "language": "toml",
    "description": "docs full example block",
  },
]


def read_text(file_path: Path) -> str:
  return file_path.read_text(encoding="utf-8")


def normalize_text(text: str) -> str:
  return text.replace("\r\n", "\n").rstrip()


def extract_fenced_block(markdown: str, heading: str, language: str) -> str:
  lines = markdown.replace("\r\n", "\n").split("\n")

  try:
    heading_index = next(i for i, line in enumerate(lines) if line.strip() == heading)
  except StopIteration as exc:
    raise ValueError(f'Missing heading "{heading}"') from exc

  for i in range(heading_index + 1, len(lines)):
    if lines[i].strip() == f"```{language}":
      block_lines = []

      for j in range(i + 1, len(lines)):
        if lines[j].strip() == "```":
          return "\n".join(block_lines)

        block_lines.append(lines[j])

      raise ValueError(f'Unterminated {language} fenced block after "{heading}"')

  raise ValueError(f'Missing {language} fenced block after "{heading}"')


def main() -> int:
  canonical_example = normalize_text(read_text(CANONICAL_EXAMPLE_PATH))
  mismatches = []

  for target in TARGETS:
    markdown = read_text(target["path"])
    block = normalize_text(
      extract_fenced_block(markdown, target["heading"], target["language"])
    )

    if block != canonical_example:
      mismatches.append(target)

  if mismatches:
    print("full-config example is out of sync:", file=sys.stderr)
    for mismatch in mismatches:
      relative_path = mismatch["path"].relative_to(REPO_ROOT)
      print(f'- {relative_path} ({mismatch["description"]})', file=sys.stderr)
    print("", file=sys.stderr)
    print(
      "Update the checked-in example block to match examples/full-config.toml.",
      file=sys.stderr,
    )
    return 1

  print("full-config example blocks are in sync")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
