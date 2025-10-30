import os
import subprocess

REPLACE = {
    # "COMPILATIONDB_INCLUDE_TOOLCHAIN": True,
    # "COMPILATIONDB_PATH": os.path.join("$BUILD_DIR", "compile_commands.json"),
    "COMPILATIONDBTC_INCLUDE_TOOLCHAIN": True,
    "COMPILATIONDBTC_PATH": os.path.join("$BUILD_DIR", "compile_commands.json"),
}

Import("env")  # type:ignore
env.Replace(**REPLACE)  # type:ignore

# https://github.com/platformio/platformio-core/issues/4711
if "compiledb" not in COMMAND_LINE_TARGETS:  # type:ignore
    subprocess.run(["pio", "run", "--target", "compiledb"])
