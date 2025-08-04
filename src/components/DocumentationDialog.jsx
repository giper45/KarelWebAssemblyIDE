import React, { useState, useEffect } from 'react';
import { XMarkIcon } from '@heroicons/react/24/solid';
import CodeDoc from './CodeDoc';

const DocumentationDialog = ({ isOpen, onClose }) => {
  const [isVisible, setIsVisible] = useState(false);
  const [isAnimating, setIsAnimating] = useState(false);

  // Define function data
  const movementFunctions = [
    { name: 'karel_move()', description: 'Makes Karel move one step forward in the direction it\'s facing.' },
    { name: 'karel_turn_left()', description: 'Makes Karel turn 90 degrees to the left.' }
  ];

  const beeperFunctions = [
    { name: 'karel_pick_beeper()', description: 'Makes Karel pick up a beeper from the current position.' },
    { name: 'karel_put_beeper()', description: 'Makes Karel put down a beeper at the current position.' }
  ];

  const sensorFunctions = [
    { name: 'front_is_clear()', description: 'Returns true if there\'s no wall in front of Karel.' },
    { name: 'beepers_present()', description: 'Returns true if there are beepers at Karel\'s current position.' },
    { name: 'beepers_in_bag()', description: 'Returns true if Karel has beepers in its bag.' },
    { name: 'facing_north()', description: 'Returns true if Karel is facing north.' },
    { name: 'facing_south()', description: 'Returns true if Karel is facing south.' },
    { name: 'facing_east()', description: 'Returns true if Karel is facing east.' },
    { name: 'facing_west()', description: 'Returns true if Karel is facing west.' }
  ];

  const drawingFunctions = [
    { name: 'drawWalls()', description: 'Draws all walls in the Karel world.' },
    { name: 'drawGrid()', description: 'Draws the grid lines in the Karel world.' },
    { name: 'drawBeepers()', description: 'Draws all beepers in the Karel world.' },
    { name: 'drawKarel()', description: 'Draws Karel at its current position and orientation.' },
    { name: 'drawInfo()', description: 'Draws information about Karel\'s current state.' }
  ];

  const setupFunctions = [
    { name: 'karel_init()', description: 'Initializes Karel and the world. Call this in your setup() function.' },
    { name: 'karel_add_beeper(x, y)', description: 'Adds a beeper at position (x, y) in the world.' },
    { name: 'karel_add_horizontal_wall(x, y, length)', description: 'Adds a horizontal wall starting at (x, y) with the specified length.' },
    { name: 'karel_add_vertical_wall(x, y, length)', description: 'Adds a vertical wall starting at (x, y) with the specified length.' }
  ];

  const canvasFunctions = [
    { name: 'canvas_setFillStyleZ(color)', description: 'Sets the fill color for drawing operations. Use color names like "white", "red", etc.' },
    { name: 'canvas_fillRect(x, y, width, height)', description: 'Draws a filled rectangle at the specified position and size.' }
  ];

  useEffect(() => {
    if (isOpen) {
      setIsVisible(true);
      setTimeout(() => setIsAnimating(true), 10);
    } else {
      setIsAnimating(false);
      const timer = setTimeout(() => setIsVisible(false), 300);
      return () => clearTimeout(timer);
    }
  }, [isOpen]);

  if (!isVisible) return null;

  return (
    <div 
      className={`fixed inset-0 flex items-center justify-center z-50 p-4 transition-all duration-300 ease-in-out ${
        isAnimating ? 'backdrop-brightness-50' : 'backdrop-brightness-100'
      }`}
      onClick={onClose}
    >
      <div 
        className={`bg-white rounded-lg shadow-xl max-w-5xl w-full max-h-[90vh] overflow-hidden transition-all duration-300 ease-in-out ${
          isAnimating ? 'scale-100 opacity-100 translate-y-0' : 'scale-95 opacity-0 translate-y-4'
        }`}
        onClick={(e) => e.stopPropagation()}
      >
        {/* Header */}
        <div className="flex justify-between items-center p-6 border-b border-gray-200">
          <h2 className="text-3xl font-bold text-gray-900">Karel Documentation</h2>
          <button
            onClick={onClose}
            className="p-2 hover:bg-gray-100 rounded-full transition-colors"
          >
            <XMarkIcon className="w-6 h-6 text-gray-500" />
          </button>
        </div>

        {/* Content */}
        <div className="p-6 overflow-y-auto max-h-[calc(90vh-120px)]">
          <div className="space-y-8">
            {/* Introduction */}
            <section>
              <h3 className="text-xl font-semibold text-gray-800 mb-4">About Karel</h3>
              <p className="text-gray-600 leading-relaxed">
                Karel is a simple programming environment designed to teach the basics of programming logic. 
                Karel is a robot that lives in a grid world and can move around, pick up and put down objects called "beepers", 
                and interact with walls.
              </p>
            </section>

            <h3> Guide for students </h3>
            {/* Movement Functions */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Movement Functions</h4>
              <CodeDoc functions={movementFunctions} />
            </section>

            {/* Beeper Functions */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Beeper Functions</h4>
              <CodeDoc functions={beeperFunctions} />
            </section>

            {/* Sensor Functions */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Sensor Functions</h4>
              <CodeDoc functions={sensorFunctions} />
            </section>

            <h3> Guide for world designers </h3>
            {/* Drawing Functions */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Drawing Functions</h4>
              <CodeDoc functions={drawingFunctions} />
            </section>

            {/* Setup Functions */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Setup Functions</h4>
              <CodeDoc functions={setupFunctions} />
            </section>

            {/* Canvas Functions */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Canvas Functions</h4>
              <CodeDoc functions={canvasFunctions} />
            </section>

            {/* Program Structure */}
            <section>
              <h4 className="text-xl font-semibold text-gray-800 mb-4">Program Structure</h4>
              <div className="bg-gray-50 p-4 rounded-lg">
                <pre className="text-sm text-gray-800 overflow-x-auto">
{`#include "karel.h"

void setup() {
    // Initialize Karel and set up the world
    karel_init();
    
    // Add beepers and walls here
    karel_add_beeper(3, 2);
    karel_add_horizontal_wall(3, 2, 2);
}

void loop(double timeSec, double elapsedSec) {
    // Clear the canvas
    canvas_setFillStyleZ("white");
    canvas_fillRect(0, 0, 800, 600);
    
    // Draw the world
    drawWalls();
    drawGrid();
    drawBeepers();
    drawKarel();
    drawInfo();
    
    // Your Karel logic here
    if (front_is_clear()) {
        karel_move();
    } else {
        karel_turn_left();
    }
}`}
                </pre>
              </div>
            </section>
          </div>
        </div>
      </div>
    </div>
  );
};

export default DocumentationDialog;
