<!-- markdownlint-disable-file MD033 -->

# spacecadetpinball-android
[![Android CI](https://github.com/zakkyhidayat/spacecadetpinball-android/actions/workflows/android.yml/badge.svg)](https://github.com/zakkyhidayat/spacecadetpinball-android/actions/workflows/android.yml)
## Summary

Android port of `3D Pinball for Windows – Space Cadet`, a game bundled with Windows.

This is a fork of [fexed/Pinball-on-Android](https://github.com/fexed/Pinball-on-Android) with build updates and bug fixes. Thanks to [k4zmu2a](https://github.com/k4zmu2a) for the original source code, to [iscle](https://github.com/Iscle) for the original Android porting and to [fexed](https://github.com/fexed) for the Android app.

## Changes in this fork

- Build upgraded to Gradle 8.5 / Android Gradle Plugin 8.2.2 (JDK 17+), targetSdk 34, NDK 26.3
- Flippers no longer stick when a touch is cancelled, e.g. by an edge swipe ([fexed#82](https://github.com/fexed/Pinball-on-Android/issues/82))
- No garbage text after reaching the top rank ([fexed#53](https://github.com/fexed/Pinball-on-Android/issues/53))
- No graphics corruption when typing the `gmax` cheat ([fexed#93](https://github.com/fexed/Pinball-on-Android/issues/93))
- Message typos and desktop key prompts fixed ([fexed#95](https://github.com/fexed/Pinball-on-Android/issues/95))
- No crash when the ball cheat spawns more than 20 balls ([k4zmu2a#209](https://github.com/k4zmu2a/SpaceCadetPinball/issues/209))
- Cheats that stay on now block high score entry in later games ([k4zmu2a#228](https://github.com/k4zmu2a/SpaceCadetPinball/issues/228))
- Score upload: fixed a crash on repeated uploads and the wrong message on failure

## Building

Requirements: JDK 17 or newer, Android SDK (platform 34, build-tools 34.0.0, NDK 26.3.11579264, CMake 3.22.1).

```bash
git clone --recursive https://github.com/zakkyhidayat/spacecadetpinball-android
cd spacecadetpinball-android
echo "sdk.dir=$HOME/Android/Sdk" > local.properties
./gradlew installDebug   # with a phone connected over adb
```

## How to play

Build it yourself as above, or download the upstream [APK](https://github.com/fexed/Pinball-on-Android/releases)

## Credits

- Original source: [k4zmu2a/SpaceCadetPinball](https://github.com/k4zmu2a/SpaceCadetPinball) by k4zmu2a
- Forked from: [fexed/Pinball-on-Android](https://github.com/fexed/Pinball-on-Android) by fexed
