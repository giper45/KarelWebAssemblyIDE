// Hook per gestire l'inizializzazione dell'API WebAssembly
import { useEffect, useRef } from 'react'

export const useWebAssemblyAPI = (showTiming, onLog) => {
  const apiRef = useRef(null)

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
              if (onLog) onLog(output)
            },
            showTiming: showTiming,
            clang: 'clang',
            lld: 'lld', 
            memfs: 'memfs',
            sysroot: 'sysroot.tar'
          })
          
          apiRef.current = api
          if (onLog) onLog('WebAssembly API initialized.\n')
        }
      } catch (error) {
        console.error('Failed to initialize API:', error)
        if (onLog) onLog(`Error initializing API: ${error.message}\n`)
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
  }, [showTiming, onLog])

  return apiRef.current
}

export default useWebAssemblyAPI
