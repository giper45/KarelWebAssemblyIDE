import React from 'react';

const SidebarOpenButton = ({ onSidebarToggle }) => (
    <button
        onClick={onSidebarToggle}
        // className="inline-flex items-center justify-center p-2 rounded-lg bg-white border border-gray-300 shadow hover:bg-blue-100 hover:border-blue-400 focus:outline-none focus:ring-2 focus:ring-blue-400 transition"
        className="inline-flex items-center justify-center p-2 rounded-lg bg-white shadow hover:bg-blue-100 hover:border-blue-400 focus:outline-none focus:ring-2 focus:ring-blue-400 transition"
        aria-label="Open sidebar"
        type="button"
    >
        <svg className="w-6 h-6 text-gray-700" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth={2}
                d="M4 6h16M4 12h16M4 18h16"
            />
        </svg>
    </button>
);

export default SidebarOpenButton;