import React from "react";
import ReactMarkdown from "react-markdown";
import welcomeMarkdown from '../assets/Welcome.md?raw'

const MarkdownReader = () => {
  
// *prova*
//   `;

    return (
    <div className="prose max-w-none overflow-y-auto h-full">
      <ReactMarkdown>{welcomeMarkdown}</ReactMarkdown>
    </div>
    )
};

export default MarkdownReader;