# Marvel vs. Capcom 2: New Age of Heroes — GBA Fan Edition

**Unofficial, non-commercial fan project. Not affiliated with or endorsed by Marvel, Capcom, or Nintendo.**

This repository is an **early Phase 1 engineering scaffold (v0.1.2)**, not the completed game and not yet a playable visual demo. It establishes a Butano/devkitARM C++ project, a first-pass combat-state model, build automation, and the ZIP-update workflow. The current main loop does not yet render fighters or a battle HUD, and no successful ROM build has been verified in this environment. The GitHub CI workflow is intended to produce the `.gba` artifact after the repository is uploaded and built successfully.

## Current status

- [x] Butano project layout and Makefile
- [x] First-pass C++ combat model: health, facing, movement, jump, guard, attack cooldown and hitstun
- [x] GBA input polling mapped to combat input
- [x] CI build definition, ROM validation, artifact upload and build-log artifact
- [x] ZIP upload/unpack workflow and Dependabot
- [ ] Fighter/background rendering and battle HUD (required before this is visually playable)
- [ ] Original sprite sheets, animation sets, stages, music and SFX
- [ ] 3v3 team selection, assists, tags, hyper combos
- [ ] Full 40-character roster and game modes

The current code is a non-visual combat-logic scaffold. It is not yet a playable fighting-game ROM. The next required implementation step is the rendering layer (original fighter sprites, background, health bars and text HUD), followed by emulator testing. Add original art/audio only; do not copy assets from commercial games.

## Requirements

- Butano (the CI workflow clones the upstream repository)
- devkitARM / devkitPro GBA Development group
- GNU Make

## Local build

1. Install devkitPro and its **GBA Development** component.
2. Clone Butano into the repository root as `butano/`:
   `git clone https://github.com/GValiente/butano.git butano`
3. Build from the project root with `make -j`.
4. Output: `mvc2_gba_fan_edition.gba`.

See the [official Butano devkitARM setup guide](https://gvaliente.github.io/butano/getting_started_dka.html).

## Planned controls (once the rendering/gameplay scene is integrated)

- D-pad: move / crouch / jump
- A: light attack
- B: heavy attack
- L: guard
- R: special attack (prototype)
- START: pause/resume

## GitHub Actions

The `CI` workflow uses the official `devkitpro/devkitarm` container image instead of bootstrapping devkitPro from `apt.devkitpro.org`, clones Butano, builds the ROM, validates its size, and uploads the ROM and compiler log under **Actions → workflow run → Artifacts**.

### One-time GitHub setup (Tagalog)

1. Gumawa ng GitHub repository at i-upload ang laman ng project ZIP.
2. Sa **Settings → Actions → General → Workflow permissions**, piliin ang **Read and write permissions**, pagkatapos Save. (Kailangan ito ng unpack workflow para makapag-commit ng ZIP updates.)
3. Sa unang setup lang, ilagay ang `.github/workflows/unpack.yml` sa repository gamit ang **Add file → Create new file** o GitHub web upload. I-enable ang Actions workflows kung hihingin. Ang kasunod na updates ay iisang ZIP na lang.
4. Para sa unang ROM build, buksan ang **Actions → CI → Run workflow**. Pagkatapos ng successful run, kunin ang `.gba` sa **Artifacts**.

### Paano mag-update gamit ang ZIP

1. I-upload ang iisang buong project ZIP sa repository root (huwag sa `updates/` kung root upload ang gamit). Dapat kasama sa ZIP ang `README.md` at `.github/workflows/ci.yml`.
2. Awtomatikong ive-verify ang ZIP, ia-update ang project files, at papalitan lamang ang `.github/workflows/ci.yml` mula sa ZIP. Hindi nito papalitan ang kasalukuyang `unpack.yml`, Dependabot, o ibang workflow files.
3. Awtomatikong aalisin ang uploaded ZIP, gagawa ng commit, at tatawagin ang CI build.
4. Tingnan ang **Actions → CI → Artifacts** para sa `.gba` ROM at build logs.
5. Additive ang source update: hindi nito binubura ang lumang source files. Kung kailangang magtanggal ng file, gawin iyon nang mano-mano.
6. Huwag kailanman maglagay ng passwords, keys, tokens, o secrets sa ZIP/repository.

## License and asset policy

Code: MIT unless otherwise noted. Butano remains under its own zlib license. All game characters, logos, portraits, stages, audio and other game assets must be original fan-created work or properly licensed. This project must not redistribute proprietary sprites, music, voice clips, ROM data, or extracted assets.
