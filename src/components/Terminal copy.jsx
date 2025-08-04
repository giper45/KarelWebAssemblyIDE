import React, { useRef, useEffect, useState } from 'react'

const Terminal = ({ output }) => {
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
    {/* ...header e resize handle... */}
    <div
      ref={terminalRef}
      className="flex-1 p-4 overflow-y-auto text-gray-800 font-mono text-sm leading-relaxed 
                 scrollbar-thin scrollbar-thumb-gray-300 scrollbar-track-gray-100 bg-white w-full"
      style={{
        fontFamily: 'Monaco, "Cascadia Code", "SF Mono", Consolas, "Liberation Mono", Menlo, "Courier New", monospace',
      }}
    >
      <pre className="whitespace-pre-wrap w-full">
        {output ? output : (
          <div className="text-gray-500">
            <span className="text-blue-600">karel@ide</span>
            <span className="text-gray-400">:</span>
            <span className="text-green-600">~</span>
            <span className="text-gray-400">$ </span>
            <span className="text-gray-500">Ready for C++ compilation...</span>
            <span className="animate-pulse text-blue-600">█</span>
          </div>
        )}
      </pre>
    </div>
  </div>
)
}
// ...existing code...}

export default Terminal