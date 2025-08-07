import { StopIcon } from "@heroicons/react/24/solid";



// Aggiungi questo nuovo componente per la navigazione
const NavigationControls = ({ onPrevious, onNext, hasPrevious, hasNext }) => (
  <div className="flex items-center gap-2">
    <button
      onClick={onPrevious}
      disabled={!hasPrevious}
      className={`px-3 py-1.5 text-sm font-medium rounded-md transition-colors ${hasPrevious
          ? 'text-gray-700 bg-gray-100 hover:bg-gray-200 border border-gray-300'
          : 'text-gray-400 bg-gray-50 border border-gray-200 cursor-not-allowed'
        }`}
      title="Previous Exercise"
    >
      <svg className="w-4 h-4 mr-1 inline" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M15 19l-7-7 7-7" />
      </svg>
      Previous
    </button>

    <button
      onClick={onNext}
      disabled={!hasNext}
      className={`px-3 py-1.5 text-sm font-medium rounded-md transition-colors ${hasNext
          ? 'text-gray-700 bg-gray-100 hover:bg-gray-200 border border-gray-300'
          : 'text-gray-400 bg-gray-50 border border-gray-200 cursor-not-allowed'
        }`}
      title="Next Exercise"
    >
      Next 
      <svg className="w-4 h-4 ml-1 inline" fill="none" stroke="currentColor" viewBox="0 0 24 24">
        <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M9 5l7 7-7 7" />
      </svg>
    </button>
  </div>
);

const EditorControls = ({
  keyboard,
  onKeyboardChange,
  showTiming,
  theme,
  onThemeChange
}) => (
  <div className="flex flex-1 items-center gap-3 p-3 bg-gray-50 overflow-x-auto">
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

    <div className="flex items-center gap-2 bg-white px-3 py-2 rounded-lg border border-gray-200 shrink-0">
      <input
        type="checkbox"
        checked={showTiming}
        onChange={(e) => onShowTimingChange(e.target.checked)}
        className="w-4 h-4 text-blue-600 border-gray-300 rounded focus:ring-blue-500"
      />
    </div>
  </div>
)

const CodeControls = ({
  onRun,
  isRunning,
  isActive,
  onDownloadFile,
  onReset
}) => (
  <div className="flex flex-1 items-center gap-3 p-3 border-b border-gray-100">
    {!isActive ? (
      <button
        onClick={onRun}
        disabled={isRunning}
        className="flex items-center justify-center gap-2 px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600 disabled:opacity-50 disabled:cursor-not-allowed transition-colors font-medium"
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
    ) :
      (
        <button
          onClick={onReset}
          disabled={isRunning}
          className="flex items-center justify-center gap-2 px-4 py-2 bg-red-500 text-white rounded-lg hover:bg-red-600 disabled:opacity-50 disabled:cursor-not-allowed transition-colors font-medium"
        >
          <StopIcon className="w-4 h-4" />
          Stop

        </button>


      )}

    <button
      onClick={onDownloadFile}
      className="flex items-center gap-2 px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600 transition-colors font-medium"
    >
      <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
        <path fillRule="evenodd" d="M3 17a1 1 0 011-1h12a1 1 0 110 2H4a1 1 0 01-1-1zm3.293-7.707a1 1 0 011.414 0L9 10.586V3a1 1 0 112 0v7.586l1.293-1.293a1 1 0 111.414 1.414l-3 3a1 1 0 01-1.414 0l-3-3a1 1 0 010-1.414z" clipRule="evenodd" />
      </svg>
      Download
    </button>

    {/* <button 
        onClick={onReset}
        className="flex items-center gap-2 px-4 py-2 bg-red-500 text-white rounded-lg hover:bg-red-600 transition-colors font-medium"
      >
        <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
          <path fillRule="evenodd" d="M4 2a1 1 0 011 1v2.101a7.002 7.002 0 0111.601 2.566 1 1 0 11-1.885.666A5.002 5.002 0 005.999 7H9a1 1 0 010 2H4a1 1 0 01-1-1V3a1 1 0 011-1zm.008 9.057a1 1 0 011.276.61A5.002 5.002 0 0014.001 13H11a1 1 0 110-2h5a1 1 0 011 1v5a1 1 0 11-2 0v-2.101a7.002 7.002 0 01-11.601-2.566 1 1 0 01.61-1.276z" clipRule="evenodd" />
        </svg>
        Reset
      </button> */}
  </div>

)


const IdeControls = ({
  isRunning,
  isActive,
  onRun,
  onDownloadFile,
  keyboard,
  onKeyboardChange,
  showTiming,
  onShowTimingChange,
  onReset,
  theme,
  onThemeChange,
  // Next Previous 
  onPrevious,
  onNext,
  hasPrevious,
  hasNext
}) => (
  <div className="flex flex-row w-full justify-between bg-white border-b border-gray-200">
    {/* Primary Actions Row */}
    <EditorControls
      keyboard={keyboard}
      onKeyboardChange={onKeyboardChange}
      showTiming={showTiming}
      onShowTimingChange={onShowTimingChange}
      theme={theme}
      onThemeChange={onThemeChange}
    />
    <div className="flex flex-row w-1/2 px-5">
      <CodeControls
        onRun={onRun}
        isRunning={isRunning}
        isActive={isActive}
        onDownloadFile={onDownloadFile}
        onReset={onReset}
      />

      {/* Code Controls */}
      <NavigationControls
        onPrevious={onPrevious}
        onNext={onNext}
        hasPrevious={hasPrevious}
        hasNext={hasNext}
      />

    </div>
  </div>
);




export default IdeControls