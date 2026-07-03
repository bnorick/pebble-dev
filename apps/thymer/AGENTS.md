# Repository Guidelines

## Project Structure & Module Organization
`src/c/thymer.c` contains the watch app runtime: config ingestion, persistence, timer logic, wakeups, gestures, and UI. `src/pkjs/pebble-js-app.js` contains the phone-side settings UI, TOML parsing, normalization, and AppMessage transport. The timer config docs site lives in `docs/` and is built with VitePress. Use `examples/full-config.toml` as the reference config; keep it valid against the live PKJS parser, not just the README prose. Treat `build/` as generated output. Project metadata lives in `package.json`, and Pebble build rules live in `wscript`.

## Reference Material
Shared reference material lives in `../../reference`. Use `../../reference/c` and `../../reference/docs` for Pebble SDK behavior, drawing, animation, and API details before inventing app-local patterns. `../../reference/alloy` is only relevant when comparing against JS-first Pebble apps.

High-quality reference apps live in `../../reference/apps`, you can review `../../reference/apps/AGENTS.md` for a guide to which apps are good references for which needs.

## Build, Test, and Development Commands
Run commands from the repository root.

- `pebble build` builds the app for the platforms listed in `package.json` (`emery`, `gabbro`).
- `pebble install --emulator emery` installs the current build into the Emery emulator.
- `pebble install --phone <ip>` pushes the app to a paired phone for device testing.
- `pebble clean` removes generated build artifacts before a fresh rebuild.
- `npm run docs:dev` starts the local VitePress docs server on `127.0.0.1`.
- `npm run docs:build` builds the static docs site into `docs/.vitepress/dist`.
- `npm run docs:preview` previews the built docs site locally on `127.0.0.1`.

If you rename PKJS entry files, update `wscript` so `js_entry_file` matches the actual source.

Practical notes learned from this repo:

- `pebble build` may fail in restricted sandboxes because the Pebble SDK writes analytics and settings files under `~/.pebble-sdk`. If the error mentions `pending_analytics.json` or `settings.json`, rerun with permissions that allow writes there.
- `npm run docs:build` is the fastest validation pass for docs changes and should stay green before shipping docs edits.
- The docs dev and preview commands intentionally bind to `127.0.0.1` rather than `0.0.0.0` because the Vite/VitePress dependency chain currently carries unresolved dev-server advisories.
- The GitHub Pages workflow for this app lives at the git repo root, not inside this app directory: `../../.github/workflows/thymer-docs.yml`.
- GitHub Pages is configured for the monorepo path `/pebble-dev/`; if the repo name changes, update `docs/.vitepress/config.mts` `base` and the PKJS docs link in `src/pkjs/config.js`.

## Coding Style & Naming Conventions
Follow the existing style: 2-space indentation in C and JS, K&R-style braces, and short static helpers in C prefixed with `prv_`. Global/static state uses the `s_` prefix. Prefer `camelCase` for JS functions and `ALL_CAPS` for constants. Keep Pebble-facing limits explicit with named constants such as `MAX_TIMERS` and `MAX_SEGMENTS`.

## Testing Guidelines
There is no automated test suite in this app today. Minimum validation for changes is:

- `pebble build` with no warnings introduced by your change
- emulator install on at least `emery`
- manual config import using `examples/full-config.toml`
- for docs changes, `npm run docs:build`

For behavior changes, verify both watch-side flow and PKJS config delivery, especially persistence, AppMessage sequencing, and gesture triggers. For config-format changes, also verify that `examples/full-config.toml` still parses under the live PKJS parser and that the docs pages in `docs/` reflect the current parser behavior.

## Commit & Pull Request Guidelines
Recent history uses short, imperative subjects such as `Update docs` and `Restructure monorepo`. Keep commit titles concise and descriptive; avoid leaving `WIP` commits in review branches. PRs should explain the user-visible change, note tested platforms (`emery`, `gabbro`), and include screenshots or brief UI notes when watch screens change. Link related issues and call out config-format or persistence compatibility impact.
