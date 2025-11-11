import os


# ANSI color codes
class Colors:
    """ANSI color codes for terminal output"""
    RESET = "\033[0m"
    BOLD = "\033[1m"
    
    # Foreground colors
    BLACK = "\033[30m"
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    MAGENTA = "\033[35m"
    CYAN = "\033[36m"
    WHITE = "\033[37m"
    
    # Bright colors
    BRIGHT_GREEN = "\033[92m"
    BRIGHT_YELLOW = "\033[93m"
    BRIGHT_BLUE = "\033[94m"
    BRIGHT_MAGENTA = "\033[95m"
    BRIGHT_CYAN = "\033[96m"


def parse_env_file(path):
    """
    Parse a .env file and return a dictionary of key-value pairs.
    
    Args:
        path: Path to the .env file
        
    Returns:
        Dictionary of environment variables, or empty dict if file not found
    """
    if not os.path.exists(path):
        print(f"{Colors.YELLOW}⚠️  [load_env.py] Warning: .env file not found at {path}{Colors.RESET}")
        return {}
    
    try:
        with open(path) as f:
            return dict(
                line.strip().split("=", 1)
                for line in f
                if "=" in line and not line.startswith("#")
            )
    except Exception as e:
        print(f"{Colors.RED}❌ [load_env.py] Error parsing .env file: {e}{Colors.RESET}")
        return {}


# Import the PlatformIO build environment
Import("env")

# Load environment variables from .env file
vars = parse_env_file(".env")

if vars:
    print(f"{Colors.BRIGHT_GREEN}✅ [load_env.py] Successfully loaded environment variables:{Colors.RESET}")
    for key, value in vars.items():
        # Convert value to proper C macro format with proper escaping
        value = env.StringifyMacro(value.strip())
        env.Append(CPPDEFINES=[(key, value)])
        print(f"{Colors.BRIGHT_CYAN}   📌 {Colors.BOLD}{key}{Colors.RESET}{Colors.BRIGHT_CYAN}={value}{Colors.RESET}")
else:
    print(f"{Colors.YELLOW}⚠️  [load_env.py] No environment variables loaded from .env{Colors.RESET}")
