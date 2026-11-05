<!-- markdownlint-disable-file MD033 -->

# Full Tilt! Pinball for Android
[![Android CI](https://github.com/zakkyhidayat/spacecadetpinball-android/actions/workflows/android.yml/badge.svg)](https://github.com/zakkyhidayat/spacecadetpinball-android/actions/workflows/android.yml)
## Summary

Android app for the tables of `Full Tilt! Pinball`, running on the open source engine of `3D Pinball for Windows – Space Cadet`.

This is a fork of [fexed/Pinball-on-Android](https://github.com/fexed/Pinball-on-Android) with build updates and bug fixes. Thanks to [k4zmu2a](https://github.com/k4zmu2a) for the original source code, to [iscle](https://github.com/Iscle) for the original Android porting and to [fexed](https://github.com/fexed) for the Android app.

## Features of this fork

- Main menu with one card per Full Tilt! table: Space Cadet, Dragon's Keep and Skulduggery.
  - **Space Cadet**: the full original rules.
  - **Dragon's Keep** and **Skulduggery**: rules re-implemented from the original executables (scores, lights, sounds, quests or modes, jackpot, bonus, shoot again) plus the help file. They do not yet cover every part of the originals, see [the component guide](docs/TABLE_COMPONENTS.md) for what is and is not done.
- Table parts new to Full Tilt in the engine: accelerators, return exits, magnets and multi-gate one-way gates
- Dragon's Keep: random quest draw with the quest selection target, ten second quest restart, Slay Dragon, Wizard's Fury mystery award, armor and dragon eggs, tower locks and multiballs, and the tower diverters
- Skulduggery: the eleven letter drop targets start a mode, seven timed modes drawn at random (captive ball changes or extends them), Storm levels and the shipwreck mystery, Swordfight, Treasure Hunt with buried finds, fathom level, coin awards, special treasures, map pieces, Lava-Ball, the brig with Jail Break and Peg Leg's Loot
- Bauhaus table font and per-table accent colours, always on
- Local top 10 high scores per table (name and date), shown after each game. Scores of games with cheats are not recorded
- No online leaderboard. Sound effects and music have on/off toggles and volume sliders.
- New touch controls, haptic feedback, a restart confirmation and a back-to-menu confirmation
- Build upgraded to Gradle 8.5 / Android Gradle Plugin 8.2.2 (JDK 17+), targetSdk 34, NDK 26.3, 16 KB page size support
- Bug fixes: sticking flippers ([fexed#82](https://github.com/fexed/Pinball-on-Android/issues/82)), garbage text after the top rank ([fexed#53](https://github.com/fexed/Pinball-on-Android/issues/53)), graphics corruption when typing `gmax` ([fexed#93](https://github.com/fexed/Pinball-on-Android/issues/93)), message typos ([fexed#95](https://github.com/fexed/Pinball-on-Android/issues/95)), a crash with more than 20 balls ([k4zmu2a#209](https://github.com/k4zmu2a/SpaceCadetPinball/issues/209)) and high scores after cheats ([k4zmu2a#228](https://github.com/k4zmu2a/SpaceCadetPinball/issues/228))

## Full Tilt! data (optional)

### Playing with a released APK

The released APK has no game data. Copy the folder of your own copy of Full Tilt! Pinball (the one holding CADET, DRAGON and PIRATE) to your phone, open the app and tap **Add Full Tilt! files**, then choose that folder. The app copies the data it needs (the `.DAT` files, sounds, music and icons) into its own storage and unlocks the tables it finds; the original folder can then be removed. Dragon's Keep also needs the CADET folder for its ball.

### Building your own APK with the data

Full Tilt! Pinball is copyrighted and its data is **not** in this repository. To build an APK with the Full Tilt tables for your own use, stage your own copy of the game (the folder holding CADET, DRAGON and PIRATE) before building:

```bash
tools/stage_fulltilt.sh /path/to/FULLTILT
```

This copies the data into the git-ignored `app/fulltilt-assets/`. Do not share an APK built this way. Without it the app builds, and the tables come from the files added in the app. The original Windows 3D Pinball table is no longer bundled.

## Documentation

* [Pinball table components](docs/TABLE_COMPONENTS.md): what each part of a table is, how the game data names them, which engine class implements them, and which rules are implemented for each table.
* [CONTRIBUTING.md](CONTRIBUTING.md)

## Project layout

| Path | Contents |
| --- | --- |
| `app/` | Android app (Java): menu, settings, high scores, touch controls |
| `app/src/main/cpp/` | JNI bridge and CMake build of the engine and SDL |
| `SpaceCadetPinball/` | The pinball engine (C++), table components and `control.cpp` rules |
| `tools/` | Helper scripts, e.g. `stage_fulltilt.sh` |
| `docs/` | Documentation |

## Building

Requirements: JDK 17 or newer, Android SDK (platform 34, build-tools 34.0.0, NDK 26.3.11579264, CMake 3.22.1).

```bash
git clone --recursive https://github.com/zakkyhidayat/spacecadetpinball-android
cd spacecadetpinball-android
echo "sdk.dir=$HOME/Android/Sdk" > local.properties
./gradlew installDebug   # with a phone connected over adb
```

## Credits

- Original source: [k4zmu2a/SpaceCadetPinball](https://github.com/k4zmu2a/SpaceCadetPinball) by k4zmu2a
- Forked from: [fexed/Pinball-on-Android](https://github.com/fexed/Pinball-on-Android) by fexed
