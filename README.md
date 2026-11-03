<!-- markdownlint-disable-file MD033 -->

# spacecadetpinball-android
[![Android CI](https://github.com/zakkyhidayat/spacecadetpinball-android/actions/workflows/android.yml/badge.svg)](https://github.com/zakkyhidayat/spacecadetpinball-android/actions/workflows/android.yml)
## Summary

Android port of `3D Pinball for Windows – Space Cadet`, a game bundled with Windows.

This is a fork of [fexed/Pinball-on-Android](https://github.com/fexed/Pinball-on-Android) with build updates and bug fixes. Thanks to [k4zmu2a](https://github.com/k4zmu2a) for the original source code, to [iscle](https://github.com/Iscle) for the original Android porting and to [fexed](https://github.com/fexed) for the Android app.

## Features of this fork

- Main menu with one card per table: the classic Windows 3D Pinball Space Cadet and the three Full Tilt! Pinball tables (Space Cadet, Dragon's Keep, Skulduggery). Dragon's Keep and Skulduggery are listed as "Coming soon": the engine has no rules for them yet.
- No online leaderboard and no in-app volume sliders: use Android's media volume. Sound effects and music keep their on/off toggles.
- New touch controls, haptic feedback, a restart confirmation and a back-to-menu confirmation
- Build upgraded to Gradle 8.5 / Android Gradle Plugin 8.2.2 (JDK 17+), targetSdk 34, NDK 26.3, 16 KB page size support
- Bug fixes: sticking flippers ([fexed#82](https://github.com/fexed/Pinball-on-Android/issues/82)), garbage text after the top rank ([fexed#53](https://github.com/fexed/Pinball-on-Android/issues/53)), graphics corruption when typing `gmax` ([fexed#93](https://github.com/fexed/Pinball-on-Android/issues/93)), message typos ([fexed#95](https://github.com/fexed/Pinball-on-Android/issues/95)), a crash with more than 20 balls ([k4zmu2a#209](https://github.com/k4zmu2a/SpaceCadetPinball/issues/209)) and high scores after cheats ([k4zmu2a#228](https://github.com/k4zmu2a/SpaceCadetPinball/issues/228))

## Full Tilt! data (optional)

Full Tilt! Pinball is copyrighted and its data is **not** in this repository. To build an APK with the Full Tilt tables for your own use, stage your own copy of the game (the folder holding CADET, DRAGON and PIRATE) before building:

```bash
tools/stage_fulltilt.sh /path/to/FULLTILT
```

This copies the data into the git-ignored `app/fulltilt-assets/`. Do not share an APK built this way. Without it the app builds with the classic table only.

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
