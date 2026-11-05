# Pinball table components

This document describes the parts of a Full Tilt! Pinball table as the engine of this app sees them, how the
game data names them, which engine class implements each, and how the Dragon's Keep and Skulduggery rules use them.
No game data is included in this repository: the names and numbers below describe how the data is laid out and what
the code does with it.

## 1. How a table is built

A table is a group in the game's `.DAT` file. Every component in it has a name (its *group name*, for example
`a_bump1`) and an object type code stored in the data. At load time `TPinballTable` reads the type code and creates the
matching C++ class (`SpaceCadetPinball/TPinballTable.cpp`). Components that react to the ball call
`control::handler(code, component)` with a message code; the rules live in `SpaceCadetPinball/control.cpp`.

* `63` (original `0x4a`): the ball hit this component.
* `57`: a drop or solo target was knocked down.
* `60`: the ball was lost (drain) or a timer expired.
* `1005`: the plunger was released.

Space Cadet has one hand-written control function per component. Dragon's Keep and Skulduggery use the generic,
table driven rules (`lenient_rules`, enabled by `loader::Lenient`) described in section 5.

## 2. Naming convention

The first letters of a group name tell what kind of part it is.

| Prefix | Part |
| --- | --- |
| `a_bump` | Pop bumper: kicks the ball away and scores |
| `a_rebo` | Rebound: angled rubber post |
| `a_spot` | Solo target: one stationary target with a light |
| `a_drop` | Drop target: falls down when hit, resets as a bank |
| `a_sink` | Sink: hole that captures the ball, then serves it out |
| `a_kout` | Kickout: hole that fires the ball back into play |
| `a_roll` | Rollover lane: sensor with a light |
| `a_ramp` | Ramp the ball travels along |
| `a_accl` | Accelerator: lane zone that speeds the ball up |
| `a_flip` | Flipper |
| `a_kick` | Kickback in an outlane |
| `a_bloc` | Blocker: gate that opens and closes a passage |
| `a_rock` | Sliding rock moved by a target |
| `a_center_post` | Post between the flippers |
| `s_trip` | Tripwire: lane sensor that counts passes |
| `s_oneway` | One-way gate, may have several gates |
| `s_rexit` | Return exit: lets the ball back out of a ramp or lane |
| `s_hole` | Hole to a lower playfield |
| `s_magnet` | Magnet that holds or pulls the ball |
| `s_launcher`, `s_plunger` | Ball launcher |
| `v_lite`, `v_wlite` | Lights, wall lights |

The engine class is chosen by the object type code, not by the prefix. The codes the engine creates
(`TPinballTable.cpp`):

| Code | Class | Code | Class |
| --- | --- | --- | --- |
| 1000, 1010 | `TWall` | 1015 | `TRollover` |
| 1001, 1034 | `TPlunger` | 1016 | `TOneway` |
| 1002 | `TLight` | 1017 | `TSink` |
| 1003, 1004 | `TFlipper` (left, right) | 1018 | `TFlagSpinner` |
| 1005 | `TBumper` | 1019 | `TSoloTarget` |
| 1006 | `TPopupTarget` | 1020 | `TLightRollover` |
| 1007 | `TDrain` | 1021 | `TRamp` |
| 1011 | `TBlocker` | 1022 | `THole` |
| 1012, 1029 | `TKickout` | 1024 | `TTripwire` |
| 1013 | `TGate` | 1026 | `TLightGroup` |
| 1014 | `TKickback` | 1028 | `TComponentGroup` |
| 1030 | `TLightBargraph` | 1031 | `TSound` |
| 1032 | `TTimer` | 1033 | `TTextBox` |

Object type codes that Full Tilt adds to the original 3D Pinball set (from the original executable's creation switch):

| Code | Part | Notes |
| --- | --- | --- |
| 1034 | Launcher | handled as the plunger |
| 1035 | Return exit | two lines from the data; passes the ball through and plays a sound |
| 1036 | Accelerator | throw speed multipliers and angle from the data |
| 1037 | The ball | `ball0`, not a table part |
| 1038 | Light sweeps | light animation sequencer, not implemented (no gameplay effect) |
| 1042 | Magnet | pulls the ball while it is not held; holds it for a short time |
| 1043 | Multi-gate one-way | several gate lines, each with its back line |

## 3. Dragon's Keep

Theme: a battle with a dragon. Goal: complete the quests, or push the sword target in, to slay the dragon.

Jackpot growth (0x42c020): each target hit adds 50,000 and counts for the 2,000 a target end-of-ball bonus; a ball in the well (`a_sink4`) or the first fire lizard sink (`a_sink1`) adds 75,000. Other sinks and the kickouts add nothing. The jackpot is capped at 10,000,000 (0x4238a0). The end-of-ball bonus steps (0x42b7c0) are 2,000 a target, 100,000 a quest, 50,000 an armor light, 75,000 a spell, 150,000 an egg and 75,000 times the weapon multiplier, which is what the port pays.

Component inventory (counts from the game data):

| Group | Count | Role |
| --- | --- | --- |
| `a_bump` | 4 | Forest bumpers, 1,500 each |
| `a_rebo` | 2 | Rebounds, 1,000 each |
| `a_spot` | 18 | Spell targets, tower targets, gargoyle targets, sword, quest selection and ricochet targets |
| `a_sink` | 10 | Fire lizard sinks, well, prison tower, hideaways and more |
| `a_kout` | 3 | Armor kickout, dragon egg kickout, gargoyle kickout |
| `a_roll` | 5 | Lane rollovers, 10,000 to 30,000 |
| `s_trip` | 8 | Ramp and lane sensors with stepped scores |
| `a_ramp` | 2 | Tower ramp and dragon ramp |
| `a_accl` | 1 | Lane accelerator (75,000 / 500,000) |
| `a_rock` | 2 | Sliding rocks in front of the gargoyle passage |
| `a_bloc` | 2 | Blockers |
| `s_oneway`, `s_rexit`, `s_hole` | 2, 2, 1 | Gates, return exits, hole |

Key components (names are the group names in the data):

* `a_sink1`, `a_sink2`: the two **fire lizard sinks**, 5,000 each. Two sink hits start the next quest. A finished quest
  can be restarted by a fire lizard sink for ten seconds.
* `a_spot4`, `a_spot5`, `a_spot6`, `a_spot7`, `a_spot22`: the five **spell targets**, 2,500 each. During Wizard's Fury they
  set the mystery award (extra ball, max armor, max weapons, jackpot, one million).
* `a_spot1`, `a_spot2`, `a_spot3`: **tower targets**, 2,000 each, 10,000 for the bank.
* `a_spot8`, `a_spot10`, `a_spot12`, `a_spot14`: **gargoyle targets**, 3,000 each, 15,000 for the bank.
* `a_spot27`: the **quest selection target**, 5,000. Draws another quest that is not completed.
* `a_spot19`, `a_spot26`, `a_spot28`: the **sword targets**. In the idle state they must be hit in that order (original `0x425750`, `0x4257c0`, `0x425830`); the third starts the Slay Dragon quest. The order restarts on each ball.
* `a_sink4`: the **well**. Pays the mystery award during Wizard's Fury. In the idle state a quarter of the balls start the drawn quest and the rest cast a spell (original 0x426140).
* `a_sink19`: the **dragon's mouth**. Counts the hits for Slay Dragon.
* `a_kout1`: **armor kickout**. Awards the next piece of armor.
* `a_kout2`: **dragon egg kickout**. Each hit adds a dragon egg.
* `a_kout3`: a kickout that only sets a flag in the original.
* `a_bump1` to `a_bump4`: forest bumpers. Every tenth hit of a ball awards the next weapon (25,000 more each time; the count restarts on each ball). A weapon pays 25,000, 35,000, 45,000 or 55,000 without the multiplier and then sets the table's score multiplier to 2, 3, 4 or 5 for every later score, until the ball is lost (decoded from 0x423330, 0x423130 and the table's score routine 0x419f10, which multiplies each score by `+0x15e`). The original's jackpot accumulation flags (`+0x16e`, `+0x176`, `+0x17e`) are never switched on in either game, so scoring never feeds the jackpots by itself.

Rules that are implemented (`control.cpp`):

* Per component scores, banks and bank bonuses from the game data.
* Jackpot: starts at 1,000,000; targets add 50,000, sinks 75,000, each completed quest 500,000.
* Five timed quests (about 27 to 32 seconds each), drawn at random from the ones not completed. Their order in the original is Dragon Hoard,
  Fire Lizard Attack, Rescue Maiden, Dragon Pass, Wizard's Fury. Starting a quest pays 100,000. A quest ends when its timer runs out; the original
  credits it then (jackpot +500,000, quest light lit, next quest drawn) and the table score multiplier rises.
* Dragon Hoard: each gem has its own value (gold 10,000 bumpers, diamond 50,000 spell targets, pearl 60,000 tower targets, sapphire 70,000 gargoyle targets,
  ruby 100,000 fire lizard sinks, opal 100,000 accelerator, emerald 200,000 and amethyst 250,000 ramps); all nine give the extra ball.
* Fire Lizards: each sink hit is worth 100,000 more than the one before (up to 1,000,000) and every fourth hit awards the jackpot.
* Slay Dragon: starts when the sword targets are hit in order or when all five quests are done. Starting it pays 500,000. Needs eight minus the weapons and offensive spells hits in the
  dragon's mouth, in 30 seconds plus five per armor piece or defensive spell. The super jackpot (cap 20,000,000) grows with bumpers (50,000), targets (100,000), the sinks `a_sink1`/`a_sink2` (500,000) and kickouts (750,000); slaying the dragon pays it plus 1,500,000 and the jackpot. Each ball in the dragon's mouth pays by the lit lights of the sweeping dragon fire: 100,000, 1,000,000 with two lit, a one in five jackpot with three, a one in ten extra ball light or extra ball with more. Each ball in the mouth that does not finish the quest adds 15 seconds.
* Skill shot: the first spell target the launched ball hits gives a spell (`a_spot4`), dragon egg (`a_spot5`), weapon (`a_spot6`), armor (`a_spot7`) or Gargoyle Gaggle-Ball (`a_spot22`).
* Spell bank: hitting all five spell targets casts a spell (75,000 each in the ball bonus).
* Ball drain: shoot again in the first 15 seconds, then the bonus (targets, quests, armor, spells, dragon eggs), extra balls, game over.
* Lights and sounds as the original per-component code switches them.

* Dragon eggs: the egg award pays the eggs held times 100,000; the return exits (`s_rexit18`, `s_rexit19`) give two eggs, the kickout `a_kout2` one during Dragon Pass.
* Multiball: Gargoyle Gaggle-Ball (two balls, the new ball comes out of `a_sink1`) from the gargoyle kickout `a_kout2` or the skill shot; Tower Barrage (three balls): the tower bank
  lights the tower lock, the tower sinks lock a ball each, in that order: first `a_sink18` or `a_sink15` (lock light `v_lite48`), then `a_sink17` or `a_sink13` (`v_lite49`), then `a_sink9` or `a_sink10` (`v_lite50`); the diverters choose between the two sinks of a lock, and `a_sink16` has no handler of its own; "Ball Trapped" shows the sink score), and the third lock releases them; Dragon Flurry (five balls)
  when all six dragon letters are lit (fire lizard sinks, spell bank, dragon loop, gargoyle bank, tower ramp, tower bank). The letters, and the tower lock light, count only in the idle state (no quest, Slay or multiball), as in the original.
* Egg hole (`s_hole118`): offers the highest affordable purchase (quest 1 egg, spell 4, weapon 5, armor 6, extra ball light 7, extra ball 8); the left flipper buys, the right declines for 25,000.
* Dragon loop (`a_ramp103`): pays and adds to the jackpot (50,000 more for each loop in a row, up to ten); the jackpot is capped at 10,000,000.

Bonus hold: slaying the dragon lights `v_lite31`; the end-of-ball bonus is then kept and added to the next ball's bonus. Only Gaggle pays 100,000 at the start (decoded). Each multiball mode ends when one ball is left (the original has no extra scoring inside the Gaggle and Barrage states).

Tower diverters: four pairs of one-way gates (`a_dvtraa`/`ab`, `ba`/`bb`, `ca`/`cb`, `da`/`db`) take the messages 63 (active) and 62 (inactive), decoded from the original gate class (0x415410: 0x3f sets the active flag, 0x3e clears it). Position 1 makes the second gate of a pair active and the first inactive, position 2 the opposite. At the start of a ball: A and D position 2, B and C position 1 (0x4245b0). Moves: tower bank complete (idle, and only when it does not light the sixth dragon letter, 0x4250e0 and 0x4244e0) A and D to 1; gargoyle bank complete B and C to 1; `a_roll7` A to 1; `a_sink9`/`a_sink10` A and D to 2; `s_oneway5` (idle) D to 1; `a_ramp103` D to 2; `s_rexit18` (idle) B to 2; `s_rexit19` (idle) C to 2; Dragon Hoard start B and C to 2; Rescue Maiden start A 1, B 2, C 1, D 1. The original skips the A and D moves in its info states 6 (the Rescue Maiden quest, whose start sets the pairs) and 0xd (Tower Barrage), and does the idle moves only in state 2 (no quest, Slay or multiball).

Slay Dragon mouth, extra: each ball in the mouth that does not finish the quest tells one of `a_sink4`, `a_sink1`, `a_sink2`, `a_sink18`, `a_sink17`, `a_sink16`, chosen at random, to release its ball after 3 seconds (original 0x427f10). A ball held by a tower lock is left locked.

Not implemented: the random ball transfer from the tower sinks to
`a_sink1`/`a_sink2`, the gem lights of Dragon Hoard, and light sweeps.

## 4. Skulduggery

Theme: a hunt for pirate treasure. Goal: complete the modes, collect the six map pieces and find Peg Leg's loot.

| Group | Count | Role |
| --- | --- | --- |
| `a_bump` | 3 | Bumpers with seven stepped scores (1,500 to 10,500) |
| `a_drop` | 11 | Drop targets: ship (5), tavern (3), parrot (3) |
| `a_spot` | 8 | Skulduggery letter targets, volcano targets, captive ball `a_spot102` |
| `a_sink` | 10 | Hideaways, ship sink `a_sink4`, tavern window sinks |
| `a_kout` | 2 | Kickouts |
| `a_roll` | 10 | Wind lanes (four, 25,000 / 50,000 / 75,000) and island lanes |
| `a_ramp` | 3 | Ramps |
| `s_magnet` | 6 | Keg magnets under the tavern; each hit pays 100,000 (0x42a470 to 0x42a740) |
| `s_trip`, `s_oneway`, `s_rexit`, `s_hole` | 5, 2, 1, 1 | Lane sensors, gates, return exit, hole |

Modes, in the order of the original: Attack Ship, Treasure Hunt, Tavern, Bermuda Triangle, Storm, Mutiny, Swordfight, then
Peg Leg's Loot. The captive ball (`a_spot102`) draws another mode and adds ten seconds during a mode.

Implemented:

* Per component scores and banks from the game data, jackpot, ball bonus, shoot again, lights, sounds.
* Seven modes drawn at random from those not completed, each timed (24 to 31 seconds where the original timers were read).
* Mode start payouts (the start case of each mode's handler): Attack 200,000, Treasure Hunt 300,000, Tavern 200,000, Bermuda 200,000, Storm 300,000, Mutiny 100,000, Swordfight 250,000. Peg Leg's Loot pays 1,000,000 when it starts.
* Attack Ship: each ship target pays 10,000; all five sink the ship ("Ship Sunk": the jackpot and 25,000, the targets come back up) and the mode goes on until its timer ends; during the mode the wire ramp exit `s_rexit8` gives "Ship Captured", raises the ship targets again and the fathom level. The sensor `s_trip2` also raises the ship targets again (0x4290c0).
* Fathom level: 1 at the start of each ball, up to 7. It goes up when all six island lane lights are lit (each of `a_roll12`, `a_roll11`, `a_roll10` lights twice), with Peg Leg's Loot, with the Fathoms Up mystery and when the ship is captured. It multiplies the buried bonus.
* Treasure Hunt: only the hideaway with the flashing X counts; the X then moves. The finds are buried and paid when the mode ends (decoded from 0x424b00 and 0x425ab0): three coin awards, two special treasures, a bonus (((special treasures x 2 + map pieces) x 25 + modes x 20 + targets) x 10,000, times the fathom level), the jackpot and an extra ball, then coin awards again.
* Storm: a ball in a hideaway (`a_sink17`, `a_sink15`, `a_sink14`) wrecks the ship ("Shipwrecked") and ends the storm; the shipwreck mystery is then paid by the next hit on the rollover `a_roll3`: a special treasure, extra ball, map piece, coin award (the bumper level award sets the bumpers to the top level, "Max Crew", from 0x425000; the fathom award raises the fathom level).
* Bermuda Triangle: the indicated wind lane pays 125,000 / 250,000 / 500,000 / 1,000,000 / jackpot, other lanes 50,000 (the indicator moves every 0.1 s, decoded from the original light timer). In this mode the lanes pay only that award, not their normal 25,000 to 75,000.
* Storm: any drop target bails water; value and jackpot interval follow the storm level (squall, tropical storm, monsoon,
  hurricane). The level is approximated from the wind lane passes, because the eight wind lights are not tracked.
* Swordfight: parrot and volcano targets, 30,000 each; completing a bank pays a coin award, special treasure, map piece or extra ball.
* Coin awards (50,000 doubling to 1,600,000), special treasures (100,000 up to 1,500,000), map pieces (1,000,000 each).
* Tavern mode: the window sinks (`a_sink5`, `a_sink6`, `a_sink7`) give the random award of the original: map piece, special treasure, coin award or extra ball.
* Peg Leg's Loot after all modes or all six map pieces: hideaways give special treasures, the ship sink finds the loot.

Skulduggery has no skill shot: its executable has no skill-shot message or state (the launcher handler `s_launcher1` only drives the cannon and the launch lights). Skulduggery has no wormhole: neither its component table nor its messages mention one, so the wormhole multiball item does not apply. Not implemented: light sweeps (visual only).

Skulduggery start: the eleven drop targets `a_drop5` to `a_drop15` each light one letter of SKULDUGGERY (bits 0x1 to 0x400 of `v_lite1`, set by the handlers 0x4268b0 and the others). When all eleven are lit the mode is chosen (original 0x425de0). The old rule of ten hits on any start target is replaced by this.

Skulduggery idle state: with all four volcano lights `a_spot8` to `a_spot11` lit, Lava-Ball starts and two balls are queued for the plunger (original 0x427540; the `0x192` queue is the same feed as `feed_balls`). Jail (the brig, `s_hole19`, decoded from 0x429040 and the routine at 0x424210, whose only caller is the brig handler at 0x4290a6): the hole gives a trapped ball back itself, so the first two traps change nothing. The third trap is held and starts Jail Break: 100,000, and two more balls are fed (the held ball is the third). Decoded from the jail routine (0x424210, in a block Ghidra left undefined): every trap in `s_hole19` (message 0x42 in the idle state) takes one off the table's ball counter `0x192` and adds one to the held count `0x435d3c`; at the second trap it switches the one-way `s_oneway12` on (0x43bc04: the gate behind which the held balls wait); the first two traps then play a sound and send message 0x3fb with 0.96 to the launcher `s_launcher1` (0x43abdc), which serves a new ball for the held one, and play `tabb39wave`; the third trap starts Jail Break (info state 0xd, 0x423630). Jail Break (0x42d590, message 0x4f) adds the three held balls back to `0x192`, re-enables `a_kick1` (message 0x4b; its class at 0x415d70 is the outlane kickback: 0x4c disables it, 0x4b enables it, so it does not hold balls), pays 100,000 and opens `s_oneway12` again so the held balls come out. `s_hole19` is a drop-through hole, and the held balls wait behind the closed `s_oneway12` gate. The port's version (first two traps do nothing, the third feeds two balls) has about the same effect for the player but not the same mechanics. The counter `0x192` is the balls the table still has to serve: the drain routine (0x42db30) ignores a ball that rests on a flipper, `s_launcher1`, `s_oneway12` or `a_kick1`, and otherwise removes the ball, takes one off `0x192` and sends message 0x3fb to `s_launcher1`, which serves the next ball. Lava-Ball (state 0xc, 0x42d480) re-enables `a_kick1`, opens `s_oneway12` and adds 2 to `0x192` (two more balls); state 0x11 (0x42d730) also opens `s_oneway12`, disables the six magnets and both kickouts, and gives the held balls back. Approximation: the original's ball counter (`0x192`) is not tracked, so the release feeds new balls rather than queued ones. The brig's flag on the second trap (a light) is not ported. Jail Break from the idle state: the third hit of `a_spot6` (original 0x4279b0) pays 100,000 for the held balls and clears the count; no ball is fed, because the brig hole already returned them; with none held it does nothing. The idle lights of that cycle are not ported.

Skulduggery routes (`a_ramp8` Island Breeze, `a_ramp5` Nor'Easter, `s_trip3` and `s_trip8` Tradewind Loop; decoded from 0x428b70, 0x428d80, 0x429210, 0x429400 and the wind lanes 0x4298f0 to 0x429da0 "Sou'Eastern", "Easterly", "Westerly"): a hit lights the next light of the route's group (message 0xf with 2.0 in the original: the light stays on and only flashes for two seconds), and the lit count before the hit is the score step. A wind lane has 3 steps (25,000, 50,000, 75,000), so repeated hits climb the steps and stay on the last one. The ramps and orbit sensors have 12 steps: 3 times the combo level (0 to 3, the combo group, lit by every hit and put out when a different route scores) plus the lit count of the route's own light group (0 to 2). The route lights light only in the idle state, and start again with each ball and each ended mode (0x42c070 cases 0x4f and 0x52). The port keeps them as counters instead of lights. Wind lanes keep their separate Bermuda and storm rules.

Lane lights (idle state only; 0x429630, 0x429790, 0x429840, 0x4298f0, 0x4296d0, checked by 0x424290): `s_trip11`, `a_roll5`, `a_roll1`, `a_roll2` and `a_roll3` each light their lane light; with all five lit the lights start again and 0x423aa0 lights a map piece and pays One Million (the port's `map_piece`). They start again with each ball. `a_roll3` also runs the Shipwreck Mystery when it is available (0x425d10 with `v_lite529` lit, then the random award of 0x425c50), which is already ported. The light that picks the next map piece (0x425850) is visual only.

## 5. Engine classes added for Full Tilt

| File | Purpose |
| --- | --- |
| `TAccelerator.cpp/.h` | Lane zone. Records the ball on collision and throws it with the multipliers read from the data. |
| `TReturnExit.cpp/.h` | Two pass-through lines with collision masks from the data. |
| `TMagnet.cpp/.h` | Core circle plus pull field; holds the ball for one second. |
| `TOneway.cpp/.h` | Extended for multi-gate one-ways (several line pairs, back lines). |
| `control.cpp` | Table rules: `lenient_rules`, the quest/mode state, bonus and drain handling. |
| `lenient_scores.h` | Per component score values read from the original executables. |
| `lenient_lights.h`, `lenient_sounds.h` | Lights and sounds switched by each component's original code. |

## 6. Where the rules come from

The score tables, light and sound operations and the state flow were read from the original executables with a decompiler
(handler tables, quest selection, mystery award mapping, special treasure and coin tables, storm levels). Behavior that
could not be read is taken from the original help file and marked above as approximated or not implemented. Nothing in
this repository was copied from the original program's code; the rules are a re-implementation.
