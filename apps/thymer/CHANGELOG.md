# Changelog

## 1.5.0

- Changed fresh-install defaults to come from `examples/default-config.toml`, with PKJS now falling back to that bundled TOML when no saved config exists.
- Added build-time generation of a watch-side default config from `examples/default-config.toml`, so first launch no longer depends on a watch-initiated PKJS config request.
- Added build-time generation of `src/pkjs/default-config.generated.js` from `examples/default-config.toml` so the shipped default config has a single source of truth.
- Updated the default PKJS vibration intensity mappings to the tuned values now used for new users.
- Improved config-update UX on the watch: fresh installs and config reloads now immediately show a centered `Updating config...` message while the new config is loading.
- Refined the watch config notices so `Updating config...` and `Updated` now share the same stripped-down centered layout, reuse the timer background sized to the notice text, and hide button icons while shown.
- Added a bottom progress bar to the `Updating config...` screen that fills based on config messages received versus the total expected in the current update batch.
- Changed PKJS config diffing to compare normalized parsed timer configs instead of raw TOML text, so cleanup-only edits that do not change the effective watch config no longer trigger a full config update.
