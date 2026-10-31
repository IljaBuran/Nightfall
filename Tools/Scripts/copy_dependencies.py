# AI-GENERATED (Claude Opus 5.5): finished the runtime-dependency copy script on request.
# Copies third-party runtime binaries (Agility SDK, DXC) next to the built executable.

import argparse
import shutil
import sys
from pathlib import Path


def resolve_platform(machine: str) -> str:
    machine = machine.lower()
    if machine in ("amd64", "x86_64"):
        return "x64"
    if machine in ("arm64", "aarch64"):
        return "arm64"
    raise RuntimeError(f"Unsupported platform: {machine}")


# Resolve relative to this script, not the caller's working directory.
SCRIPT_DIR   = Path(__file__).resolve().parent.parent
PROJECT_ROOT = SCRIPT_DIR.parent
THIRD_PARTY  = PROJECT_ROOT / "ThirdParty"

# [source relative to ThirdParty/, destination folder relative to output, configurations]
# "{platform}" is substituted with x64 / arm64.
FILES_TO_COPY = [
    ("Engine/DirectXAgilitySDK/Bin/{platform}/D3D12Core.dll",      "D3D12", {"Debug", "Release"}),
    ("Engine/DirectXAgilitySDK/Bin/{platform}/d3d12SDKLayers.dll", "D3D12", {"Debug"}),
    ("Engine/DirectXShaderCompiler/Bin/{platform}/dxcompiler.dll", "",      {"Debug", "Release"}),
    ("Engine/DirectXShaderCompiler/Bin/{platform}/dxil.dll",       "",      {"Debug", "Release"}),
]


def is_up_to_date(src: Path, dst: Path) -> bool:
    if not dst.exists():
        return False
    s, d = src.stat(), dst.stat()
    return s.st_size == d.st_size and int(s.st_mtime) <= int(d.st_mtime)


def main() -> int:
    parser = argparse.ArgumentParser(prefix_chars="-/")
    parser.add_argument("/output", "--output", required=True, type=Path)
    parser.add_argument("/platform", "--platform", default=..., choices=["x64", "arm64"])
    parser.add_argument("/configuration", "--configuration", required=True, choices=["Debug", "Release"])
    args = parser.parse_args()

    # Strip stray quote left by MSBuild when $(OutDir) ends with a backslash.
    output_dir = Path(str(args.output).rstrip('"')).resolve()

    errors = 0
    for src_rel, dst_rel, configs in FILES_TO_COPY:
        if args.configuration not in configs:
            continue

        src = THIRD_PARTY / src_rel.format(platform=args.platform)
        dst_dir = output_dir / dst_rel
        dst = dst_dir / src.name

        if not src.is_file():
            print(f"error: missing dependency: {src}", file=sys.stderr)
            errors += 1
            continue

        if is_up_to_date(src, dst):
            continue

        dst_dir.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        print(f"Copied {src.name} -> {dst}")

    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
