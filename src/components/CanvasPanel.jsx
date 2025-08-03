import React, { useRef, useEffect } from "react";

const CanvasPanel = ({
    canvasRef,
    isActive
}) => {
    return (
        <div class="w-full min-h-full">
            <div className={!isActive ? "h-full" : "hidden h-full"}>
                <div className="w-full h-full bg-gray-50 flex items-center justify-center">
                    <div className="text-center h-full">
                        {/* <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-blue-500 mx-auto"></div> */}
                        <span className="mt-2 text-gray-600">Karen is not running</span>
                    </div>
                </div>
            </div>
            <div className={isActive ? "h-full" : "hidden"}>
                <div className="w-full h-full bg-gray-100 flex flex-col">
                    <div className="h-full p-6 bg-gradient-to-br from-gray-100 to-gray-200 flex items-center justify-center">
                        <canvas
                            ref={canvasRef}
                            width={400}
                            height={300}
                            className="border-2 border-gray-800 bg-white rounded-lg shadow-lg max-w-full max-h-full"
                        />
                    </div>
                </div>
            </div>
        </div>
    );
};

export default CanvasPanel;