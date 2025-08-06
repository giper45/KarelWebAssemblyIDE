import React from "react";
import ReactMarkdown from "react-markdown";
import welcomeMarkdown from '../assets/Welcome.md?raw'
import rehypeRaw from "rehype-raw";
import remarkGfm from "remark-gfm";
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter';
import { tomorrow } from 'react-syntax-highlighter/dist/esm/styles/prism';

const MarkdownReader = ({
  markdownContent
}) => {
  
  const components = {
    code({ node, inline, className, children, ...props }) {
      const match = /language-(\w+)/.exec(className || '');
      const [copied, setCopied] = React.useState(false);

      // Funzione per copiare il codice negli appunti
      const handleCopy = () => {
        navigator.clipboard.writeText(String(children)).then(() => {
          setCopied(true);
          setTimeout(() => setCopied(false), 1200);
        });
      };

      if (!inline && match) {
        return (
          <div className="relative group">
            <button
              onClick={handleCopy}
              className="absolute top-2 right-2 z-10 px-2 py-1 text-xs rounded bg-gray-200 hover:bg-blue-500 hover:text-white transition-colors border border-gray-300 opacity-80 group-hover:opacity-100"
              style={{fontFamily: 'inherit'}}
              aria-label="Copy code"
            >
              {copied ? 'Copied!' : 'Copy'}
            </button>
            <SyntaxHighlighter
              style={tomorrow}
              language={match[1]}
              PreTag="div"
              {...props}
            >
              {String(children).replace(/\n$/, '')}
            </SyntaxHighlighter>
          </div>
        );
      } else {
        return (
          <code className={className} {...props}>
            {children}
          </code>
        );
      }
    },
    p({ children }) {
      return <p className="mb-4 leading-relaxed">{children}</p>;
    },
    pre({ children }) {
      return <pre className="bg-gray-100 p-4 rounded-lg overflow-x-auto mb-4">{children}</pre>;
    },
    h1({ children }) {
      return <h1 className="text-2xl font-bold mb-4 text-gray-900">{children}</h1>;
    },
    h2({ children }) {
      return <h2 className="text-xl font-semibold mb-3 text-gray-800">{children}</h2>;
    },
    h3({ children }) {
      return <h3 className="text-lg font-medium mb-2 text-gray-700">{children}</h3>;
    },
    ul({ children }) {
      return <ul className="list-disc pl-6 mb-4 space-y-1">{children}</ul>;
    },
    ol({ children }) {
      return <ol className="list-decimal pl-6 mb-4 space-y-1">{children}</ol>;
    },
    li({ children }) {
      return <li className="mb-1">{children}</li>;
    },
    blockquote({ children }) {
      return <blockquote className="border-l-4 border-blue-500 pl-4 italic text-gray-600 mb-4">{children}</blockquote>;
    }
  };

  return (
    <div className="prose max-w-none overflow-y-auto h-full p-4">
      <ReactMarkdown
        remarkPlugins={[remarkGfm]}
        rehypePlugins={[rehypeRaw]}
        components={components}
      >
        {markdownContent}
      </ReactMarkdown>
    </div>
  )
};

export default MarkdownReader;