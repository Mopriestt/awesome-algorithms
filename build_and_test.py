#!/usr/bin/env python3
import shutil
import subprocess
import sys
from pathlib import Path
import platform


def run(cmd, cwd: Path):
    print(f"\n>>> Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=str(cwd))
    if result.returncode != 0:
        print(f"\n!!! Command failed with exit code {result.returncode}: {' '.join(cmd)}")
        sys.exit(result.returncode)


def main():
    repo_root = Path(__file__).resolve().parent
    build_dir = repo_root / "build"

    print(f"Repository root: {repo_root}")

    # 1. Cleanup build directory
    if build_dir.exists():
        print(f"\n>>> Removing existing build directory: {build_dir}")
        shutil.rmtree(build_dir)

    # 2. CMake configure
    cmake_args = ["-S", ".", "-B", "build"]
    
    if platform.system() == "Windows":
        if not shutil.which("cl") and shutil.which("gcc"):
            print(">>> MSVC (cl.exe) not found, but GCC detected. Using 'MinGW Makefiles'.")
            cmake_args.extend(["-G", "MinGW Makefiles"])

    run(["cmake"] + cmake_args, cwd=repo_root)

    # 3. CMake build
    is_windows = platform.system() == "Windows"

    build_cmd = ["cmake", "--build", "build"]
    if is_windows:
        build_cmd += ["--config", "Debug"]

    run(build_cmd, cwd=repo_root)

    # 4. CTest
    ctest_cmd = ["ctest", "--test-dir", "build", "--output-on-failure"]
    if is_windows:
        ctest_cmd += ["-C", "Debug"]

    run(ctest_cmd, cwd=repo_root)

    print("\nBuild and tests finished successfully.")

if __name__ == "__main__":
    main()
