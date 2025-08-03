import MarkdownReader from "./MarkdownReader";
import CanvasPanel from "./CanvasPanel";
import Terminal from "./Terminal";
import {
  BookOpenIcon,
  GlobeAltIcon,
  CommandLineIcon,
} from "@heroicons/react/24/solid";
import React, { useState } from "react";

function TabComponent({
  terminalOutput,
  canvasRef
}) {
  const [activeTab, setActiveTab] = useState('readme');

  return (
    <div className="w-full h-full">
      {/* Tab Navigation */}
      <div className="flex border-b border-gray-200">
        <button
          onClick={() => setActiveTab('readme')}
          className={`flex items-center gap-2 px-4 py-2 border-b-2 transition-colors ${activeTab === 'readme'
              ? 'border-blue-500 text-blue-600 bg-blue-50'
              : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
            }`}
        >
          <BookOpenIcon className="w-5 h-5" />
          README
        </button>
        <button
          onClick={() => setActiveTab('world')}
          className={`flex items-center gap-2 px-4 py-2 border-b-2 transition-colors ${activeTab === 'world'
              ? 'border-blue-500 text-blue-600 bg-blue-50'
              : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
            }`}
        >
          <GlobeAltIcon className="w-5 h-5" />
          Karen World
        </button>
        <button
          onClick={() => setActiveTab('terminal')}
          className={`flex items-center gap-2 px-4 py-2 border-b-2 transition-colors ${activeTab === 'terminal'
              ? 'border-blue-500 text-blue-600 bg-blue-50'
              : 'border-transparent text-gray-500 hover:text-gray-700 hover:border-gray-300'
            }`}
        >
          <CommandLineIcon className="w-5 h-5" />
          Terminal
        </button>
      </div>

      {/* Tab Content */}
      {/* <div className="p-4"> */}
      <div className="p-4 h-[calc(100%-3.5rem)] overflow-auto relative">
        <div className={activeTab === 'readme' ? '' : 'hidden'}>
          <MarkdownReader />
        </div>
        <div className={activeTab === 'world' ? '' : 'hidden'}>
          <CanvasPanel canvasRef={canvasRef} />
        </div>
        <div className={activeTab === 'terminal' ? '' : 'hidden'}>
          <Terminal output={terminalOutput} />
        </div>
      </div>
      {/* <div className="p-4 h-[calc(100%-3.5rem)] overflow-auto">
        {activeTab === 'readme' && <MarkdownReader />}
        {activeTab === 'world' && <CanvasPanel canvasRef={canvasRef}/>}
        {activeTab === 'terminal' && <Terminal output={terminalOutput} />}
      </div> */}
    </div>
  );
}

export default TabComponent