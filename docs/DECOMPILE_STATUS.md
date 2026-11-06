# Decompile status

Helper routines of the original game code that write game state or scores and that no table component owns directly. Generated from the decompiles of `DRAGON.EXE` and `PIRATES.EXE`. A routine counts as *cited* when its address appears in `docs/TABLE_COMPONENTS.md` or `control.cpp`. *Open* routines still need to be read. Cited means the routine is referenced in the docs or code; it does not mean it is ported. See the notes below the tables for what is still approximated.

## Skulduggery: 59 cited, 0 open

| Address | Status | Score-like values | State set |
| --- | --- | --- | --- |
| `0x4230c0` | cited | 1000000 | 0x11, 0 |
| `0x4232c0` | cited | - | - |
| `0x423310` | cited | - | - |
| `0x423350` | cited | - | - |
| `0x423440` | cited | - | 3 |
| `0x423460` | cited | - | 2 |
| `0x423480` | cited | - | 4 |
| `0x4234c0` | cited | - | 5 |
| `0x423500` | cited | - | 6 |
| `0x423520` | cited | - | 7 |
| `0x423560` | cited | - | 8 |
| `0x4235a0` | cited | - | 9 |
| `0x4235c0` | cited | - | 10 |
| `0x4235f0` | cited | - | 0xb |
| `0x423610` | cited | - | 0xc |
| `0x423630` | cited | - | 0xd |
| `0x423650` | cited | 10000000 | - |
| `0x4236a0` | cited | - | - |
| `0x423720` | cited | - | - |
| `0x423aa0` | cited | 1000000 | - |
| `0x424580` | cited | - | - |
| `0x424700` | cited | - | - |
| `0x424780` | cited | 100000, 1000000, 1500000, 250000 | - |
| `0x424b00` | cited | - | - |
| `0x425080` | cited | - | - |
| `0x425110` | cited | - | - |
| `0x425230` | cited | - | - |
| `0x425440` | cited | - | - |
| `0x425490` | cited | 30000 | - |
| `0x425550` | cited | - | - |
| `0x425ab0` | cited | - | - |
| `0x425de0` | cited | - | - |
| `0x4264f0` | cited | 10000, 25000 | - |
| `0x426a40` | cited | 25000, 50000 | - |
| `0x426eb0` | cited | 30000 | - |
| `0x427540` | cited | - | - |
| `0x4278c0` | cited | - | - |
| `0x428900` | cited | - | - |
| `0x429ef0` | cited | - | - |
| `0x42a830` | cited | - | - |
| `0x42aad0` | cited | - | - |
| `0x42ab90` | cited | - | - |
| `0x42abf0` | cited | - | - |
| `0x42ad70` | cited | 200000 | - |
| `0x42b090` | cited | 20000, 300000 | - |
| `0x42b420` | cited | 200000 | - |
| `0x42b820` | cited | 10000, 100000, 200000, 250000 | 1, 3 |
| `0x42c070` | cited | 200000 | - |
| `0x42c430` | cited | 10000, 100000, 25000, 300000 | - |
| `0x42ca00` | cited | 100000 | - |
| `0x42cc10` | cited | 250000 | - |
| `0x42cfc0` | cited | 1000000, 50000, 500000 | - |
| `0x42d480` | cited | - | 2 |
| `0x42d590` | cited | 100000 | 2, 2 |
| `0x42d730` | cited | - | - |
| `0x42d830` | cited | - | 2 |
| `0x42d850` | cited | 20000, 40000 | 2 |
| `0x42d900` | cited | 750000 | - |
| `0x42db30` | cited | - | - |

## Dragon: 26 cited, 0 open

| Address | Status | Score-like values | State set |
| --- | --- | --- | --- |
| `0x423be0` | cited | - | 0xd |
| `0x423e90` | cited | 65526 | 9 |
| `0x424210` | cited | - | - |
| `0x424260` | cited | 1000000, 2500000 | 1 |
| `0x4244e0` | cited | - | 0xf |
| `0x424d20` | cited | - | - |
| `0x4250e0` | cited | - | - |
| `0x4252b0` | cited | - | - |
| `0x425c30` | cited | 100000 | - |
| `0x4282c0` | cited | - | - |
| `0x4285f0` | cited | 15000 | 2, 2, 2 |
| `0x428870` | cited | - | 2, 2 |
| `0x428a80` | cited | 10000, 100000, 200000, 250000 | 3, 2 |
| `0x4291c0` | cited | 100000 | 3, 2 |
| `0x429510` | cited | 100000 | 3, 2, 2 |
| `0x429b10` | cited | 100000 | 3, 2 |
| `0x429ec0` | cited | 100000 | 3, 2 |
| `0x42a150` | cited | 100000, 1500000, 50000, 500000 | 2, 3 |
| `0x42ac80` | cited | 25000 | 2, 2 |
| `0x42b0e0` | cited | - | 2 |
| `0x42b3c0` | cited | 100000 | 2 |
| `0x42b510` | cited | - | 2 |
| `0x42b7c0` | cited | 100000, 150000, 50000, 75000 | 0 |
| `0x42c000` | cited | - | 2 |
| `0x42c020` | cited | 100000, 50000, 75000 | - |
| `0x42c320` | cited | - | - |

- `0x4245b0` (Dragon ball start): checked. Diverters, multiplier reset to 1 and the kicker enabled are ported; the other calls are light resets (visual only).
- `0x423680` (Skulduggery `a_sink8` message 0x41): decoded. The sink class (constructor `0x418390`, vtable `0x4386c0`, Message `0x418650`) handles 0x41 by starting a timer: a negative value uses the sink's own time (attribute 407), otherwise the value in seconds; when it fires (`0x418500`) the ball leaves the sink, or the timer retries after 0.5 s while the spot is blocked. This is the engine's `TSink` message 56, so the mode values -1, 1 and 2 are waits of default, 1 and 2 seconds. Not called in the port yet: the callers are the brig start and the mode states, which are approximations here, so calling it now could duplicate balls.
- `0x424560` / `0x42ce80` (Skulduggery): ported. Peg Leg's Loot start (0x42cfc0 0x4f) turns a_sink9 and a_sink12 on and the orbit tripwires s_trip3 and s_trip8 off; Treasure Hunt start (0x42b090 0x4f) turns only the tripwires off. When either mode ends (0x52) the sinks go off and the tripwires on.
- `+0x192` (balls the table still has to serve): covered by `BallsInPlay` and `HeldBalls` in `control.cpp`. The original adds 1, 3 or 4 when a multiball starts (0x42b3c0, 0x42b0e0, 0x42b510) and subtracts 1 per ball lost; our version counts balls in play. Not tracked separately.
- `a_kick1` (+5 flag, Dragon 0x4245b0, 0x424260, 0x423240, 0x426a50): set to 1 at ball start, when the kickback is awarded and when a lit spot is hit; set to 0 by message 0x3f3. The flag is the kicker class's own on/off, which the engine kickback (`KickActiveFlag`) does not map onto directly, so the engine default is kept.
- Pirates brig trap (`0x424210`, called from `0x429040` when a ball enters `s_hole19` outside states 0xc, 0xd and 0x11): decoded and ported. Queue (+0x192) minus one (not below 0), held count plus one, `s_oneway12` switched on at two held balls, and message 0x3fb makes the launcher serve a replacement ball (no queue check, `0x418950`). The third held ball starts Jail Break (`0x423630`, state 0xd, `0x42d590`): 100,000 and every held ball is served again. Ported: the held count, Jail Break at three, release of the held balls from `a_spot6` (one ball per held ball), and no counting during a multiball. Ported: `s_oneway12` is off at each ball start and in the drain (0x42d480, 0x4230c0) and on at two held balls. Not ported: the physical holding of the ball and the plunger replacement (the hole returns the ball itself). States 0xc/0xd/0x11 (`0x42d480`, `0x42d590`, `0x42d730`) add the held count to the queue when they start.

- Lava-Ball (`0x427540`, state 0xc start `0x42d480`): ported the queue of two balls and now also clears the held brig balls and the `s_oneway12` gate. The original also ejects from `a_sink8` (`0x423680`, see above) when zero or one ball is held; not ported.
