import React, { useRef, useEffect } from "react";

const CanvasPanel = ({ canvasRef }) => {


    return (
            <div className="h-full p-6 bg-gradient-to-br from-gray-100 to-gray-200 flex items-center justify-center">
                <canvas
                    ref={canvasRef}
                    width={400}
                    height={300}
                    className="border-2 border-gray-800 bg-white rounded-lg shadow-lg max-w-full max-h-full"
                />
            </div>
    );
};

export default CanvasPanel;