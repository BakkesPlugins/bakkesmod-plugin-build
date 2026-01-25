# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial composite action structure
- Support for BakkesMod plugin builds
- Configurable build parameters
- Artifact output handling
- New `plugin-outdir` input parameter to override the plugin output directory (default: `plugins\`)
- Support for custom output directories via MSBuild `/p:OutDir=` parameter

### Changed
- Build step now passes the `plugin-outdir` parameter to MSBuild to override project-level `<OutDir>` settings
- Artifact preparation step now uses the configured `plugin-outdir` to locate build outputs
- Added backwards compatibility fallback to search legacy `plugins/` directory if custom outdir is not found
- N/A

### Deprecated
- N/A

### Removed
- N/A

### Fixed
- vcpkg manifest (`vcpkg.json`) is now checked in the same directory as the solution file instead of the workspace root

### Security
- N/A

## [1.0.0] - 2025-11-08

### Added
- Initial release of BakkesMod Plugin Build Action
- Basic build functionality
- Input validation
- Output generation
- Documentation and examples