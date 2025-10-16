# Karel WebAssembly IDE
<p align="center">
  <img src="public/img/karel.png" alt="Karel Icon" width="120"/>
</p>


A modern, web-based integrated development environment for learning programming with Karel the Robot using C and WebAssembly.

Demo here:
https://karel.comics.unina.it

## 🤖 About Karel

Karel is a programming environment designed to teach fundamental programming concepts in a simple, visual way. Students write C code to control a robot (Karel) that moves around a grid world, picks up and puts down "beepers," and navigates around walls.

## 🚀 Features

- **Modern Web IDE**: Full-featured code editor with syntax highlighting and multiple keybinding modes (Vim, Emacs, Sublime)
- **Real-time Compilation**: C code is compiled to WebAssembly and executed directly in the browser
- **Visual Feedback**: Interactive canvas showing Karel's world with grid, walls, beepers, and robot position
- **Exercise System**: Structured learning path with categorized programming challenges
- **Responsive Design**: Works seamlessly on desktop and mobile devices
- **No Installation Required**: Everything runs in the browser - no setup needed

## 🛠️ Technology Stack

- **Frontend**: React 18 + Vite
- **Styling**: Tailwind CSS
- **Code Editor**: ACE Editor with C syntax highlighting
- **Compilation**: Clang/LLVM compiled to WebAssembly
- **Canvas Graphics**: HTML5 Canvas for Karel's world visualization
- **Build Tool**: Vite for fast development and optimized builds

## 🎯 Educational Goals

This IDE is designed to teach:
- Basic programming concepts (loops, conditionals, functions)
- Problem decomposition and algorithmic thinking
- C syntax and semantics
- Debugging and testing strategies
- Structured programming practices

## 🏗️ Project Structure

```
src/
├── components/          # React components
│   ├── Toolbar.jsx     # Main navigation bar
│   ├── Title.jsx       # Exercise title and metadata display
│   ├── TabComponent.jsx # Terminal and Canvas tabs
│   └── Sidebar.jsx     # Exercise navigation
├── assets/
│   └── exercise/       # Exercise definitions and worlds
public/
├── karel/
├── clang               # WebAssembly-compiled C compiler
├── lld                 # WebAssembly linker
└── memfs              # In-memory file system
```

## 🎮 Karel Programming API

The Karel library provides these core functions:

### Movement
- `karel_move()` - Move forward one step
- `karel_turn_left()` - Turn 90 degrees counter-clockwise

### Beeper Operations
- `karel_pick_beeper()` - Pick up a beeper from current location
- `karel_put_beeper()` - Put down a beeper at current location

### World Sensing
- `front_is_clear()` - Check if can move forward
- `beepers_present()` - Check if beeper exists at current location
- `facing_north()`, `facing_south()`, `facing_east()`, `facing_west()` - Direction checks

### World Setup
- `karel_add_beeper(x, y)` - Place beeper at coordinates
- `karel_add_horizontal_wall(x, y, length)` - Add horizontal wall(s)
- `karel_add_vertical_wall(x, y, length)` - Add vertical wall(s)

## 🚀 Getting Started

1. **Clone the repository**
   ```bash
   git clone https://github.com/giper45/KarelWebAssemblyIDE
   cd wasm-karen-clang
   ```

2. **Install dependencies**
   ```bash
   npm install
   ```

3. **Start development server**
   ```bash
   npm run dev
   ```

4. **Open your browser**
   Navigate to `http://localhost:5173`

## 📚 Exercise System

Exercises are organized in the `src/assets/exercise/` directory:

```
exercise/
└── 1/                  # Exercise ID
    ├── world.c         # World setup and robot behavior
    ├── exercise.c      # Student starting code
    ├── README.md       # Exercise description
    ├── SOLUTION.md     # Solution explanation
    └── metadata.json   # Exercise metadata
```

## 🎨 Customization

- **Themes**: Switch between Light, Dark, and Classic editor themes
- **Keybindings**: Choose from Vim, Emacs, or Sublime Text key mappings
- **Layout**: Responsive design adapts to different screen sizes

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for:
- New exercises and challenges
- UI/UX improvements
- Performance optimizations
- Bug fixes
- Documentation improvements

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 🙏 Acknowledgments

- Built on the WebAssembly compiler infrastructure by [@binji](https://github.com/binji)
- Inspired by Stanford's Karel programming environment
- Uses modern web technologies to make programming education accessible
- Copilot Pro from my educational account makes this project really easier to be implemented. Thank you very much for GitHub Education plan!. 
