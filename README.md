# Text adventure (data driven) engine using raylib-cpp

Statically linked dependencies (not required to install):

- nlohmann/json
- raylib
- raylib-cpp

## Controls

- `Enter` -- Advance text (Skip or go to next one)
- `Space` -- Speed up text
- `0-9` -- Pick choice(s)

## Usage

This engine uses JSON files to define all aspects of a text adventure game. The main components are (under `./data`):

- `config.json` -- Text display settings
- `story.json` -- Game narrative and flow
- `items.json` -- In-game items
- `effects.json` -- Status effects
- `variables.json` -- Hidden game variables
- `flags.json` -- Boolean flags

(won't) TODO...

## Example

There is a `data` directory inside this repository (and the released binaries), it contains an example on every option possible using this engine.
Instead of writing a long guide on how to use it, read the JSON files instead.
The engine uses sane defaults for condition/action options (comparison, value/amount etc.)

## Building from source

Prerequisites:

- C++ compiler
- CMake

Project dependencies are handled with CMake, install and build using CMake on your system.

## License

Do whatever.
