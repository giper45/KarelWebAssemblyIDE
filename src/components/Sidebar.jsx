import React, { useState } from 'react';
const categories = [
  {
    icon: "✅",
    name: "1. Sequences and Basic Commands",
    concept: "Ordered execution of instructions",
    objectives: "Understand movement, orientation, instruction order.",
    exercises: [
      { name: "Move forward 1 step", description: "Move Karel forward by one cell." },
      { name: "Move forward 5 steps", description: "Move Karel forward by five cells." },
      { name: "Turn left", description: "Rotate Karel 90° to the left." },
      { name: "Turn right (3 lefts)", description: "Rotate Karel 90° to the right using three left turns." },
      { name: "Draw a square", description: "Make Karel walk in a square (implicit loop)." },
      { name: "Draw an 'L'", description: "Make Karel draw the letter L." },
      { name: "Spin 360°", description: "Make Karel turn around completely." },
      { name: "Return to start", description: "Go back to the starting point." },
      { name: "Enter a door", description: "Move Karel through a door." },
      { name: "Move while path is clear", description: "Advance until there is no more space." },
    ]
  },
  {
    icon: "📦",
    name: "2. Data Manipulation (beepers)",
    concept: "Input/output, state",
    objectives: "Learn to read, write, and modify the environment state.",
    exercises: [
      { name: "Pick up a beeper", description: "Pick up a beeper from the ground." },
      { name: "Drop a beeper", description: "Place a beeper on the ground." },
      { name: "Pick up all beepers on a cell", description: "Collect all beepers from one cell." },
      { name: "Pick up all beepers in the world", description: "Collect all beepers everywhere." },
      { name: "Place a beeper in each cell of a row", description: "Fill a row with beepers." },
      { name: "Place a beeper every 2 cells", description: "Place beepers every other cell." },
      { name: "Count beepers", description: "Count how many beepers are present." },
      { name: "Copy beepers to another row", description: "Duplicate beepers from one row to another." },
      { name: "Checkerboard beepers", description: "Create a checkerboard pattern with beepers." },
      { name: "Transport a beeper from A to B", description: "Move a beeper from one location to another." },
    ]
  },
  {
    icon: "🧱",
    name: "3. Conditions and Branching (if/else)",
    concept: "Decision making based on world state",
    objectives: "Detect obstacles, use sensors, make decisions.",
    exercises: [
      { name: "Move until wall", description: "Advance until a wall is encountered." },
      { name: "Walk to beeper or wall", description: "Move until a beeper or wall is found." },
      { name: "Turn if wall ahead", description: "Turn if there is a wall in front." },
      { name: "Jump over 1-high wall", description: "Jump over a single-height wall." },
      { name: "Jump over a series of walls", description: "Jump over multiple walls in sequence." },
      { name: "Find first free cell on the right", description: "Detect and move to the first free cell to the right." },
      { name: "Avoid obstacles", description: "Navigate around obstacles." },
      { name: "Find corridor exit", description: "Find and exit a corridor." },
      { name: "Enter a room", description: "Move Karel into a room." },
      { name: "Fill closed area with beepers", description: "Fill an enclosed area with beepers." },
    ]
  },
  {
    icon: "🔁",
    name: "4. Loops (while, for, until)",
    concept: "Repetition, code optimization",
    objectives: "Use loops to avoid repetition and traverse dynamic environments.",
    exercises: [
      { name: "Walk in a circle 3 times", description: "Make Karel walk in a circle three times." },
      { name: "Pick up beepers in 5 cells", description: "Collect beepers from five consecutive cells." },
      { name: "Repeat a sequence of moves", description: "Repeat a set of moves multiple times." },
      { name: "Count steps and stop at tenth", description: "Move and stop after ten steps." },
      { name: "Walk in a spiral", description: "Make Karel walk in a spiral pattern." },
      { name: "Fill a row with beepers", description: "Place beepers in every cell of a row." },
      { name: "Climb a staircase", description: "Move Karel up a staircase." },
      { name: "Copy a pattern to multiple rows", description: "Duplicate a pattern across rows." },
      { name: "Fill all rows", description: "Fill every row with beepers." },
      { name: "Fill only even rows", description: "Place beepers only in even-numbered rows." },
    ]
  },
  {
    icon: "🧩",
    name: "5. Functions and Decomposition",
    concept: "Abstraction, code reuse, logical order",
    objectives: "Write modular and reusable code.",
    exercises: [
      { name: "Write turnRight()", description: "Implement a right turn function." },
      { name: "Write goToRowEnd()", description: "Create a function to move to the end of a row." },
      { name: "Write jumpWall()", description: "Create a function to jump over a wall." },
      { name: "Build a rectangle with functions", description: "Use functions to build a rectangle." },
      { name: "Compose 'enter, collect, exit'", description: "Sequence entering, collecting, and exiting." },
      { name: "Explore and clean a room", description: "Write code to explore and clean a room." },
      { name: "Build letters like 'H', 'T', 'L'", description: "Use functions to draw letters." },
      { name: "Draw a border with beepers", description: "Place beepers along the border." },
      { name: "Go around an obstacle", description: "Navigate around an obstacle." },
      { name: "Solve a maze (right hand)", description: "Solve a maze using the right-hand rule." },
    ]
  }
];

// COMPONENTE: SidebarHeader
const SidebarHeader = ({ onToggle }) => (
  <div className="bg-gradient-to-r from-blue-50 to-indigo-50 px-6 py-4 border-b border-gray-200">
    <div className="flex items-center justify-between">
      <div className="flex items-center gap-3">
        <div className="w-8 h-8 bg-gradient-to-br from-blue-500 to-purple-600 rounded-lg flex items-center justify-center">
          <span className="text-white font-bold text-sm">📋</span>
        </div>
        <h2 className="text-lg font-bold text-gray-900">Exercises</h2>
      </div>
      <button
        onClick={onToggle}
        className="p-2 hover:bg-white/50 rounded-lg transition-colors"
      >
        <svg className="w-5 h-5 text-gray-600" fill="none" stroke="currentColor" viewBox="0 0 24 24">
          <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M6 18L18 6M6 6l12 12" />
        </svg>
      </button>
    </div>
  </div>
);

// COMPONENTE: SidebarSearch
const SidebarSearch = ({ searchTerm, setSearchTerm }) => (
  <div className="mt-4 px-6">
    <div className="relative">
      <input
        type="text"
        placeholder="Search exercises..."
        value={searchTerm}
        onChange={(e) => setSearchTerm(e.target.value)}
        className="w-full px-4 py-2 pl-10 bg-white border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-blue-500 text-sm"
      />
    </div>
  </div>
);

// COMPONENTE: ExerciseItem
const getStatusIcon = (status) => {
  switch (status) {
    case 'completed': return '✅'
    case 'in-progress': return '🔄'
    case 'locked': return '🔒'
    default: return '📝'
  }
};
const getDifficultyColor = (difficulty) => {
  switch (difficulty.toLowerCase()) {
    case 'easy': return 'text-green-600'
    case 'medium': return 'text-yellow-600'
    case 'hard': return 'text-red-600'
    default: return 'text-blue-600'
  }
};

const ExerciseItem = ({ exercise, isActive, onSelect }) => (
  <div
    onClick={() => onSelect(exercise)}
    className={`
      p-3 rounded-lg border transition-all duration-200 cursor-pointer
      ${isActive ? 'bg-blue-50 border-blue-400 shadow' : 'bg-white border-gray-200 hover:border-blue-300 hover:shadow-sm'}
    `}
  >
    <div>
      <h4 className="font-semibold text-gray-900 text-sm">{exercise.name}</h4>
      <p className="text-xs text-gray-600 mt-1">{exercise.description}</p>
    </div>
  </div>
);

const CategorySection = ({ category, currentExercise, onExerciseSelect }) => (
  <div className="mb-6">
    <div className="flex items-center gap-2 mb-1">
      <span className="text-xl">{category.icon}</span>
      <span className="font-bold text-base text-gray-800">{category.name}</span>
    </div>
    <div className="text-xs text-gray-500 mb-1 italic">{category.concept}</div>
    <div className="text-xs text-gray-500 mb-2">{category.objectives}</div>
    <div className="space-y-2">
      {category.exercises.map((exercise, idx) => (
        <ExerciseItem
          key={exercise.name}
          exercise={{ ...exercise, category: category.name }}
          isActive={currentExercise?.name === exercise.name}
          onSelect={onExerciseSelect}
        />
      ))}
    </div>
  </div>
);

const ExerciseList = ({ categories, currentExercise, onExerciseSelect, searchTerm }) => (
  <div className="flex-1 overflow-y-auto p-4">
    {categories.map((category) => {
      // Filtra per ricerca
      const filtered = category.exercises.filter(e =>
        e.name.toLowerCase().includes(searchTerm.toLowerCase())
      );
      if (filtered.length === 0) return null;
      return (
        <CategorySection
          key={category.name}
          category={{ ...category, exercises: filtered }}
          currentExercise={currentExercise}
          onExerciseSelect={onExerciseSelect}
        />
      );
    })}
  </div>
);

const Sidebar = ({
  isOpen,
  onToggle,
  currentExercise,
  onExerciseSelect
}) => {
  const [searchTerm, setSearchTerm] = useState('');

  return (
    <>
      {isOpen && (
        <div
          className="fixed inset-0 bg-black bg-opacity-50 z-40 md:hidden"
          onClick={onToggle}
        />
      )}
      <div className={`
        fixed top-0 left-0 h-full bg-white border-r border-gray-200 shadow-xl z-50 transform transition-transform duration-300 ease-in-out
        ${isOpen ? 'translate-x-0' : '-translate-x-full'}
        w-80 md:w-96 flex flex-col min-h-0
      `}>
        <SidebarHeader onToggle={onToggle} />
        <SidebarSearch searchTerm={searchTerm} setSearchTerm={setSearchTerm} />
        <ExerciseList
          categories={categories}
          currentExercise={currentExercise}
          onExerciseSelect={onExerciseSelect}
          searchTerm={searchTerm}
        />
        {/* SidebarFooter può essere adattato se vuoi mostrare progress per categoria */}
      </div>
    </>
  );
};

export default Sidebar;