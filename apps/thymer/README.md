# Thymer
> A flavorful timer.

Thymer is a highly configurable timer app specifically tuned for Pebble Time 2: moderately big text for my old eyes, touch controls, and... that's it I guess. Timer definitions are written in TOML (because it's the best), processed on the phone, and sent to the watch where they are cached.

## Installation

You can install Thymer from the [Pebble Appstore](https://apps.repebble.com/337bcb025b4e48788aa24d00) or build it yourself and install it with the the [`tasks` task runner](../../tasks) in this monorepo (recommended) or directly with `pebble` command line tool (e.g., `uv run pebble ...`) or . See the [Building & running](#building--running) section for more details.


## Documentation

The [documentation](https://bnorick.github.io/pebble-dev/thymer/guide/getting-started) covers all configuration in depth and has an array of examples.

## Building & running

Handled by the monorepo `tasks` runner,
```sh
# from monorepo root
./tasks build thymer
./tasks install <ip> thymer          # install to a paired phone

# or as a single command
./tasks install <ip> thymer --build
```

Docs site commands are also handled by `tasks`,
```sh
# from monorepo root
./tasks docs-dev thymer
```

## Target platforms

`targetPlatforms` in `package.json` controls which watches you build for. The
modern Pebble hardware is **emery** (Pebble Time 2), **gabbro** (Pebble Round
2), and **flint** (Pebble 2 Duo). I am only building for Pebble Time 2 (emery).
