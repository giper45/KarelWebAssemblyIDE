
import React from 'react'
import SidebarOpenButton from './SidebarOpenButton'

const ToolbarControls = ({
  isRunning,
  onRun,
  onOpenFile,
  keyboard,
  onKeyboardChange,
  showTiming,
  onShowTimingChange,
  onReset,
  theme,
  onThemeChange
}) => (
  <div className="flex-1 flex flex-row h-full m-3 items-center gap-2 min-w-0 overflow-x-auto scrollbar-thin scrollbar-thumb-gray-300 scrollbar-track-gray-100 py-1 pl-4 pr-4">
    <button 
      onClick={onRun} 
      disabled={isRunning}
      className="flex items-center justify-center gap-2 shrink-0 px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600 disabled:opacity-50 disabled:cursor-not-allowed transition-colors font-medium"
    >
      {isRunning ? (
        <>
          <div className="w-4 h-4 border-2 border-white border-t-transparent rounded-full animate-spin"></div>
          Running...
        </>
      ) : (
        <>
          <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
            <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clipRule="evenodd" />
          </svg>
          Run
        </>
      )}
    </button>
  
    <div>
      <button 
        onClick={onOpenFile}
        className="flex items-center gap-2 shrink-0 px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600 transition-colors font-medium"
      >
        <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
          <path fillRule="evenodd" d="M3 17a1 1 0 011-1h12a1 1 0 110 2H4a1 1 0 01-1-1zm3.293-7.707a1 1 0 011.414 0L9 10.586V3a1 1 0 112 0v7.586l1.293-1.293a1 1 0 111.414 1.414l-3 3a1 1 0 01-1.414 0l-3-3a1 1 0 010-1.414z" clipRule="evenodd" />
        </svg>
        Open
      </button>
    </div>

    <div className="flex items-center gap-2 bg-gray-50 px-3 py-2 rounded-lg border border-gray-200 shrink-0">
      <label className="text-xs font-medium text-gray-700">Editor</label>
      <select 
        value={keyboard} 
        onChange={(e) => onKeyboardChange(e.target.value)}
        className="text-sm border border-gray-300 rounded px-2 py-1 bg-white min-w-0"
      >
        <option value="vim">Vim</option>
        <option value="emacs">Emacs</option>
        <option value="sublime">Sublime</option>
      </select>
    </div>

    <div className="flex items-center gap-2 bg-gray-50 px-3 py-2 rounded-lg border border-gray-200 shrink-0">
      <label className="text-xs font-medium text-gray-700">Theme</label>
      <select 
        value={theme}
        onChange={(e) => onThemeChange(e.target.value)}
        className="text-sm border border-gray-300 rounded px-2 py-1 bg-white min-w-0"
      >
        <option value="github">Light</option>
        <option value="monokai">Dark</option>
        <option value="textmate">Classic</option>
      </select>
    </div>
    
    <div className="flex items-center gap-2 bg-gray-50 px-3 py-2 rounded-lg border border-gray-200 shrink-0">
      <input 
        type="checkbox"
        checked={showTiming}
        onChange={(e) => onShowTimingChange(e.target.checked)}
        className="w-4 h-4 text-blue-600 border-gray-300 rounded focus:ring-blue-500"
      />
      <label className="text-xs font-medium text-gray-700">
        Show timing
      </label>
    </div>
    
    <div>
      <button 
        onClick={onReset}
        className="flex items-center gap-2 shrink-0 px-4 py-2 bg-red-500 text-white rounded-lg hover:bg-red-600 transition-colors font-medium"
      >
        <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
          <path fillRule="evenodd" d="M4 2a1 1 0 011 1v2.101a7.002 7.002 0 0111.601 2.566 1 1 0 11-1.885.666A5.002 5.002 0 005.999 7H9a1 1 0 010 2H4a1 1 0 01-1-1V3a1 1 0 011-1zm.008 9.057a1 1 0 011.276.61A5.002 5.002 0 0014.001 13H11a1 1 0 110-2h5a1 1 0 011 1v5a1 1 0 11-2 0v-2.101a7.002 7.002 0 01-11.601-2.566 1 1 0 01.61-1.276z" clipRule="evenodd" />
        </svg>
        Reset
      </button>
    </div>
  </div>
);

const Toolbar = ({ 
  isRunning, 
  onRun, 
  onOpenFile, 
  keyboard, 
  onKeyboardChange, 
  showTiming, 
  onShowTimingChange, 
  onReset,
  theme,
  onThemeChange,
  onSidebarToggle
}) => {
  return (

    <header className="w-full bg-white border-b border-gray-200 shadow-sm z-20 h-16">
      <div className="flex flex-row items-center justify-center h-full px-4 py-2 gap-2 w-full min-w-0">
        <SidebarOpenButton
          onSidebarToggle={onSidebarToggle}
        />
        {/* Project Name */}
        <div className="flex-1 flex flex-col justify-center min-w-0 pl-8 pr-4">
          <span className="text-base font-bold text-gray-900 leading-tight truncate">
            Karel WebAssembly IDE
          </span>
          <span className="text-xs text-gray-400 font-mono tracking-wide truncate">
            Modern C++ Playground
          </span>
        </div>
        {/* Toolbar Controls */}
        <ToolbarControls
          isRunning={isRunning}
          onRun={onRun}
          onOpenFile={onOpenFile}
          keyboard={keyboard}
          onKeyboardChange={onKeyboardChange}
          showTiming={showTiming}
          onShowTimingChange={onShowTimingChange}
          onReset={onReset}
          theme={theme}
          onThemeChange={onThemeChange}
        />
      </div>
    </header>
  )
}

export default Toolbar