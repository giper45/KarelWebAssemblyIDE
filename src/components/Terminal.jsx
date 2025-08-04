import React, { useRef, useEffect, useState } from 'react'

// Funzione per convertire codici ANSI in HTML colorato
const convertAnsiToHtml = (text) => {
  if (!text) return ''
  
  // Mappa dei colori ANSI più comuni
  const ansiColors = {
    '0': '',        // reset
    '1': 'font-bold',        // bold
    '30': 'text-black',      // black
    '31': 'text-red-600',    // red
    '32': 'text-green-600',  // green
    // '33': 'text-yellow-800', // yellow
    '33': 'text-black', // yellow
    '34': 'text-blue-600',   // blue
    '35': 'text-purple-600', // magenta
    '36': 'text-black',   // cyan
    '37': 'text-gray-300',   // white
    '90': 'text-gray-500',   // bright black (gray)
    '91': 'text-red-400',    // bright red
    '92': 'text-green-400',  // bright green
    '93': 'text-black', // bright yellow
    '94': 'text-blue-400',   // bright blue
    '95': 'text-purple-400', // bright magenta
    '96': 'text-cyan-400',   // bright cyan
    '97': 'text-white',      // bright white
  }
  
  // Rimuovi sequenze di escape e converti in HTML
  let result = text
    // Converti newlines in <br> prima di processare i codici ANSI
    .replace(/\r\n/g, '\n')  // Normalizza line endings
    .replace(/\r/g, '\n')    // Converti CR in LF
    // Rimuovi caratteri di controllo comuni MA preserva newlines
    .replace(/\x1b\[[0-9;]*[a-zA-Z]/g, (match) => {
      // Estrai i codici numerici
      const codes = match.slice(2, -1).split(';')
      const classes = codes.map(code => ansiColors[code]).filter(Boolean)
      
      if (classes.length > 0) {
        return `<span class="${classes.join(' ')}">`
      }
      return ''
    })
    // Rimuovi altri caratteri di controllo MA preserva newlines (\n = \x0a)
    .replace(/[\x00-\x09\x0b-\x1f\x7f-\x9f]/g, '')
    // Converti newlines in <br> dopo aver processato i codici ANSI
    .replace(/\n/g, '<br>')
  
  // Chiudi i tag span aperti
  const openTags = (result.match(/<span/g) || []).length
  const closeTags = (result.match(/<\/span>/g) || []).length
  for (let i = 0; i < openTags - closeTags; i++) {
    result += '</span>'
  }
  
  return result
}

const Terminal = ({ output, onClearTerminal }) => {
  const terminalRef = useRef(null)
  const [terminalHeight, setTerminalHeight] = useState(240) // Altezza iniziale in px
  const [isResizing, setIsResizing] = useState(false)

  // Auto-scroll al fondo quando c'è nuovo output
  useEffect(() => {
    if (terminalRef.current) {
      terminalRef.current.scrollTop = terminalRef.current.scrollHeight
    }
  }, [output])

  // Gestione del resize
  const handleMouseDown = (e) => {
    setIsResizing(true)
    const startY = e.clientY
    const startHeight = terminalHeight

    const handleMouseMove = (e) => {
      const newHeight = startHeight - (e.clientY - startY)
      setTerminalHeight(Math.max(120, Math.min(600, newHeight))) // Min 120px, Max 600px
    }

    const handleMouseUp = () => {
      setIsResizing(false)
      document.removeEventListener('mousemove', handleMouseMove)
      document.removeEventListener('mouseup', handleMouseUp)
    }

    document.addEventListener('mousemove', handleMouseMove)
    document.addEventListener('mouseup', handleMouseUp)
  }

// ...existing code...
return (
  <div 
    className="w-full h-full border-t border-gray-200 bg-white flex flex-col shadow-lg"
    // style={{ height: terminalHeight, minHeight: 120, maxHeight: 600 }}
  >
    {/* Terminal Header */}
    <div className="flex items-center justify-between px-4 py-2 bg-gray-50 border-b border-gray-200">
      <div className="flex items-center gap-2">
        <div className="flex items-center gap-1">
          <div className="w-3 h-3 rounded-full bg-red-400"></div>
          <div className="w-3 h-3 rounded-full bg-yellow-400"></div>
          <div className="w-3 h-3 rounded-full bg-green-400"></div>
        </div>
        <span className="text-sm font-medium text-gray-600 ml-2">Terminal</span>
      </div>
      {onClearTerminal && (
        <button
          onClick={onClearTerminal}
          className="px-3 py-1 text-xs bg-gray-200 hover:bg-gray-300 text-gray-700 rounded transition-colors duration-200"
        >
          Clear
        </button>
      )}
    </div>
    
    <div
      ref={terminalRef}
      className="flex-1 p-4 overflow-y-auto text-gray-800 font-mono text-sm leading-relaxed 
                 scrollbar-thin scrollbar-thumb-gray-300 scrollbar-track-gray-100 bg-white w-full"
      style={{
        fontFamily: 'Monaco, "Cascadia Code", "SF Mono", Consolas, "Liberation Mono", Menlo, "Courier New", monospace',
      }}
    >
      {output ? (
        <div 
          className="whitespace-pre-wrap w-full"
          dangerouslySetInnerHTML={{ __html: convertAnsiToHtml(output) }}
        />
      ) : (
        <div className="text-gray-500">
          <span className="text-blue-600">karel@ide</span>
          <span className="text-gray-400">:</span>
          <span className="text-green-600">~</span>
          <span className="text-gray-400">$ </span>
          <span className="text-gray-500">Ready for C++ compilation...</span>
          <span className="animate-pulse text-blue-600">█</span>
        </div>
      )}
    </div>
  </div>
)
}
// ...existing code...}

export default Terminal