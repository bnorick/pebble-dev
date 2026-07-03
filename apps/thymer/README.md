# Thymer
> A flavorful timer.

Thymer is a highly configurable timer app specifically tuned for Pebble Time 2: moderately big text for my old eyes, touch controls, and... that's it I guess. Timer definitions are written in TOML (because it's the best), processed on the phone, and sent to the watch where they are cached.

## Documentation

The [documentation](https://bnorick.github.io/pebble-dev/thymer/guide/getting-started) covers all configuration in depth and has an array of examples.

## Building & running

Handled by the monorepo `tasks` runner,
```sh
# from monorepo root
./tasks build thymer
./tasks install <ip> thymer          # install to a paired phone
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
