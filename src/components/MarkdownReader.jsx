import React from "react";
import ReactMarkdown from "react-markdown";
import welcomeMarkdown from '../assets/Welcome.md?raw'

const MarkdownReader = ({
  markdownContent
}) => {
  
// *prova*
//   `;

    return (
    <div className="prose max-w-none overflow-y-auto h-full">
      <ReactMarkdown>{markdownContent}</ReactMarkdown>
    </div>
    )
};

export default MarkdownReader;