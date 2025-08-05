import React, { useState, useEffect, useRef } from 'react'
import './App.css'
import { Toolbar, Terminal, Sidebar, Title, Footer } from './components'
import { useExerciseData } from './hooks/useExerciseData';
import LoadingSpinner from './components/LoadingSpinner'
import TabComponent from './components/TabComponent';
import IsRunningButton from './components/IsRunningButton';
import IdeControls from './components/IdeControls';
import DocumentationDialog from './components/DocumentationDialog';

import { saveCodeToLocalStorage, saveCurrentExerciseToLocalStorage, getCodeFromLocalStorage, getCurrentExerciseFromLocalStorage, isCodePresentInLocalStorage, isExercisePresentInLocalStorage } from './utils/localStorageUtils';


// import CanvasPanel from './components/CanvasPanel';


// const initialProgram = `#include "karel.h"
// // Variabili globali di Karel
// const char* DIRECTION_NAMES[] = {"Est", "Nord", "Ovest", "Sud"};

// void setup() {
//     // Inizializza Karel e il mondo
//     karel_init();

//     // Aggiungi alcuni beeper nel mondo
//     karel_add_beeper(3, 2);
//     karel_add_beeper(5, 4);
//     karel_add_beeper(7, 3);
//     karel_add_beeper(2, 6);
//     karel_add_horizontal_wall(3, 2, 2); // Horizontal wall (3,2)
//     karel_add_vertical_wall(5, 1, 2);   // Vertical wall (5,1)
// }
// int i = 0;
// void loop(double timeSec, double elapsedSec) {
//     // Cancella il canvas
//     canvas_setFillStyleZ("white");
//     canvas_fillRect(0, 0, 800, 600);
//     //printf("I %d", i);
//     // Disegna il mondo di Karel
//     //karel_refresh_state();
//     drawWalls();
//     drawGrid();
//     drawBeepers();
//     drawKarel();
//     drawInfo();
//     i++;
//     if (i == 2)
//     {
//       printf("Put beeper");
//       karel_put_beeper();
//     }

//     // Logica di Karel - Muoviti e raccogli beeper!
//     static double lastMoveTime = 0;
//     if(timeSec - lastMoveTime > 1.0) {

//         // // Se c'è un beeper, raccoglilo
//         // if(beepers_present()) {
//         //     karel_pick_beeper();
//         // }

//         // Se puoi andare avanti, vai
//         if(front_is_clear()) {
//             karel_move();
//         } else {
//             // Altrimenti gira a sinistra
//             karel_turn_left();
//         }

//         lastMoveTime = timeSec;
//     }
// }`;

function App() {
  // const [code, setCode] = useState(null)
  const [keyboard, setKeyboard] = useState('sublime')
  const [theme, setTheme] = useState('github')
  const [showTiming, setShowTiming] = useState(false)
  const [terminalOutput, setTerminalOutput] = useState('')
  const [isRunning, setIsRunning] = useState(false)
  const [isActive, setIsActive] = useState(false)
  const [editorEventConfigured, setEditorEventConfigured] = useState(false)
  const [isHelpDialogOpen, setIsHelpDialogOpen] = useState(false)
  // const [loadingMessage, setLoadingMessage] = useState('Initializing...')
  const [editorInitialized, setEditorInitialized] = useState(false)
  const [activeTab, setActiveTab] = useState('readme');
  const editorRef = useRef(null)
  const terminalRef = useRef(null)
  const fileInputRef = useRef(null)
  const apiRef = useRef(null)


  const {
    categories,
    exercises,
    loading,
    error,
    loadingProgress,
    loadingMessage,
    getExercisesByCategory,
    getPreviousExercise,
    getNextExercise,
    getExercise,

  } = useExerciseData();

  // Stato per sidebar e esercizio corrente
  const [isSidebarOpen, setIsSidebarOpen] = useState(false);
  const [currentExercise, setCurrentExercise] = useState(exercises[0]);
  // const [currentExerciseId, setCurrentExerciseId] = useState(1);
  // Ottieni l'esercizio corrente solo se i dati sono caricati
  // const currentExercise = !loading ? getExercise(currentExerciseId) : null;
  const uploadCodeFromEditor = () => {
    const editor = window.ace.edit(editorRef.current);
    setCurrentExercise({
      ...currentExercise,
      exerciseCode: editor.getValue()
    });
  }

  // Quando selezioni un esercizio dalla sidebar
  const handleExerciseSelect = (exercise) => {
    console.log("Handle Exercise Select");
    setCurrentExercise(exercise);
    // setCurrentExerciseId(exercise.id);
    setIsSidebarOpen(false);
    // Qui puoi anche caricare il codice nell'editor, ecc.
  };

  const toggleSidebar = () => {
    setIsSidebarOpen(!isSidebarOpen)
  }

  const handleHelpClick = () => {
    setIsHelpDialogOpen(true)
  }

  const handleHelpClose = () => {
    setIsHelpDialogOpen(false)
  }

  const handleClearTerminal = () => {
    setTerminalOutput('')
  }

  // const resetWorld = async () => {
  //   await safeStop()
  //   console.log("COMPILE LINK RUN")
  //   apiRef.current.compileLinkRun(currentExercise.worldCode)
  // }



  const canvasRef = useRef(null);
  // Aggiorna il codice quando cambia l'esercizio e i dati sono caricati
  useEffect(() => {
    if (!loading && !currentExercise) {
      setCurrentExercise(getExercise(1))
      // if (currentExercise && currentExercise.exerciseCode) {
      //   setCode(currentExercise.exerciseCode);
      // }
    }
  }, [loading]);

  //   useEffect(() => {
  //   if (window.ace && editorRef.current && !editorEventConfigured) {
  //     setEditorEventConfigured(true);
  //     const editor = window.ace.edit(editorRef.current);

  //     // Imposta il valore iniziale
  //     editor.setValue(currentExercise.exerciseCode, -1);

  //     // Listener per l'evento di modifica
  //     const handleChange = () => {
  //       if (editor.getValue() != currentExercise.exerciseCode && editor.getValue() != "")
  //       {
  //         console.log("IN HANDLE CHANGE")
  //         setCurrentExercise({
  //           ...currentExercise,
  //           exerciseCode: editor.getValue()
  //         })

  //       }
  //       // Se vuoi aggiornare anche currentExercise:
  //       // setCurrentExercise(prev => ({ ...prev, exerciseCode: editor.getValue() }));
  //     };

  //     editor.on('change', handleChange);

  //     // Cleanup: rimuovi il listener quando il componente si smonta
  //     return () => {
  //       console.log("CLEANUP")
  //       editor.off('change', handleChange);
  //     };
  //   }
  // }, [editorRef, window.ace]);

  // Remove the local canvasRef, accept it as a prop instead
  // Remove this line: const canvasRef = useRef(null);
  useEffect(() => {
    if (!loading && canvasRef.current && currentExercise) {
      // if (canvasRef.current) {
      const canvas = canvasRef.current
      canvas.width = 800
      canvas.height = 600

      // Rendi il canvas disponibile globalmente 
      window.canvas = canvas
      window.ctx2d = canvas.getContext('2d')

      setTerminalOutput(prev => prev + 'Canvas initialized.\n')
    }
  }, [loading, canvasRef, currentExercise])


      //   let code = ""
      //   let exercise = null

      //   if (isCodePresentInLocalStorage())
      //     code = getCodeFromLocalStorage()
      //   if (isExercisePresentInLocalStorage()) {
      //   exercise = getCurrentExerciseFromLocalStorage()
      //   if (exercise && code) {
      //     exercise.exerciseCode = code
      //   }
      // }
        
      //   // Not found exercise
      //   if (!exercise) {
      //     exercise = firstExercise
      //     if (code != "")
      //       exercise.exerciseCode = code
      //   }
      //   setCurrentExercise(exercise)
      //   const editor = window.ace.edit(editorRef.current);
      //   editor.setValue(exercise.exerciseCode)
  // When current exercise changes, compile the worldCode and update the editor page. In addition, change the stored code in the local storage
  useEffect(() => {
    console.log("Before everything")
    console.log(currentExercise)
    let localCode = null
    let localExercise = null 
    if (isCodePresentInLocalStorage())
      localCode = getCodeFromLocalStorage()
    if (isExercisePresentInLocalStorage())
      localExercise = getCurrentExerciseFromLocalStorage()

    if (localExercise)
    {
      if (localCode) {
        localExercise.exerciseCode = localCode
      }
      setCurrentExercise(localExercise)
      console.log("Set current work")
    }
    
  }, [])
  useEffect(() => {
    console.log("In update editor")
    if (editorRef && editorRef.current && currentExercise && window.ace) {
      const editor = window.ace.edit(editorRef.current)
      console.log(currentExercise.exerciseCode)
      let exerciseCode;
      // If undefined try to take from local storage, otherwise defaut exercise 1
      if (!currentExercise.exerciseCode)
      {
        if (isCodePresentInLocalStorage())
        {
          exerciseCode = getCodeFromLocalStorage()
          // setCurrentExercise(
          //   ...currentExercise,
          //   exerciseCode
          // )
        }
        else 
        {
          exerciseCode = getExercise(1).exerciseCode
        }
      }
      else
      {
        exerciseCode = currentExercise.exerciseCode
      }
      editor.setValue(exerciseCode, -1)
      // async function _world() 
      // {
      //   await resetWorld()

      // }
      // _world()
      if (exerciseCode)
        saveCodeToLocalStorage(exerciseCode)
      if (currentExercise)
        saveCurrentExerciseToLocalStorage(currentExercise)

    }
  }, [currentExercise, editorRef, window.ace])

  // Inizializza ACE Editor
  useEffect(() => {
    console.log("Init ACE")
    if (!loading && canvasRef.current && currentExercise) {
      const loadAceScripts = async () => {
        try {
          // setLoadingMessage('Loading code editor...')
          // Carica ACE base prima
          await loadScript('/lib/ace.js')

          // Aspetta che ace sia disponibile
          await waitForAce()

          // setLoadingMessage('Loading editor modules...')
          // Carica i moduli aggiuntivi
          await loadScript('/lib/mode-c_cpp.js')
          await loadScript('/lib/keybinding-vim.js')

          await loadScript('/lib/ext-searchbox.js')
          await loadScript('/lib/ext-language_tools.js')

          // setLoadingMessage('Initializing editor...')
          // Inizializza l'editor
          initializeEditor()
          setEditorInitialized(true)
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
              maxLines: Infinity,
              autoScrollEditorIntoView: true,
              showPrintMargin: false,
              enableSearchTools: true,
              // enableSnippets: true,
              // enableEmmet: false
            })

            //   // Enable search
            // editor.commands.addCommand({
            //   name: 'find',
            //   bindKey: { win: 'Ctrl+F', mac: 'Command+F' },
            //   exec: function(editor) {
            //     editor.execCommand('find')
            //   }
            // })

            editor.setValue(currentExercise.exerciseCode, -1)

            // Imposta keybinding
            if (keyboard === 'vim') {
              editor.setKeyboardHandler('ace/keyboard/vim')
            }

            editor.on('change', () => {
              const code = editor.getValue();
              saveCodeToLocalStorage(code)
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
    }


  }, [loading, canvasRef, currentExercise])

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

  const safeStop = async () => {
      const USER_STOP = 0xC1C1A
      try {
        await apiRef.current.stop()
      }
      catch (error) {
        if (error.code == USER_STOP) {
          console.log("OK - Safe exit by user")
          return 0
        }
      else {
        throw Error("Some error in stop program");
      }

  }
}
  const run = async () => {
    let _isActive = true
    if (!apiRef.current) {
      setTerminalOutput(prev => prev + 'Error: API not initialized\n')
      return
    }
    await safeStop()
    handleClearTerminal()
    setActiveTab('terminal');
    uploadCodeFromEditor();
    setIsRunning(true);
    setIsActive(_isActive);
    setTerminalOutput(prev => prev + '\n--- Running program ---\n')

    try {
      await apiRef.current.compileLinkRun(editor.getValue())
    } 
    catch (error) {
        console.error('Error running program:', error)
        _isActive = false
        setIsActive(_isActive);
        // setTerminalOutput(prev => prev + `Error: ${error.message}\n`)

      
    } finally {
      setIsRunning(false)
      _isActive ? setActiveTab('world') : setActiveTab('terminal')
    }

  }

  const handleOpenFileClick = () => {
    fileInputRef.current?.click()
  }


  const handleFileOpen = async (event) => {
    const file = event.target.files[0]
    if (file) {
      const text = await file.text()
      setCurrentExercise({
        ...currentExercise,
        exerciseCode: text,
      })
      // setCode(text)
      if (window.editor) {
        window.editor.setValue(text, -1)
      }
    }
    event.target.value = ''
  }

  const resetLayout = async () => {
    // if (confirm('Really reset?')) {
    // setCode(initialProgram)
    // setTerminalOutput('');
    setIsActive(false);
    // if (window.editor) {
    //   window.editor.setValue(initialProgram, -1)
    // }
    // apiRef.current.stop();
    await safeStop()
    // }
  }
  const handleChangeTab = (tab) => {
    setActiveTab(tab);
  }


  const handlePreviousExercise = () => {
    const currentIndex = currentExercise.id;
    if (currentIndex > 0) {
      // const previousExercise = exercises[currentIndex - 1];
      const previousExercise = getPreviousExercise(currentIndex)
      handleExerciseSelect(previousExercise);
    }
  };

  const handleNextExercise = () => {
    const currentIndex = currentExercise.id;
    // const nextExercise = exercises[currentIndex + 1];
    const nextExercise = getNextExercise(currentIndex)
    handleExerciseSelect(nextExercise);
  };

  // Verifica se ci sono esercizi precedenti/successivi
  const hasPreviousExercise = () => {
    const currentIndex = currentExercise.id;
    return currentIndex > 1;
  };

  const hasNextExercise = () => {
    const currentIndex = currentExercise.id;
    return currentIndex < Object.keys(exercises).length;
  };


  return (
    <div id="all" className="min-h-screen bg-gray-50 flex flex-col">
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
        onExerciseSelect={handleExerciseSelect}
        currentExerciseId={currentExercise?.id}
        categories={categories}
        loading={loading}
        error={error}
        getExercisesByCategory={getExercisesByCategory}
        onToggle={toggleSidebar}
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
        onHelpClick={handleHelpClick}
      />



      {loading && 
      <LoadingSpinner 
        message={loadingMessage}
        progress={loadingProgress}
      />}
      {/* Title Section */}
      {!loading && currentExercise && (
        <div className="flex flex-col flex-1 h-full w-full">
          <Title
            idExercise={currentExercise.id}
            exerciseName={currentExercise.name}
            difficulty={currentExercise.difficulty}
            status={currentExercise.status}
          />

          {/* IDE Controls Row */}
          <IdeControls
            isRunning={isRunning}
            isActive={isActive}
            onRun={run}
            onOpenFile={handleOpenFileClick}
            keyboard={keyboard}
            onKeyboardChange={setKeyboard}
            showTiming={showTiming}
            onShowTimingChange={setShowTiming}
            onReset={resetLayout}
            theme={theme}
            onThemeChange={setTheme}
            onPrevious={handlePreviousExercise}
            onNext={handleNextExercise}
            hasPrevious={hasPreviousExercise()}
            hasNext={hasNextExercise()}
          />

          {/* Layout principale */}
          <div className="flex flex-1 h-full min-h-0 overlow-y-auto">

            {/* Top row: Editor + Canvas */}
            {/* Editor */}
            <div className="flex-1 border-r border-gray-300 bg-white shadow-sm">
              <div
                ref={editorRef}
                className="w-full h-full text-lg"
              />
            </div>

            {/* Canvas Panel */}
            <div className="flex-1 w-1/2 h-full shrink-0 bg-gray-50">
              {/* <CanvasPanel /> */}
              <TabComponent
                terminalOutput={terminalOutput}
                canvasRef={canvasRef}
                activeTab={activeTab}
                onChangeTab={handleChangeTab}
                readme={currentExercise.readme}
                solution={currentExercise.solution}
                isActive={isActive}
                onClearTerminal={handleClearTerminal}
              />

              {/* Status Indicator */}
              <IsRunningButton
                isRunning={isRunning}
              />
            </div>
          </div>
        </div>
      )}
      <Footer />

      {/* Documentation Dialog */}
      <DocumentationDialog 
        isOpen={isHelpDialogOpen}
        onClose={handleHelpClose}
      />

    </div>
  )
}

export default App