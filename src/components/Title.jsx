import React from 'react';

const Title = ({ exerciseName, difficulty = "Beginner", status = "ready" }) => {
  const getStatusColor = (status) => {
    switch (status) {
      case 'completed': return 'text-green-600 bg-green-100'
      case 'in-progress': return 'text-blue-600 bg-blue-100'
      case 'locked': return 'text-gray-600 bg-gray-100'
      default: return 'text-orange-600 bg-orange-100'
    }
  }

  const getDifficultyColor = (difficulty) => {
    switch (difficulty.toLowerCase()) {
      case 'easy': return 'text-green-600 bg-green-100'
      case 'medium': return 'text-yellow-600 bg-yellow-100'
      case 'hard': return 'text-red-600 bg-red-100'
      default: return 'text-blue-600 bg-blue-100'
    }
  }

  return (
    <div className="bg-white border-b border-gray-200 px-6 py-4 shadow-sm">
      <div className="flex items-center justify-between">
        <div className="flex items-center gap-4">
          <div className="flex items-center gap-3">
            <div className="w-10 h-10 bg-gradient-to-br from-blue-500 to-purple-600 rounded-lg flex items-center justify-center">
              <span className="text-white font-bold text-lg">📚</span>
            </div>
            <div>
              <h1 className="text-2xl font-bold text-gray-900 leading-tight">
                Exercise: {exerciseName}
              </h1>
              <p className="text-sm text-gray-500 mt-1">
                Karel Robot Programming Challenge
              </p>
            </div>
          </div>
        </div>
        
        <div className="flex items-center gap-3">
          {/* Badge Difficoltà */}
          <span className={`px-3 py-1 rounded-full text-xs font-semibold ${getDifficultyColor(difficulty)}`}>
            {difficulty}
          </span>
          
          {/* Badge Status */}
          <span className={`px-3 py-1 rounded-full text-xs font-semibold ${getStatusColor(status)}`}>
            {status.replace('-', ' ').toUpperCase()}
          </span>
        </div>
      </div>
    </div>
  );
};

export default Title;