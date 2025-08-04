import React from 'react';

const CodeDoc = ({ functions }) => {
  return (
    <div className="grid gap-4">
      {functions.map((func, index) => (
        <div key={index} className="bg-gray-50 p-4 rounded-lg">
          <code className="text-lg font-mono text-blue-600">{func.name}</code>
          <p className="text-gray-600 mt-2">{func.description}</p>
        </div>
      ))}
    </div>
  );
};

export default CodeDoc;
