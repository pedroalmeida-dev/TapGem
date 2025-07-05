## 💎 Tap Gem

**Genre**: Puzzle Game  
**Technologies**: C++, SDL2, SDL_image, SDL_ttf, SDL_mixer  
**Development Time**: ~1 week (Technical Challenge)  
**Team Size**: 1  

**Description**:  
Tap Gem is a 2D puzzle game prototype developed as part of a technical challenge, inspired by *Ores*. Players interact with colored blocks to solve puzzles within a limited number of moves. The gameplay loop is structured to be responsive and efficient, with clear separation of game systems.

**Architecture**:  
- Built from scratch in C++ using SDL  
- Game loop with fixed timestep logic (60 FPS)  
- Central `GameManager` controlling game state and update flow  
- Mouse input system with real-time tracking and state transitions  
- Event-driven window focus handling  
- Integrated audio and font rendering via SDL_mixer and SDL_ttf  

**Highlights**:
- Implemented core game loop with delta time control  
- Designed clean object-oriented structure using singletons and managers  
- Handled real-time input and window focus state  
- Managed rendering, update logic, and memory cleanup manually  
- Built with maintainability in mind, modular structure split across `Game`, `GameManager`, `MouseInput`, etc.

**My Role**:  
I designed and programmed the entire codebase, from SDL initialization to game loop, input, rendering, and resource cleanup. The project showcases my ability to rapidly deliver polished, low-level gameplay prototypes under time constraints.
