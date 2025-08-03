import React from 'react'

const EditorSettings = ({ 
  keyboard, 
  onKeyboardChange, 
  theme, 
  onThemeChange, 
  showTiming, 
  onShowTimingChange 
}) => (
  <div className="flex items-center gap-3 p-3 bg-gray-50 border-b border-gray-200 overflow-x-auto">
    {/* Editor Keybinding */}
    <div className="flex items-center gap-2 bg-white px-3 py-2 rounded-lg border border-gray-200 shrink-0">
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

    {/* Theme Selection */}
    <div className="flex items-center gap-2 bg-white px-3 py-2 rounded-lg border border-gray-200 shrink-0">
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
    
    {/* Show Timing */}
    <div className="flex items-center gap-2 bg-white px-3 py-2 rounded-lg border border-gray-200 shrink-0">
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
  </div>
)

export default EditorSettings
