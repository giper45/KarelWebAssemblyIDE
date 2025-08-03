import React, { useRef, useEffect } from 'react'

const Terminal = ({ output }) => {
  const terminalRef = useRef(null)

  // Auto-scroll al fondo quando c'è nuovo output
  useEffect(() => {
    if (terminalRef.current) {
      terminalRef.current.scrollTop = terminalRef.current.scrollHeight
    }
  }, [output])

  return (
    <div className="h-60 border-t border-gray-200 bg-white flex flex-col rounded-b-xl overflow-hidden shadow-inner">
      {/* Terminal header */}
      <div className="px-4 py-2 bg-gray-100 border-b border-gray-200 flex items-center space-x-3">
        {/* Traffic lights */}
        <div className="flex space-x-1">
          <div className="w-3 h-3 bg-red-400 rounded-full" />
          <div className="w-3 h-3 bg-yellow-400 rounded-full" />
          <div className="w-3 h-3 bg-green-400 rounded-full" />
        </div>
        {/* Label */}
        <div className="flex items-center space-x-2 text-gray-700">
          <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
            <path fillRule="evenodd" d="M2 5a2 2 0 012-2h12a2 2 0 012 2v10a2 2 0 01-2 2H4a2 2 0 01-2-2V5zm3.293 1.293a1 1 0 011.414 0l3 3a1 1 0 010 1.414l-3 3a1 1 0 01-1.414-1.414L7.586 10 5.293 7.707a1 1 0 010-1.414zM11 12a1 1 0 100 2h3a1 1 0 100-2h-3z" clipRule="evenodd" />
          </svg>
          <span className="text-sm font-medium">Output Terminal</span>
        </div>
        <div className="ml-auto">
          <div className="text-xs text-gray-500 bg-gray-200 px-2 py-1 rounded">
            Ctrl+Enter to run
          </div>
        </div>
      </div>

      
      {/* Area del terminale */}
      <div
        ref={terminalRef}
        className="flex-1 p-4 overflow-y-auto text-gray-800 font-mono text-sm leading-relaxed 
                   scrollbar-thin scrollbar-thumb-gray-300 scrollbar-track-gray-100 bg-white"
        style={{
          fontFamily: 'Monaco, "Cascadia Code", "SF Mono", Consolas, "Liberation Mono", Menlo, "Courier New", monospace',
        }}
      >
        <pre className="whitespace-pre-wrap">
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

export default Terminal