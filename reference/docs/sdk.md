# Installing the Pebble SDK

Source: https://developer.repebble.com/sdk/

The easiest way to start building a Pebble watchface or app is with [CloudPebble](https://cloudpebble.repebble.com) - no installation required. It runs entirely in your browser!

Otherwise, if you are somewhat command-line knowledgeable, you can follow the instructions below to install the SDK locally on your computer.

## Install dependencies

#### MacOS

You will need to install Node.js. The easiest way is with [Homebrew](https://brew.sh/):

```
brew install node
```

#### Ubuntu

You will need to install a few dependencies to make the SDK run:

```
sudo apt install nodejs npm libsdl2-2.0-0 libglib2.0-0 libpixman-1-0 zlib1g libsndio7.0
```

> Note: if you already have `node` installed, you can install only:

```
sudo apt install libsdl2-2.0-0 libglib2.0-0 libpixman-1-0 zlib1g libsndio7.0
```

#### Fedora

```
sudo dnf install nodejs SDL2 glib2 pixman zlib
```

#### Windows

The Pebble SDK does not run on Windows, but you can use WSL. Install Ubuntu in WSL, and then use the instructions above to install dependencies.

## Download the Pebble CLI

Install [uv](https://docs.astral.sh/uv/getting-started/installation/), a fast package manager for Python.

Then, run:

```
uv tool install pebble-tool --python 3.13
```

> Note: pebble-tool requires Python 3.10, 3.11, 3.12, or 3.13 (higher than 3.9 and lower than 3.14).

## Next Steps

Now that you have the Pebble SDK downloaded and installed on your computer, it is time to create your first app!

#### Create a Pebble app

Install the latest SDK:

```
pebble sdk install latest
```

Create a project (for example, called myproject):

```
pebble new-project myproject
```

Compile the project (after `cd`ing to your project directory):

```
pebble build
```

Install the app on an emulator for the Pebble Time:

```
pebble install --emulator basalt
```

Or, install the app/watchface on your phone.

Requires the new Pebble mobile app (install at [rePebble.com/app](https://repebble.com/app)) -\> go to Devices -\> tap 3 dots -\> Enable Dev Connect -\> Sign into GitHub. Then back on your computer, run

```
pebble login # Sign into GitHubpebble install --cloudpebble
```

#### Learn more

The best way to learn is by checking out our examples apps: [weather](https://github.com/pebble-examples/pebblekit-js-weather/), [simple game](https://github.com/pebble-hacks/pandas-and-bananas/), [concentricity watchface](https://github.com/pebble-examples/concentricity/), and [many more](/examples.md)! Or try [tutorials](/tutorials.md) for a step-by-step guide on how to write a simple C Pebble application.

### Installation Problems?

Check the [FAQ](/faqs.md) first - common install, emulator, and `pebble` tool errors are answered there.

If you're still stuck, ask on the [Pebble Developer Forum](https://forum.repebble.com/c/developers-ask-questions-and-get-help/7) or in `#sdk-dev` on the[Rebble Discord](https://discord.com/invite/aRUAYFN). Please provide as many details as you can about the issues you may have encountered.

**Tip:** Copying and pasting commands from your Terminal output will help a great deal.
