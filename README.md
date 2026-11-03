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

## Articles

Some articles were written about this project! Thank you to everyone. Some articles I found are on: [Frandroid](https://www.frandroid.com/android/applications/1384165_un-developpeur-ressuscite-le-pinball-3d-de-windows-sur-android-voici-comment-y-jouer), [TudoCelular](https://www.tudocelular.com/android/noticias/n192126/windows-xp-jogo-classico-pinball-3d-android.html), [Libero Tecnologia](https://tecnologia.libero.it/uno-studente-italiano-ha-portato-il-flipper-di-windows-su-android-58522), [Oxii](https://www.oxii.vn/tech/tua-game-huyen-thoai-tren-windows-pinball-3d-da-co-phien-ban-tren-android-39480.html), [Tugatech](https://tugatech.com.pt/t46867-space-cadet-do-windows-agora-chega-tambem-ao-android), [Robotina](https://www.robotina.us/entretenimiento/El-Pinball-tiene-una-version-disponible-para-celulares-Android-20220701-0004.html), [Androiditaly](https://www.androiditaly.com/2022/07/02/3d-pinball-space-cadet-arriva-su-android-grazie-ad-un-progetto-amatoriale-tutto-italiano/), [Pasion Movil](https://www.pasionmovil.com/videojuegos-2/3d-pinball-el-clasico-juego-de-windows-xp-llega-a-dispositivos-android/), [Clubic](https://www.clubic.com/pro/entreprises/microsoft/actualite-429654-vous-en-reviez-et-ils-l-ont-fait-3d-pinball-de-windows-obtient-un-portage-sur-android.html), [Meteoweek](https://tech.meteoweek.com/2022/07/10/3d-pinball-non-e-piu-unesclusiva-windows-space-cadet-sara-anche-per-android-grazie-ad-uno-studente/), 

## Known source ports

| Platform           | Author          | URL                                                                                                        |
| ------------------ | --------------- | ---------------------------------------------------------------------------------------------------------- |
| Original source    | k4zmu2a         |<https://github.com/k4zmu2a/SpaceCadetPinball>                                                              |
| PS Vita            | Axiom           | <https://github.com/suicvne/SpaceCadetPinball_Vita>                                                        |
| Emscripten         | alula           | <https://github.com/alula/SpaceCadetPinball> <br> Play online: <https://alula.github.io/SpaceCadetPinball> |
| Nintendo Switch    | averne          | <https://github.com/averne/SpaceCadetPinball-NX>                                                           |
| webOS TV           | mariotaku       | <https://github.com/webosbrew/SpaceCadetPinball>                                                           |
| Android (WIP)      | Iscle           | https://github.com/Iscle/SpaceCadetPinball                                                                 |
| Nintendo Wii       | MaikelChan      | https://github.com/MaikelChan/SpaceCadetPinball                                                            |
| Nintendo 3DS       | MaikelChan      | https://github.com/MaikelChan/SpaceCadetPinball/tree/3ds                                                   |
| Nintendo Wii U     | IntriguingTiles | https://github.com/IntriguingTiles/SpaceCadetPinball-WiiU                                                  |
| MorphOS            | BeWorld         | https://www.morphos-storage.net/?id=1688897                                                                |
| AmigaOS 4          | rjd324          | http://aminet.net/package/game/actio/spacecadetpinball-aos4                                                |

Platforms covered by this project: Android.
