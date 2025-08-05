import React from 'react'
import KarelIcon from './KarelIcon'

const LoadingSpinner = ({ message = "Loading in progress...", progress = 0 }) => {
  const circumference = 2 * Math.PI * 32 // radius = 32
  const strokeDasharray = circumference
  const strokeDashoffset = circumference - (progress / 100) * circumference

  return (
    <div className="fixed inset-0 bg-white bg-opacity-95 backdrop-blur-sm z-50 flex flex-col items-center justify-center">
      {/* Main loading container */}
      <div className="flex flex-col items-center justify-center space-y-6 p-8">
        
        {/* Karel Icon with progress ring */}
        <div className="relative">
          {/* Background circle */}
          <svg className="w-20 h-20 transform -rotate-90" viewBox="0 0 80 80">
            <circle
              cx="40"
              cy="40"
              r="32"
              stroke="rgb(219, 234, 254)" // blue-100
              strokeWidth="6"
              fill="transparent"
            />
            {/* Progress circle */}
            <circle
              cx="40"
              cy="40"
              r="32"
              stroke="rgb(37, 99, 235)" // blue-600
              strokeWidth="6"
              fill="transparent"
              strokeLinecap="round"
              strokeDasharray={strokeDasharray}
              strokeDashoffset={strokeDashoffset}
              className="transition-all duration-300 ease-out"
            />
          </svg>
          
          {/* Karel Icon in the center */}
          <div className="absolute inset-0 flex items-center justify-center">
            <div className="w-12 h-12 flex items-center justify-center bg-white rounded-full shadow-lg">
              <KarelIcon className="w-8 h-8 object-contain" />
            </div>
          </div>
        </div>

        {/* Progress percentage */}
        <div className="text-center">
          <div className="text-2xl font-bold text-blue-600 mb-1">
            {progress}%
          </div>
          <div className="w-64 bg-gray-200 rounded-full h-2 mb-4">
            <div 
              className="bg-blue-600 h-2 rounded-full transition-all duration-300 ease-out"
              style={{ width: `${progress}%` }}
            ></div>
          </div>
        </div>

        {/* Loading message */}
        <div className="text-center space-y-2">
          <h2 className="text-xl font-bold text-gray-800">
            Karel WebAssembly IDE
          </h2>
          <p className="text-gray-600 font-medium animate-pulse">
            {message}
          </p>
        </div>

        {/* Progress dots animation */}
        <div className="flex space-x-2">
          <div className="w-2 h-2 bg-blue-600 rounded-full animate-bounce"></div>
          <div className="w-2 h-2 bg-blue-600 rounded-full animate-bounce" style={{ animationDelay: '0.1s' }}></div>
          <div className="w-2 h-2 bg-blue-600 rounded-full animate-bounce" style={{ animationDelay: '0.2s' }}></div>
        </div>

        {/* Subtle background pattern */}
        <div className="absolute inset-0 opacity-5 pointer-events-none">
          <div className="w-full h-full bg-gradient-to-br from-blue-100 to-purple-100"></div>
        </div>
      </div>
    </div>
  )
}

export default LoadingSpinner