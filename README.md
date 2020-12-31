# Tenpai
*聴牌, also known as "Ready": A hand only needs one tile to win*

Tenpai is a starting project for developing [libmahjong](https://github.com/realliance/libmahjong) Player Controllers (AI to play in Mahjong matches). Tenpai ships with support for Gametable network match play in addition to running large numbers of local matches.

## Dependencies

- CMake
- `rapidjson`
- `pistache` (AUR `pistache-git`)
- `spdlog`

## Getting Started

```
# Bootstrap build/
cmake -S . -B build

# Build library
cmake --build build
```
