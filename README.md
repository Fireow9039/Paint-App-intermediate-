# Paint-App-intermediate-

Here’s a README.md file tailored for your graphical paint application using SFML with features like color selection, undo/redo, and eraser support:

🖼️ Simple Graphical Paint App (SFML)

This is a lightweight graphical paint application built using SFML (Simple and Fast Multimedia Library) in C++. It offers a simple drawing canvas with five color options, an eraser, undo/redo functionality, and an intuitive sidebar-based UI.

🎯 Features
🎨 Color Palette: Black, Red, Green, Blue, Yellow
🧽 Eraser Tool
🔄 Undo (↩️) and Redo (↪️) with keyboard-free interaction
🖱️ Mouse-Based Drawing
🖼️ Sidebar Layout (No scrollbars or additional GUI windows)
💾 Canvas Save Option (in extended version)
🧰 Requirements
C++ Compiler (C++17 or later)
SFML Library (version 2.5+ recommended)
Installation (macOS via Homebrew):

brew install sfml
Compile:

g++ main.cpp -o PaintApp -lsfml-graphics -lsfml-window -lsfml-system
🚀 How to Run
./PaintApp
🕹️ Usage
Use your mouse to draw on the canvas.
Select a color from the sidebar to draw with.
Click the 🧽 button to switch to eraser mode.
Click ↩️ to undo and ↪️ to redo your last changes.
All tools are located on the left sidebar (no scrollbars).
📸 Interface Layout
[ Sidebar ]
🎨 Color Options
🧽 Eraser
↩️ Undo
↪️ Redo

[ Canvas Area ]
Draw here with your mouse!
📝 Future Enhancements
Add Save/Export button to store drawings
Adjustable brush size
Shape tools (rectangle, circle, etc.)
Keyboard shortcuts
