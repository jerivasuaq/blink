import os


def parse_env_file(path):
    """Parse .env file and return a dictionary of key-value pairs"""
    env_vars = {}
    if os.path.exists(path):
        with open(path) as f:
            for line in f:
                line = line.strip()
                if "=" in line and not line.startswith("#"):
                    key, value = line.split("=", 1)
                    env_vars[key.strip()] = value.strip()
    return env_vars


# Import the current construction environment
# alias of `env = DefaultEnvironment()`
Import("env")

# Load variables from .env file
vars = parse_env_file(".env")

print("[load_env.py] Loaded environment variables:")
for key, value in vars.items():
    # Convert value to proper C macro format
    value = env.StringifyMacro(value.strip())
    env.Append(CPPDEFINES=[(key, value)])
    print(f"[load_env.py] Added CPPDEFINE: {key}={value}")
