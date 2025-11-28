# realtime-vehicle-visualization


A lightweight C++ real-time rendering engine that simulates a simplified in-vehicle driver-assist visualization, similar to the systems used in modern EVs.
The project renders a 3D scene consisting of an ego vehicle, nearby cars, lane geometry, and sensor-driven movement — all updated every frame in real time.

This project was built to strengthen my understanding of real-time rendering, graphics pipelines, and 3D vehicle visualization workflows used in automotive HMI systems.

🚗 Features

Real-time 3D rendering loop (OpenGL + C++)

Camera system (follow mode + chase view)

Scene graph with entities (ego car, road, other vehicles)

Basic Phong lighting + materials

Model loading (GLTF via tinygltf or Assimp)

Simple simulated “sensor data” controlling surrounding vehicles

Clean modular engine structure:

Renderer

Camera

Scene + entities

Shader abstraction

Model / Mesh pipeline

🧱 Tech Stack

C++17

OpenGL 4.x

GLFW (windowing)

GLAD (OpenGL loader)

GLM (math)

Assimp or tinygltf (3D model loading)

Python (optional) for simulated sensor feed

Kotlin (optional) for Android controller app
