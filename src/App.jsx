import React, { useState, useEffect, useRef } from 'react'
import './App.css'
import { Toolbar, Terminal, Sidebar, Title, Footer } from './components'
import LoadingSpinner from './components/LoadingSpinner'
import TabComponent from './components/TabComponent';
import IsRunningButton from './components/IsRunningButton';
import IdeControls from './components/IdeControls';


// import CanvasPanel from './components/CanvasPanel';


const initialProgram = `#include "karel.h"
// Variabili globali di Karel
const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

void setup() {
    // Inizializza Karel e il mondo
    karel_init();
    
    // Aggiungi alcuni beeper nel mondo
    karel_add_beeper(3, 2);
    karel_add_beeper(5, 4);
    karel_add_beeper(7, 3);
    karel_add_beeper(2, 6);
    karel_add_horizontal_wall(3, 2, 2); // Horizontal wall (3,2)
    karel_add_vertical_wall(5, 1, 2);   // Vertical wall (5,1)
}
int i = 0;
void loop(double timeSec, double elapsedSec) {
    // Cancella il canvas
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    //printf("I %d", i);
    // Disegna il mondo di Karel
    //karel_refresh_state();
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    i++;
    if (i == 2)
    {
      printf("Put beeper");
      karel_put_beeper();
    }
    
    // Logica di Karel - Muoviti e raccogli beeper!
    static double lastMoveTime = 0;
    if(timeSec - lastMoveTime > 1.0) {
        
        // // Se c'è un beeper, raccoglilo
        // if(beepers_present()) {
        //     karel_pick_beeper();
        // }
        
        // Se puoi andare avanti, vai
        if(front_is_clear()) {
            karel_move();
        } else {
            // Altrimenti gira a sinistra
            karel_turn_left();
        }
        
        lastMoveTime = timeSec;
    }
}`;

function App() {
  const [code, setCode] = useState(initialProgram)
  const [keyboard, setKeyboard] = useState('sublime')
  const [theme, setTheme] = useState('github')
  const [showTiming, setShowTiming] = useState(false)
  const [terminalOutput, setTerminalOutput] = useState('')
  const [isRunning, setIsRunning] = useState(false)
  const [isLoading, setIsLoading] = useState(true)
  const [loadingMessage, setLoadingMessage] = useState('Initializing...')

  const editorRef = useRef(null)
  const terminalRef = useRef(null)
  const fileInputRef = useRef(null)
  const apiRef = useRef(null)


  const [currentExercise, setCurrentExercise] = useState({
    id: 1,
    name: "Karel Basic Movement",
    difficulty: "Easy",
    status: "in-progress"
  })

    const [isSidebarOpen, setIsSidebarOpen] = useState(false)


  const handleExerciseSelect = (exercise) => {
    setCurrentExercise(exercise)
    setIsSidebarOpen(false) // Chiudi sidebar su mobile dopo selezione
    
    // Qui potresti caricare il codice specifico dell'esercizio
    // setCode(getExerciseCode(exercise.id))
    // if (window.editor) {
    //   window.editor.setValue(getExerciseCode(exercise.id), -1)
    // }
  }

  const toggleSidebar = () => {
    setIsSidebarOpen(!isSidebarOpen)
  }

  const canvasRef = useRef(null);

  // Remove the local canvasRef, accept it as a prop instead
  // Remove this line: const canvasRef = useRef(null);
  useEffect(() => {
      if (canvasRef.current) {
      const canvas = canvasRef.current
      canvas.width = 800
      canvas.height = 600
      
      // Rendi il canvas disponibile globalmente come nell'originale
      window.canvas = canvas
      window.ctx2d = canvas.getContext('2d')
      
      setTerminalOutput(prev => prev + 'Canvas initialized.\n')
      }
  }, [])


  // Inizializza ACE Editor
  useEffect(() => {
    const loadAceScripts = async () => {
      try {
        setLoadingMessage('Loading code editor...')
        // Carica ACE base prima
        await loadScript('/lib/ace.js')

        // Aspetta che ace sia disponibile
        await waitForAce()

        setLoadingMessage('Loading editor modules...')
        // Carica i moduli aggiuntivi
        await loadScript('/lib/mode-c_cpp.js')
        await loadScript('/lib/keybinding-vim.js')

        setLoadingMessage('Initializing editor...')
        // Inizializza l'editor
        initializeEditor()
      } catch (error) {
        console.error('Failed to load ACE scripts:', error)
        setTerminalOutput(prev => prev + ` Editor initialization error: ${error.message}\n`)
      }
    }

    const waitForAce = () => {
      return new Promise((resolve) => {
        const checkAce = () => {
          if (window.ace) {
            resolve()
          } else {
            setTimeout(checkAce, 100)
          }
        }
        checkAce()
      })
    }

    const loadScript = (src) => {
      return new Promise((resolve, reject) => {
        if (document.querySelector(`script[src="${src}"]`)) {
          resolve()
          return
        }
        const script = document.createElement('script')
        script.src = src
        script.onload = resolve
        script.onerror = reject
        document.head.appendChild(script)
      })
    }

    const initializeEditor = () => {
      if (window.ace && editorRef.current) {
        try {
          const editor = window.ace.edit(editorRef.current)

          // Configura l'editor
          editor.session.setMode('ace/mode/c_cpp')
          editor.setTheme('ace/theme/github')

          // Configura opzioni (nomi corretti)
          editor.setOptions({
            enableBasicAutocompletion: false,
            enableLiveAutocompletion: false,
            showLineNumbers: true,
            fontSize: 18,
            wrap: true,
            showPrintMargin: false
          })

          editor.setValue(code, -1)

          // Imposta keybinding
          if (keyboard === 'vim') {
            editor.setKeyboardHandler('ace/keyboard/vim')
          }

          editor.on('change', () => {
            setCode(editor.getValue())
          })

          // Comando run con Ctrl+Enter
          editor.commands.addCommand({
            name: 'run',
            bindKey: { win: 'Ctrl+Enter', mac: 'Command+Enter' },
            exec: () => run()
          })

          window.editor = editor
          setTerminalOutput(prev => prev + 'Editor initialized.\n')
        } catch (error) {
          console.error('Error initializing editor:', error)
          setTerminalOutput(prev => prev + `Editor initialization error: ${error.message}\n`)
        }
      }
    }

    loadAceScripts()
  }, [])

  // Aggiorna keybinding quando cambia
  useEffect(() => {
    if (window.editor) {
      try {
        switch (keyboard) {
          case 'vim':
            window.editor.setKeyboardHandler('ace/keyboard/vim')
            break
          case 'emacs':
            window.editor.setKeyboardHandler('ace/keyboard/emacs')
            break
          case 'sublime':
            window.editor.setKeyboardHandler('ace/keyboard/sublime')
            break
          default:
            window.editor.setKeyboardHandler(null)
        }
      } catch (error) {
        console.warn(`Failed to set ${keyboard} keybinding:`, error)
      }
    }
  }, [keyboard])

  // Aggiorna tema quando cambia
  useEffect(() => {
    if (window.editor) {
      try {
        window.editor.setTheme(`ace/theme/${theme}`)
      } catch (error) {
        console.warn(`Failed to set ${theme} theme:`, error)
      }
    }
  }, [theme])

  // Inizializza WebAssembly API
  useEffect(() => {
    const initAPI = async () => {
      try {
        // Carica shared.js
        await loadScript('/shared.js')

        // Aspetta che API sia disponibile
        await waitForAPI()

        if (window.API) {
          const api = new window.API({
            readBuffer: async (filename) => {
              const response = await fetch(filename)
              return response.arrayBuffer()
            },
            compileStreaming: async (filename) => {
              const response = await fetch(filename)
              return WebAssembly.compile(await response.arrayBuffer())
            },
            hostWrite: (output) => {
              setTerminalOutput(prev => prev + output)
              // Auto-scroll terminal
              setTimeout(() => {
                if (terminalRef.current) {
                  terminalRef.current.scrollTop = terminalRef.current.scrollHeight
                }
              }, 0)
            },
            showTiming: showTiming,
            clang: 'clang',
            lld: 'lld',
            memfs: 'memfs',
            sysroot: 'sysroot.tar'
          })

          apiRef.current = api
          setTerminalOutput(prev => prev + 'WebAssembly API initialized.\n')
        }
      } catch (error) {
        console.error('Failed to initialize API:', error)
        setTerminalOutput(prev => prev + `Error initializing API: ${error.message}\n`)
      }
    }

    const waitForAPI = () => {
      return new Promise((resolve) => {
        const checkAPI = () => {
          if (window.API) {
            resolve()
          } else {
            setTimeout(checkAPI, 100)
          }
        }
        checkAPI()
      })
    }

    const loadScript = (src) => {
      return new Promise((resolve, reject) => {
        if (document.querySelector(`script[src="${src}"]`)) {
          resolve()
          return
        }
        const script = document.createElement('script')
        script.src = src
        script.onload = resolve
        script.onerror = reject
        document.head.appendChild(script)
      })
    }

    initAPI()
  }, [showTiming])

  // Configura canvas per WebAssembly
  // useEffect(() => {
  //   if (canvasRef.current) {
  //     const canvas = canvasRef.current
  //     canvas.width = 800
  //     canvas.height = 600

  //     // Rendi il canvas disponibile globalmente come nell'originale
  //     window.canvas = canvas
  //     window.ctx2d = canvas.getContext('2d')

  //     setTerminalOutput(prev => prev + 'Canvas initialized.\n')
  //   }
  // }, [])

  const run = async () => {
    if (!apiRef.current) {
      setTerminalOutput(prev => prev + 'Error: API not initialized\n')
      return
    }

    setIsRunning(true)
    setTerminalOutput(prev => prev + '\n--- Running program ---\n')

    try {
      await apiRef.current.compileLinkRun(code)
    } catch (error) {
      console.error('Error running program:', error)
      setTerminalOutput(prev => prev + `Error: ${error.message}\n`)
    } finally {
      setIsRunning(false)
    }
  }

  const handleOpenFileClick = () => {
    fileInputRef.current?.click()
  }


  const handleFileOpen = async (event) => {
    const file = event.target.files[0]
    if (file) {
      const text = await file.text()
      setCode(text)
      if (window.editor) {
        window.editor.setValue(text, -1)
      }
    }
    event.target.value = ''
  }

  const resetLayout = () => {
    if (confirm('Really reset?')) {
      setCode(initialProgram)
      setTerminalOutput('')
      if (window.editor) {
        window.editor.setValue(initialProgram, -1)
      }
    }
  }

  return (
    <div id="all" className="h-screen bg-gray-50 flex flex-col">
      {/* Input file nascosto */}
      <input
        ref={fileInputRef}
        type="file"
        hidden
        accept=".cpp,.c,.cc,.h"
        onChange={handleFileOpen}
      />
      {/* Sidebar */}
      <Sidebar
        isOpen={isSidebarOpen}
        onToggle={toggleSidebar}
        currentExercise={currentExercise}
        onExerciseSelect={handleExerciseSelect}
      />



      <Toolbar
        isRunning={isRunning}
        onRun={run}
        onOpenFile={handleOpenFileClick}
        keyboard={keyboard}
        onKeyboardChange={setKeyboard}
        showTiming={showTiming}
        onShowTimingChange={setShowTiming}
        onReset={resetLayout}
        theme={theme}
        onThemeChange={setTheme}
        onSidebarToggle={toggleSidebar}
      />



      {/* Title Section */}
      <Title
        exerciseName={currentExercise.name}
        difficulty={currentExercise.difficulty}
        status={currentExercise.status}
      />

      {/* IDE Controls Row */}
      <IdeControls
        isRunning={isRunning}
        onRun={run}
        onOpenFile={handleOpenFileClick}
        keyboard={keyboard}
        onKeyboardChange={setKeyboard}
        showTiming={showTiming}
        onShowTimingChange={setShowTiming}
        onReset={resetLayout}
        theme={theme}
        onThemeChange={setTheme}
      />

      {/* Layout principale */}
      <div className="flex flex-col flex-1 min-h-0">

        {/* Top row: Editor + Canvas */}
        <div className="flex flex-1 min-h-0">
          {/* Editor */}
          <div className="flex-1 border-r border-gray-300 bg-white shadow-sm">
            <div
              ref={editorRef}
              className="w-full h-full text-lg"
            />
          </div>

          {/* Canvas Panel */}
          <div className="flex-1 bg-gray-50">
            {/* <CanvasPanel /> */}
            <TabComponent
              terminalOutput={terminalOutput}
              canvasRef={canvasRef}
            />

            {/* Status Indicator */}
            <IsRunningButton
              isRunning={isRunning}
            />
          </div>
        </div>
      </div>
      <Footer />

    </div>
  )
}

export default App