import React from "react";
import ReactMarkdown from "react-markdown";
import welcomeMarkdown from '../assets/Welcome.md?raw'
import rehypeRaw from "rehype-raw";
import remarkGfm from "remark-gfm";
import rehypeSlug from "rehype-slug";
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter';
import { tomorrow } from 'react-syntax-highlighter/dist/esm/styles/prism';

// Funzione per estrarre gli heading dal markdown
function extractHeadings(markdown) {
  const headingRegex = /^(#{1,6})\s+(.*)$/gm;
  const headings = [];
  let match;
  while ((match = headingRegex.exec(markdown)) !== null) {
    const level = match[1].length;
    const text = match[2].trim();
    // Genera l'anchor come fa ReactMarkdown
    const anchor = text
      .toLowerCase()
      .replace(/[^\w\s-]/g, '')
      .replace(/\s+/g, '-');
    headings.push({ level, text, anchor });
  }
  return headings;
}

function splitMarkdownAtFirstH1(markdown) {
  const h1Regex = /^#\s+.*$/m;
  const match = h1Regex.exec(markdown);
  if (!match) return { before: '', after: markdown };

  const index = match.index;
  const before = markdown.slice(0, index);
  const after = markdown.slice(index);
  return { before, after };
}


const TableOfContents = ({ markdownContent }) => {
  const headings = extractHeadings(markdownContent);
  const [open, setOpen] = React.useState(false);

  const handleClick = (e, anchor) => {
    e.preventDefault();
    const el = document.getElementById(anchor);
    if (el) {
      el.scrollIntoView({ behavior: "smooth", block: "start" });
    }
  };

  return (
    <nav className="mb-8 p-4 bg-white rounded-lg border border-gray-300 shadow-sm">
      <button
        onClick={() => setOpen((v) => !v)}
        className="flex items-center gap-2 font-bold mb-3 text-black focus:outline-none"
        aria-expanded={open}
        aria-controls="toc-list"
      >
        <svg width="20" height="20" fill="none" viewBox="0 0 24 24">
          <path stroke="#222" strokeWidth="2" d="M4 6h16M4 12h16M4 18h16"/>
        </svg>
        Table of Contents
        <span className="ml-2">
          {open ? (
            <svg width="16" height="16" fill="none" viewBox="0 0 24 24">
              <path stroke="#222" strokeWidth="2" d="M6 15l6-6 6 6"/>
            </svg>
          ) : (
            <svg width="16" height="16" fill="none" viewBox="0 0 24 24">
              <path stroke="#222" strokeWidth="2" d="M6 9l6 6 6-6"/>
            </svg>
          )}
        </span>
      </button>
      {open && (
        <ul id="toc-list">
          {headings.map((h, idx) => (
            <li
              key={idx}
              style={{ marginLeft: (h.level - 1) * 20 }}
              className="mb-1"
            >
              <a
                href={`#${h.anchor}`}
                onClick={(e) => handleClick(e, h.anchor)}
                className="flex items-center gap-1 text-black hover:text-blue-700 hover:underline transition-colors duration-150"
              >
                <span>
                  {h.level === 1 && <span>📘</span>}
                  {h.level === 2 && <span>📗</span>}
                  {h.level === 3 && <span>📙</span>}
                  {h.level > 3 && <span>📄</span>}
                </span>
                {h.text}
              </a>
            </li>
          ))}
        </ul>
      )}
    </nav>
  );
};

const MarkdownReader = ({
  markdownContent
}) => {
  const { before, after } = splitMarkdownAtFirstH1(markdownContent);
  
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
    // h1({ children }) {
    //   return <h1 className="text-2xl font-bold mb-4 text-gray-900">{children}</h1>;
    // },
    // h2({ children }) {
    //   return <h2 className="text-xl font-semibold mb-3 text-gray-800">{children}</h2>;
    // },
    // h3({ children }) {
    //   return <h3 className="text-lg font-medium mb-2 text-gray-700">{children}</h3>;
    // },
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
      {/* Render any content before the first H1 */}
      {before && (
        <ReactMarkdown
          remarkPlugins={[remarkGfm]}
          rehypePlugins={[rehypeRaw, rehypeSlug]}
          components={components}
        >
          {before}
        </ReactMarkdown>
      )}
      {/* Render first H1 and immediately after, the TOC */}
      {after && (
        <>
          {/* Find first line (H1), render it */}
          <ReactMarkdown
            remarkPlugins={[remarkGfm]}
            rehypePlugins={[rehypeRaw, rehypeSlug]}
            components={components}
          >
            {after.split('\n').slice(0, 1).join('\n')}
          </ReactMarkdown>
          {/* Render TOC */}
          <TableOfContents markdownContent={markdownContent} />
          {/* Render the rest of the markdown after H1 */}
          <ReactMarkdown
            remarkPlugins={[remarkGfm]}
            rehypePlugins={[rehypeRaw, rehypeSlug]}
            components={components}
          >
            {after.split('\n').slice(1).join('\n')}
          </ReactMarkdown>
        </>
      )}
    </div>
  );
};
export default MarkdownReader;