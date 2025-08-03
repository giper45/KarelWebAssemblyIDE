import React, { useState } from 'react';
import { useExerciseData } from '../hooks/useExerciseData';

const Sidebar = ({ isOpen, onExerciseSelect, currentExerciseId }) => {
  const { categories, loading, error, getExercisesByCategory } = useExerciseData();
  const [expandedCategories, setExpandedCategories] = useState(new Set(['basic-movement']));

  const toggleCategory = (categoryId) => {
    setExpandedCategories(prev => {
      const newSet = new Set(prev);
      if (newSet.has(categoryId)) {
        newSet.delete(categoryId);
      } else {
        newSet.add(categoryId);
      }
      return newSet;
    });
  };

  const getDifficultyColor = (difficulty) => {
    switch (difficulty?.toLowerCase()) {
      case 'easy': return 'text-green-600 bg-green-100';
      case 'medium': return 'text-yellow-600 bg-yellow-100';
      case 'hard': return 'text-red-600 bg-red-100';
      default: return 'text-blue-600 bg-blue-100';
    }
  };

  if (loading) {
    return (
      <aside className={`fixed left-0 top-16 h-[calc(100vh-4rem)] bg-white border-r border-gray-200 transition-transform duration-300 z-10 ${isOpen ? 'translate-x-0' : '-translate-x-full'} w-full`}>
        <div className="p-6 flex items-center justify-center">
          <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-blue-500"></div>
          <span className="ml-2">Loading exercises...</span>
        </div>
      </aside>
    );
  }

  if (error) {
    return (
      <aside className={`fixed left-0 top-16 h-[calc(100vh-4rem)] bg-white border-r border-gray-200 transition-transform duration-300 z-10 ${isOpen ? 'translate-x-0' : '-translate-x-full'} w-full`}>
        <div className="p-6 text-red-600">
          <p>Error loading exercises: {error}</p>
        </div>
      </aside>
    );
  }

  return (
    <aside className={`fixed left-0 top-16 h-[calc(100vh-4rem)] bg-white border-r border-gray-200 transition-transform duration-300 z-10 ${isOpen ? 'translate-x-0' : '-translate-x-full'} w-full`}>
      <div className="h-full overflow-y-auto">
        <div className="p-4 border-b border-gray-200 bg-gradient-to-r from-blue-50 to-purple-50">
          <h2 className="text-lg font-bold text-gray-900">Learning Path</h2>
          <p className="text-sm text-gray-600 mt-1">Karel Programming Exercises</p>
        </div>

        <div className="p-4 space-y-4">
          {categories.map((category) => {
            const isExpanded = expandedCategories.has(category.id);
            const categoryExercises = getExercisesByCategory(category.id);
            
            return (
              <div key={category.id} className="border border-gray-200 rounded-lg overflow-hidden">
                <button
                  onClick={() => toggleCategory(category.id)}
                  className="w-full p-4 text-left bg-gray-50 hover:bg-gray-100 transition-colors border-b border-gray-200"
                >
                  <div className="flex items-start justify-between">
                    <div className="flex items-start gap-3">
                      <span className="text-2xl">{category.icon}</span>
                      <div>
                        <h3 className="font-semibold text-gray-900">{category.name}</h3>
                        <p className="text-sm text-gray-600 mt-1">{category.concept}</p>
                        <p className="text-xs text-gray-500 mt-2">{category.objectives}</p>
                      </div>
                    </div>
                    <svg 
                      className={`w-5 h-5 text-gray-500 transition-transform ${isExpanded ? 'rotate-180' : ''}`}
                      fill="none" 
                      stroke="currentColor" 
                      viewBox="0 0 24 24"
                    >
                      <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M19 9l-7 7-7-7" />
                    </svg>
                  </div>
                </button>

                {isExpanded && (
                  <div className="bg-white">
                    {categoryExercises.length === 0 ? (
                      <div className="p-4 text-gray-500 text-sm">
                        No exercises available in this category.
                      </div>
                    ) : (
                      categoryExercises.map((exercise) => (
                        <button
                          key={exercise.id}
                          onClick={() => onExerciseSelect(exercise)}
                          className={`w-full p-3 text-left border-b border-gray-100 last:border-b-0 hover:bg-blue-50 transition-colors ${
                            currentExerciseId === exercise.id ? 'bg-blue-100 border-l-4 border-l-blue-500' : ''
                          }`}
                        >
                          <div className="flex items-start justify-between">
                            <div className="flex-1 min-w-0">
                              <h4 className="font-medium text-gray-900 text-sm truncate">
                                {exercise.name}
                              </h4>
                              <p className="text-xs text-gray-600 mt-1 line-clamp-2">
                                {exercise.description}
                              </p>
                              {exercise.estimatedTime && (
                                <p className="text-xs text-gray-500 mt-1">
                                  ⏱️ {exercise.estimatedTime}
                                </p>
                              )}
                            </div>
                            <div className="ml-2 flex flex-col items-end gap-1">
                              <span className={`px-2 py-1 rounded-full text-xs font-medium ${getDifficultyColor(exercise.difficulty)}`}>
                                {exercise.difficulty}
                              </span>
                            </div>
                          </div>
                        </button>
                      ))
                    )}
                  </div>
                )}
              </div>
            );
          })}
        </div>

        <div className="p-4 border-t border-gray-200 bg-gray-50">
          <div className="text-xs text-gray-500 text-center">
            <p>Karel WebAssembly IDE</p>
            <p>Dynamic Exercise System</p>
          </div>
        </div>
      </div>
    </aside>
  );
};

export default Sidebar;
