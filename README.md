# Satellite Visualizer

A lightweight C application that reads TLE data, calculates satellite positions using the SGP4 algorithm, and renders them in real time with Raylib.

* I plan on refactoring this project into a fully fledged C++ application because 
  over time I realise the needs of this and my ability to structure code could 
  benefit from generics/object oriented concepts * 

## Features

- TLE parsing from file (name + 2 lines per satellite)
- Real-time orbital position updates (SGP4-based, WIP)
- Basic 2D visualization with zoom/camera controls
- Modular C codebase (TLE, SGP4, rendering separated)

## How It Works

1. Reads satellites from a TLE file (3 lines per object).
2. Parses each into a struct and computes position (SGP4 in progress).
3. Renders names and coordinates using Raylib.
4. Basic debug info shown on screen.

## Evolution/Progress track pictures of project:

Early rendering tests

<img width="1922" height="1119" alt="Screenshot from 2025-07-22 15-21-25" src="https://github.com/user-attachments/assets/09d9fac6-8c07-4b9b-b8af-38dd9284fd38" />


Trail of newly launched starlink satellites 

![image](https://github.com/user-attachments/assets/32fc949e-7b03-4249-aa60-e0a40df65348)

<img width="1922" height="1119" alt="Screenshot from 2025-07-22 15-23-13" src="https://github.com/user-attachments/assets/c4c2f71a-e3bf-4690-83e9-9d4e2af2c643" />



## Requirements

- Raylib (v4.5+)
- GCC or Clang
- `make`
- Optional: `curl` (for future remote fetching)

## Known Issues

- TLE file must have line count divisible by 3.
- SGP4 still under development.
- Some TLEs may not parse or propagate correctly.

## Credits

- SGP4: Vallado/Kelso public-domain models  
- Raylib: Rendering and window management  
- Written in C for performance and control

## License

MIT License

## Disclaimer

This tool is for educational use only.  
Do **not** use it for real-world satellite tracking or commercial orbit propagation.  
SGP4 was developed by the U.S. Air Force and is provided here without any guarantees of accuracy or fitness for operational use.  
Use at your own risk.




