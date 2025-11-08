# BakkesMod Plugin Build Action

A reusable GitHub composite action for building BakkesMod plugins.

## Description

This action provides a standardized way to build BakkesMod plugins in GitHub Actions workflows. It handles the setup of the build environment, dependencies, and compilation process.

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
        uses: Bakkesplugins-Review-Testing/bakkesmod-plugin-build@v1
        with:
          build-config: 'Release'
          bakkesmod-sdk-ref: 'main'
          vcpkg-ref: 'master'
          retention-days: '30'
```

## Inputs

| Input | Description | Required | Default |
|-------|-------------|----------|---------|
| `build-config` | Build configuration (Debug or Release) | No | `Release` |
| `bakkesmod-sdk-ref` | Git reference for BakkesMod SDK (branch, tag, or commit) | No | `main` |
| `vcpkg-ref` | Git reference for vcpkg (branch, tag, or commit) | No | `master` |
| `retention-days` | Number of days to retain build artifacts | No | `30` |

## Outputs

| Output | Description |
|--------|-------------|
| `artifact-name` | Name of the uploaded artifact |
| `zip-path` | Path to the created release zip file |
| `build-status` | Status of the build process |

## Requirements

- Windows runner (BakkesMod plugins are Windows-specific)
- Visual Studio Build Tools or Visual Studio Community
- CMake (if using CMake-based builds)

## Example with Outputs

```yaml
- name: Build BakkesMod Plugin
  id: build-plugin
  uses: Bakkesplugins-Review-Testing/bakkesmod-plugin-build@v1
  with:
    build-config: 'Release'
    retention-days: '7'

- name: Download and use artifacts
  if: steps.build-plugin.outputs.build-status == 'success'
  run: |
    echo "Build completed successfully!"
    echo "Artifact name: ${{ steps.build-plugin.outputs.artifact-name }}"
    echo "Zip file created: ${{ steps.build-plugin.outputs.zip-path }}"
```

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

### v1.0.0
- Initial release
- Basic build functionality for BakkesMod plugins