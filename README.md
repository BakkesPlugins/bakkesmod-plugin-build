# BakkesMod Plugin Build Action

A reusable GitHub composite action for building BakkesMod plugins.

## Description

This action provides a standardized way to build BakkesMod plugins in GitHub Actions workflows. It handles the setup of the build environment, dependencies, and compilation process.

### Features

- **Dual Artifact System**: Automatically creates two artifact sets:
  - Debug artifacts (with PDB files) for debugging
  - Public release artifacts (without PDB files) for distribution
- **Automatic vcpkg Integration**: Detects `vcpkg.json` manifest and automatically sets up vcpkg dependencies
- **Build Error Reporting**: Captures and displays MSBuild errors in GitHub Actions summary and workflow logs
- **Flexible SDK Versioning**: Supports specifying custom BakkesMod SDK and vcpkg references

## Usage

```yaml
name: Build Plugin
on: [push, pull_request]

jobs:
  build:
    runs-on: windows-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4
      
      - name: Build BakkesMod Plugin
        uses: Bakkesplugins/bakkesmod-plugin-build@v1.0.0
        with:
          build-config: 'Release'
          bakkesmod-sdk-ref: 'master'
          vcpkg-ref: 'master'
          retention-days: '30'
```

## Inputs

| Input | Description | Required | Default |
|-------|-------------|----------|---------|
| `build-config` | Build configuration (Debug or Release) | No | `Release` |
| `bakkesmod-sdk-ref` | Git reference for BakkesMod SDK (branch, tag, or commit) | No | `master` |
| `vcpkg-ref` | Git reference for vcpkg (branch, tag, or commit) | No | `master` |
| `retention-days` | Number of days to retain build artifacts | No | `30` |
| `plugin-outdir` | Output directory for the plugin build. Can be an absolute path, a relative path (relative to solution directory), or use MSBuild variables like `$(SolutionDir)`. This value is passed to MSBuild as `/p:OutDir=` to override the project settings. | No | `plugins\` |

## Outputs

| Output | Description |
|--------|-------------|
| `artifact-name` | Name of the uploaded debug artifact (with PDB files) |
| `zip-path` | Path to the created debug release zip file (with PDB files) |
| `public-artifact-name` | Name of the uploaded public release artifact (without PDB files) |
| `public-zip-path` | Path to the public release zip file (without PDB files) |
| `build-status` | Status of the build process (`success` or `failed`) |
| `build-exit-code` | Exit code from the MSBuild process |

## Requirements

- Windows runner (BakkesMod plugins are Windows-specific)
- Visual Studio Build Tools or Visual Studio Community (automatically provided by `windows-latest` runner)
- MSBuild (set up automatically via `microsoft/setup-msbuild@v2`)
- A `.sln` (solution) file in your repository
- **Optional**: `vcpkg.json` manifest for external dependencies

## Example with Outputs

```yaml
- name: Build BakkesMod Plugin
  id: build-plugin
  uses: Bakkesplugins/bakkesmod-plugin-build@v1.0.0
  with:
    build-config: 'Release'
    retention-days: '7'

- name: Check build results
  if: always()
  run: |
    echo "Build status: ${{ steps.build-plugin.outputs.build-status }}"
    echo "Build exit code: ${{ steps.build-plugin.outputs.build-exit-code }}"
    echo "Debug artifact: ${{ steps.build-plugin.outputs.artifact-name }}"
    echo "Public artifact: ${{ steps.build-plugin.outputs.public-artifact-name }}"

- name: Use debug artifacts
  if: steps.build-plugin.outputs.build-status == 'success'
  run: |
    echo "Debug build with PDB files: ${{ steps.build-plugin.outputs.zip-path }}"
    echo "Public release: ${{ steps.build-plugin.outputs.public-zip-path }}"
```

## Advanced Usage

### Custom Output Directory

If your project uses a custom output directory instead of the default `plugins\`, you can specify it with the `plugin-outdir` parameter:

```yaml
- name: Build BakkesMod Plugin
  uses: Bakkesplugins/bakkesmod-plugin-build@v1.0.0
  with:
    build-config: 'Release'
    plugin-outdir: 'bin\'  # Custom output directory
```

The `plugin-outdir` parameter supports MSBuild variables like `$(SolutionDir)` and can be either:
- A relative path (e.g., `bin\`, `output\plugins\`)
- An absolute path
- A path with MSBuild variables (e.g., `$(SolutionDir)bin\`)

This is useful when your project's `.vcxproj` file has a custom `<OutDir>` setting that differs from the default `$(SolutionDir)plugins\`.

### Using vcpkg Dependencies

If your plugin uses external libraries, create a `vcpkg.json` manifest in your repository root:

```json
{
  "name": "my-plugin",
  "version": "1.0.0",
  "dependencies": [
    "fmt",
    "nlohmann-json"
  ]
}
```

The action will automatically detect and install these dependencies during the build process.

### Accessing Both Artifact Types

The action creates two separate artifact uploads:

1. **Debug Artifacts** (includes PDB files) - Use for debugging and development
2. **Public Artifacts** (excludes PDB files) - Use for end-user distribution

Both artifacts include:
- Compiled plugin DLL files from the `plugins/` directory
- Any data files from the `data/` directory (if present)

## Development

To contribute to this action:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test the action locally
5. Submit a pull request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Support

For issues and questions:
- Open an issue on GitHub
- Contact the BakkesPlugins community

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for detailed version history.

### Latest Changes
- Dual artifact system (debug with PDB, public without PDB)
- Automatic vcpkg manifest detection and integration
- Enhanced build error reporting in GitHub Actions summary
- Support for both solution-relative and workspace-root plugin/data directories
