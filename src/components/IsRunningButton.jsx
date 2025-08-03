import React from "react";

const IsRunningButton = ({ isRunning }) => {
    if (!isRunning) return null;

    return (
        <div className="absolute top-8 right-8 z-20">
            <div className="flex items-center space-x-3 bg-gradient-to-r from-red-200 to-red-600 text-white 
                                            px-4 py-3 rounded-full shadow-lg backdrop-blur-sm">
                <div className="w-3 h-3 bg-white rounded-full animate-pulse"></div>
                <span className="text-sm font-medium">Running...</span>
            </div>
        </div>
    );
};

export default IsRunningButton;