# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0] - 2025-08-05

### Added
- Documentation dialog system with help
- code editor features with language support extensions
- Comprehensive exercise system covering:
  - C language fundamentals
  - Functions and scope management  
  - Arrays and string manipulation
  - Control structures and conditional logic
  - Basic algorithms and data structures
- Karel robot visual improvements with WebAssembly icon-inspired design
- Canvas rendering buffer system for smooth animations
- Simulated environment for accurate state prediction
- Multiple exercise categories with progressive difficulty
- Enhanced Karel API with complete movement and detection capabilities
- Improved robot rendering with directional arrows and styled appearance
- karel command translated to English for better accessibility


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
