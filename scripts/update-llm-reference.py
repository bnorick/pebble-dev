#!/usr/bin/env python3
"""
Downloads https://developer.repebble.com/llms.txt and all linked markdown files,
then writes a local README with relative paths.
"""

import re
import sys
from pathlib import Path
from urllib.error import URLError
from urllib.request import Request, urlopen

BASE_URL = "https://developer.repebble.com"
BASE_PATH = Path("reference/docs")
CACHE_DIR = BASE_PATH / ".cache"
README_PATH = BASE_PATH / "README.md"

# Matches markdown links like: - [Title](https://developer.repebble.com/...): description
LINK_PATTERN = re.compile(r"\((https://developer\.repebble\.com/[^)]+)\)")


def download_url(url: str, dest: Path) -> str:
    """Download content from *url* and write it to *dest*. Returns the content."""
    dest.parent.mkdir(parents=True, exist_ok=True)
    req = Request(url, headers={"User-Agent": "Mozilla/5.0"})
    try:
        with urlopen(req) as response:
            content = response.read().decode("utf-8")
    except URLError as e:
        print(f"  WARNING: Failed to download {url}: {e.reason}", file=sys.stderr)
        return ""

    dest.write_text(content, encoding="utf-8")
    return content


def uri_to_local_path(uri: str) -> Path:
    """
    Convert a developer.repebble.com URI to a local path relative to reference/docs.

    Example:
        https://developer.repebble.com/tutorials/watchface-tutorial/part6.md
        -> reference/docs/tutorials/watchface-tutorial/part6.md
    """
    # Strip the base URL to get the path component.
    path = uri.replace(f"{BASE_URL}/", "", 1)
    return BASE_PATH / path


def relative_readme_path(local_path: Path) -> str:
    """
    Return a relative path from README.md to *local_path*.

    The cache directory sits alongside README.md, so pages stored there stay in
    .cache.  Every other page lives under reference/docs, so we compute a path
    relative to reference/docs/README.md.
    """
    local = Path(local_path)
    readme_parent = README_PATH.parent

    # Pages cached in .cache keep their relative position to README.md.
    if ".cache" in local.parts:
        return str(local.relative_to(readme_parent))

    return str(local.relative_to(readme_parent))


def replace_links(content: str, downloads: dict[str, Path]) -> str:
    """Replace every developer.repebble.com link with its on-disk relative path."""

    def _replacer(match: re.Match) -> str:
        uri = match.group(1)
        local_path = downloads.get(uri)
        if local_path is None:
            return match.group(0)  # leave untouched
        rel = relative_readme_path(local_path)
        return f"({rel})"

    return LINK_PATTERN.sub(_replacer, content)


def main() -> None:
    print("Downloading llms.txt ...")
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    cache_file = CACHE_DIR / "llms.txt"
    llms_content = download_url(f"{BASE_URL}/llms.txt", cache_file)
    if not llms_content:
        print("ERROR: Could not download llms.txt", file=sys.stderr)
        sys.exit(1)

    # Collect all unique links.
    links = LINK_PATTERN.findall(llms_content)
    print(f"Found {len(links)} link(s) in llms.txt")

    # Download each linked file.
    downloads: dict[str, Path] = {}
    for i, uri in enumerate(links, 1):
        local_path = uri_to_local_path(uri)
        filename = local_path.name
        print(f"  [{i}/{len(links)}] {filename}")
        content = download_url(uri, local_path)
        if content:
            downloads[uri] = local_path

    # Write README with localised paths.
    readme_content = replace_links(llms_content, downloads)
    README_PATH.parent.mkdir(parents=True, exist_ok=True)
    README_PATH.write_text(readme_content, encoding="utf-8")
    print(f"\nWrote {README_PATH}")


if __name__ == "__main__":
    main()
