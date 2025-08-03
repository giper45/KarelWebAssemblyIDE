
import React from 'react'
import SidebarOpenButton from './SidebarOpenButton'

const Toolbar = ({ onSidebarToggle }) => {
  return (
    <header className="w-full bg-white border-b border-gray-200 shadow-sm z-20 h-16">
      <div className="flex flex-row items-center h-full px-4 py-2 gap-2 w-full min-w-0">
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
      </div>
    </header>
  )
}

export default Toolbar