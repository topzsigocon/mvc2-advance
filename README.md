# Marvel vs. Capcom 2: New Age of Heroes – GBA Fan Edition

**Non-commercial fan project.** Not affiliated with Marvel, Capcom, or any official product.  
All graphics, audio, and code are original placeholders created for this homebrew.

Inspired by the classic 3-vs-3 tag-team fighter. Built with **C++** and the **Butano** GBA engine.

## Phase 1 Status (current)

- Core game loop + scene manager
- Main menu (Arcade / Versus / Training)
- Character select skeleton (pick up to 3, order, random ready for expansion)
- Two placeholder fighters (Ryu / Spider-Man style names)
- Basic movement, jump-ready structure, Light / Medium / Heavy attacks
- Simple CPU opponent
- Health, timer, combo counter (text HUD)
- GBA controls
- GitHub Actions CI that produces a `.gba` artifact

Later phases will add real pixel art, full roster, specials, hypers, assists, stages, sound, and modes.

## Requirements (local build)

1. [devkitPro](https://devkitpro.org/wiki/Getting_Started) with **GBA Development** component (devkitARM).
2. [Butano](https://github.com/GValiente/butano) (clone or download a release).
3. Python 3.
4. `make`.

## Build

```bash
# Clone this repo
git clone <your-repo-url>
cd mvc2-gba-fan

# Point LIBBUTANO in Makefile to your Butano installation
# Example: LIBBUTANO := /path/to/butano/butano

make -j$(nproc)
```

Output: `mvc2_gba_fan.gba`

Run in mGBA, VBA-M, RetroArch, or real GBA hardware.

## Controls (Phase 1)

| Input     | Action                  |
|-----------|-------------------------|
| D-Pad     | Move / Navigate menus   |
| A         | Light attack / Confirm  |
| B         | Medium attack / Back    |
| L         | Heavy attack            |
| R         | (reserved for assist)   |
| Start     | Pause / Confirm         |
| Select    | Return to menu (end of fight) |

## GitHub Actions / Zip Update Workflow

This project uses the **upload-zip-only** update style.

### One-time setup (sa GitHub website)

1. **Settings → Actions → General → Workflow permissions**  
   Piliin ang **Read and write permissions** → **Save**.

2. I-create ang mga workflow file (kung wala pa):
   - Add file → Create new file → pangalan: `.github/workflows/ci.yml` → i-paste ang content → Commit.
   - Ulitin para sa `.github/workflows/unpack.yml`.
   - (Opsyonal) `.github/dependabot.yml`.

3. Subukan: mag-upload ng maliit na `.zip` sa root o sa `updates/` folder.  
   Pumunta sa **Actions** at tingnan kung tumakbo ang **Unpack update** at **CI**.  
   Kunin ang `.gba` sa **Artifacts**.

### Paano mag-update gamit ang zip

1. Gumawa ng zip ng buong project **o** patch (mga binagong file lang).
2. Pangalan: `mvc2-gba-fan-vX.Y.Z.zip` o `-patch`.
3. I-upload sa GitHub (root o `updates/`).
4. Ang **Unpack update** workflow ay:
   - Mag-extract (tinatanggal ang wrapper folder kung may `Makefile` sa loob),
   - Mag-commit,
   - Magti-trigger ng **CI** na magbu-build ng bagong `.gba`.
5. I-download ang artifact mula sa Actions.

**Tandaan:** Hindi ginagalaw ng unpack ang `.github/` (limitasyon ng `GITHUB_TOKEN`). Kung may bagong workflow, i-paste nang manual sa website.

## Project structure

```
mvc2-gba-fan/
├── src/                  # C++ sources
│   ├── main.cpp
│   ├── main_menu_scene.cpp
│   ├── character_select_scene.cpp
│   └── battle_scene.cpp
├── include/              # Headers
├── graphics/             # BMP + JSON for Butano (add real sprites later)
├── audio/                # Maxmod assets later
├── Makefile
├── .github/workflows/
│   ├── ci.yml
│   └── unpack.yml
├── CHANGELOG.md
└── README.md
```

## Disclaimer

This is a non-commercial fan-made homebrew project for educational and entertainment purposes only.  
It does not use or redistribute any proprietary Marvel or Capcom assets, sprites, music, or ROM data.  
All character names are used under fair-use parody / fan-game context.  
Do not sell or commercially distribute this project.

## Credits

- Engine: [Butano](https://github.com/GValiente/butano) by GValiente
- Toolchain: [devkitPro](https://devkitpro.org)
- Inspiration: Marvel vs. Capcom 2: New Age of Heroes (Capcom)
