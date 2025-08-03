import React, { useState } from 'react';
import { useExerciseData } from '../hooks/useExerciseData';
import MarkdownReader from './MarkdownReader';

const ExerciseViewer = ({ exerciseId }) => {
  const { getExercise } = useExerciseData();
  const [activeTab, setActiveTab] = useState('description');
  
  const exercise = getExercise(exerciseId);

  if (!exercise) {
    return (
      <div className="p-6 text-center text-gray-500">
        <p>Exercise not found</p>
      </div>
    );
  }

  const tabs = [
    { id: 'description', label: 'Description', icon: '📝' },
    { id: 'solution', label: 'Solution', icon: '💡' },
    { id: 'code', label: 'Starter Code', icon: '💻' }
  ];

  return (
    <div className="bg-white rounded-lg border border-gray-200 shadow-sm">
      {/* Header */}
      <div className="p-4 border-b border-gray-200">
        <div className="flex items-center justify-between">
          <div>
            <h3 className="text-lg font-semibold text-gray-900">{exercise.name}</h3>
            <p className="text-sm text-gray-600 mt-1">{exercise.description}</p>
          </div>
          <div className="flex items-center gap-2">
            <span className={`px-2 py-1 rounded-full text-xs font-medium ${
              exercise.difficulty === 'Easy' ? 'text-green-600 bg-green-100' :
              exercise.difficulty === 'Medium' ? 'text-yellow-600 bg-yellow-100' :
              'text-red-600 bg-red-100'
            }`}>
              {exercise.difficulty}
            </span>
            {exercise.estimatedTime && (
              <span className="text-xs text-gray-500">
                ⏱️ {exercise.estimatedTime}
              </span>
            )}
          </div>
        </div>
      </div>

      {/* Tabs */}
      <div className="border-b border-gray-200">
        <nav className="flex space-x-0">
          {tabs.map((tab) => (
            <button
              key={tab.id}
              onClick={() => setActiveTab(tab.id)}
              className={`flex items-center gap-2 px-4 py-3 text-sm font-medium border-b-2 transition-colors ${
                activeTab === tab.id
                  ? 'border-blue-500 text-blue-600 bg-blue-50'
                  : 'border-transparent text-gray-500 hover:text-gray-700 hover:bg-gray-50'
              }`}
            >
              <span>{tab.icon}</span>
              {tab.label}
            </button>
          ))}
        </nav>
      </div>

      {/* Content */}
      <div className="p-4">
        {activeTab === 'description' && (
          <div className="prose prose-sm max-w-none">
            <MarkdownReader content={exercise.readme} />
          </div>
        )}
        
        {activeTab === 'solution' && (
          <div className="prose prose-sm max-w-none">
            <MarkdownReader content={exercise.solution} />
          </div>
        )}
        
        {activeTab === 'code' && (
          <div className="space-y-4">
            <div>
              <h4 className="text-sm font-semibold text-gray-900 mb-2">Exercise Starter Code</h4>
              <pre className="bg-gray-50 p-4 rounded-lg overflow-x-auto text-sm">
                <code>{exercise.exerciseCode}</code>
              </pre>
            </div>
            <div>
              <h4 className="text-sm font-semibold text-gray-900 mb-2">World Setup</h4>
              <pre className="bg-gray-50 p-4 rounded-lg overflow-x-auto text-sm">
                <code>{exercise.worldCode}</code>
              </pre>
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default ExerciseViewer;
