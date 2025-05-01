# 🚀 Satellite Visualizer - MVP Implementation Checklist

## 🛠️ Phase 1: Core Infrastructure
- [ ] Set up a C project structure with `main.c` and simple build system (e.g., Makefile)
- [ ] Integrate Raylib and create a basic 3D window with a camera
- [ ] Load and render a simple Earth sphere (`GenMeshSphere` + `DrawModel`)

## 🛰️ Phase 2: Satellite Data Input
- [ ] Write a Python script to fetch TLEs from Celestrak
- [ ] Parse the TLEs into structs (`tle_t`) and serialize them to a `.bin` file
- [ ] In C, write a loader to read the `.bin` file into a `tle_t[]` array

## 🧮 Phase 3: Orbit Propagation
- [ ] Integrate a C implementation of the SGP4 algorithm (e.g., Vallado or libsgp4)
- [ ] For each satellite, compute its position (ECI) based on current time
- [ ] Store results in a `satellite_t` struct with position and velocity

## 🌍 Phase 4: Visualization
- [ ] For each satellite, draw a small sphere at its computed position
- [ ] Color them all the same for now
- [ ] Use `Camera3D` controls to move around and inspect the scene

## 🕒 Phase 5: Real-Time Clock + Prediction Mode
- [ ] Add a simulation clock based on UTC or system time
- [ ] Allow toggling between real-time and "predict mode" (keyboard toggle)
- [ ] In predict mode, allow moving a time slider with left/right arrows (+/- minutes)

## 💡 Phase 6: Quality-of-Life Improvements
- [ ] Display basic text UI (e.g., number of satellites, current mode, time offset)
- [ ] Print satellite name and info on keypress or hover (basic)
- [ ] Cap number of satellites (e.g., 500) to maintain performance while testing

---

## 🎯 MVP Milestone Reached
- [ ] A spinning Earth
- [ ] Real satellites in correct 3D orbits
- [ ] Real-time or predicted positions
- [ ] A fast, responsive app with minimal dependencies
