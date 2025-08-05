

import React from 'react'
import SidebarOpenButton from './SidebarOpenButton'
import { QuestionMarkCircleIcon } from '@heroicons/react/24/solid'
import KarelIcon from './KarelIcon'

const Toolbar = ({ onSidebarToggle, onHelpClick }) => {
  return (
    <header className="w-full bg-white border-b border-gray-200 shadow-sm z-20 h-16">
      <div className="flex flex-row items-center h-full px-4 py-2 gap-2 w-full min-w-0">
        <SidebarOpenButton
          onSidebarToggle={onSidebarToggle}
        />
        {/* Project Name */}
        <div className="flex-1 flex flex-row items-center min-w-0 pl-4">
          <KarelIcon 
            className="w-12 h-12 object-contain flex-shrink-0"
          />
        <div className="flex flex-col items-end min-w-0 pl-2 pr-4">
          <span className="text-base font-bold text-gray-900 leading-tight truncate">
            Karel WebAssembly IDE
          </span>
          <span className="text-xs text-gray-400 font-mono tracking-wide truncate pl-2">
            Modern C Playground
          </span>
          </div>
        </div>
        <button
          onClick={onHelpClick}
          className="ml-auto px-4 py-2 bg-blue-500 text-white rounded hover:bg-blue-600 transition flex items-center gap-2"
        >
          <QuestionMarkCircleIcon className="w-5 h-5" />
          Doc
        </button>
      </div>
    </header>
  )
}

export default Toolbar