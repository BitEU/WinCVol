# WinCVol - Windows Master Volume Control

A simple, lightweight command-line utility for controlling Windows master volume with an interactive text-based user interface (TUI).

## Features

- **Real-time volume control** with visual feedback
- **Interactive TUI** with a graphical volume bar
- **Multiple control methods**:
  - Fine adjustment: `+`/`-` keys (5% increments)
  - Preset levels: Number keys `0-9` (0%-90% in 10% steps)
- **Live volume display** showing current volume percentage
- **Clean, intuitive interface** that updates in real-time

## Screenshots

```
Windows Master Volume Control
=============================

Use '+' to increase volume, '-' to decrease.
Press number keys: 0=0%, 1=10%, 2=20%, 3=30%, 4=40%, 5=50%
                   6=60%, 7=70%, 8=80%, 9=90%
Press 'q' to quit.

Current Volume: [#########################                         ] 50%
```

## Requirements

- **Windows OS** (Vista or later)
- **Microsoft Visual C++ Compiler** (MSVC) or Visual Studio Build Tools
- **Windows SDK** (for Core Audio APIs)

## Building

### Using the provided build script:
```cmd
build.bat
```

### Manual compilation:
```cmd
cl volume_control.c /link Ole32.lib
```

This will produce `volume_control.exe` in the current directory.

## Usage

1. Run the executable:
   ```cmd
   volume_control.exe
   ```

2. Use the following controls:
   - **`+` or `=`**: Increase volume by 5%
   - **`-`**: Decrease volume by 5%
   - **`0-9`**: Set volume to specific percentage (0%-90%)
   - **`q` or `Q`**: Quit the program

3. The interface will update in real-time showing:
   - Current volume percentage
   - Visual volume bar
   - Available controls

## Technical Details

This program uses the Windows Core Audio APIs to control the master volume:

- **COM Interface**: Uses `IMMDeviceEnumerator` and `IAudioEndpointVolume`
- **Audio Endpoint**: Controls the default audio rendering device
- **Volume Range**: 0.0 to 1.0 (0% to 100%)
- **Real-time Updates**: Continuously polls and displays current volume level

### Key Windows APIs Used:
- `CoInitialize()` - Initialize COM
- `CoCreateInstance()` - Create device enumerator
- `GetDefaultAudioEndpoint()` - Get default audio device
- `GetMasterVolumeLevelScalar()` - Read current volume
- `SetMasterVolumeLevelScalar()` - Set new volume level

## File Structure

```
WinCVol/
├── volume_control.c    # Main source code
├── build.bat          # Build script
├── volume_control.exe # Compiled executable (after build)
├── volume_control.obj # Object file (after build)
└── README.md          # This file
```

## License

This is a simple utility program. Feel free to use, modify, and distribute as needed.

## Troubleshooting

**Build Issues:**
- Ensure you have MSVC compiler installed
- Make sure Windows SDK is available
- Run build from a Visual Studio Command Prompt

**Runtime Issues:**
- Program requires Windows Vista or later
- Ensure your system has audio devices configured
- Run with appropriate permissions if needed

**No Audio Device:**
- Check Windows audio settings
- Ensure default playback device is set
- Verify audio drivers are installed

## Contributing

This is a simple demonstration program. Potential improvements could include:
- Support for individual application volume control
- Audio device selection
- Mute/unmute functionality
- Configuration file support
- Hotkey support for background operation
