# Changelog

## v0.1.2 — Single-ZIP update
- Package the complete project and CI workflow in one ZIP upload.
- Update workflow now installs only `.github/workflows/ci.yml` from the uploaded ZIP.
- Preserve the active unpack workflow and all other `.github/` files.
- Reject unsafe ZIP paths and symbolic links before extraction.
- Keep additive-only source extraction and explicitly dispatch CI after commit.

# Changelog

All notable changes are documented here.

## [0.1.1] - 2026-11-11

### Fixed
- CI uses the official devkitPro devkitARM container, avoiding the HTTP 403 bootstrap failure from apt.devkitpro.org.
- Corrected the Makefile to follow Butano's documented template variables and include path.
- CI preserves the actual compiler output as an artifact.

## [0.1.0] - 2026-11-11

### Added
- Initial Butano/devkitARM project foundation.
- Phase 1 combat state model and GBA input mapping.
- GitHub Actions CI, ZIP unpack workflow, and Dependabot configuration.

### Known limitations
- Not the complete 40-character game.
- Final original sprite art, audio, stages, tag-team systems, modes, save data and multiplayer remain future work.
