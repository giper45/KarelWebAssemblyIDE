# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Modern web interface for Karel the Robot programming
- ACE code editor with C++ support and syntax highlighting
- WebAssembly compilation system with Clang/LLVM
- Interactive canvas for Karel world visualization
- Structured exercise system with categories
- Navigable sidebar for exercise selection
- Support for multiple keybindings (Vim, Emacs, Sublime)
- Editor themes (Light, Dark, Classic)
- Integrated terminal for output
- Complete Karel API for movement, detection and beeper manipulation
- Horizontal and vertical wall system
- Real-time Karel world rendering

### Features
- **Code Editor**: ACE editor with C++ highlighting, auto-completion and customizable keybindings
- **WebAssembly Compilation**: In-browser C++ code compilation using Clang/LLVM
- **Visual World**: 10x8 grid with Karel, beepers, walls and status information
- **Exercise System**: Modular structure for progressive programming exercises
- **Responsive Interface**: Modern design with Tailwind CSS optimized for desktop and mobile
- **Fast Development**: Hot reload with Vite for rapid development

### Technical Stack
- **Frontend**: React 18 + Vite
- **Styling**: Tailwind CSS 4.x
- **Editor**: ACE Editor
- **Compilation**: Clang/LLVM WebAssembly
- **Canvas**: HTML5 Canvas API
- **Build**: Vite with ES modules support

## [0.0.1] - 2025-08-03

### Added
- Initial project setup
- Vite configuration with React 19
- Tailwind CSS 4.x integration
- Modular component base structure
- Build system and dependencies

### Dependencies
- React 19.1.0
- Tailwind CSS 4.1.11
- Vite 7.0.4
- ACE Editor (via CDN)
- ESLint configurazione

### Project Structure
```
wasm-karen-clang/
├── src/
│   ├── components/     # Modular React components
│   ├── assets/         # Resources and exercises
│   └── hooks/          # Custom React hooks
├── public/             # Static WebAssembly files
├── lib/                # JavaScript libraries
└── include/            # C++ headers
```

### Notes
- First functional version of Karel IDE
- Exercise system in development
- WebAssembly API fully integrated
- Support for educational C++ programming
