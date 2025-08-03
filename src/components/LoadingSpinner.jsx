import React from 'react'

const LoadingSpinner = ({ message = "Loading..." }) => {
  return (
    <div className="flex flex-col items-center justify-center space-y-4">
      <div className="relative">
        <div className="w-12 h-12 border-4 border-blue-200 border-t-blue-600 rounded-full animate-spin"></div>
        <div className="absolute inset-0 w-12 h-12 border-4 border-transparent border-r-purple-600 rounded-full animate-spin" style={{ animationDirection: 'reverse', animationDuration: '1s' }}></div>
      </div>
      <p className="text-gray-600 font-medium">{message}</p>
    </div>
  )
}

export default LoadingSpinner
