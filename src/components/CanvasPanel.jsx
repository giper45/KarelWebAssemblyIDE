import React, { useRef, useEffect } from "react";

function filter(output) {
   // Remove all lines before "[0m test.wasm"
    const lines = output.split('\n');
    const startIdx = lines.findIndex(line => line.includes('[0m test.wasm'));
    const filteredLines = startIdx >= 0 ? lines.slice(startIdx) : lines;

    // For filtering lines, use pattern.test(line) instead of includes
    return filteredLines.slice(2)
        .join('\n');
}
const MiniTerminal = ({ consoleOutput }) => (
    // Mini terminal at the bottom
    filter(consoleOutput) !== "" ? (
        <div className="w-full h-full px-4 pb-2">
            <textarea
                className="w-full h-full bg-black text-white font-mono text-xs rounded p-2 resize-none"
                value={filter(consoleOutput)}
                readOnly
                rows={15}
            />
        </div>
    ) : <div />
);
        

const CanvasPanel = ({
    canvasRef,
    isActive,
    consoleOutput
}) => {
    return (
        <div className="w-full min-h-full">
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
                    <MiniTerminal consoleOutput={consoleOutput} />
                </div>
            </div>
        </div>
    );
};
// const CanvasPanel = ({
//     canvasRef,
//     isActive
// }) => {
//     return (
//             <div className="h-full">
//                 <div className="w-full h-full bg-gray-100 flex flex-col">
//                     <div className="h-full p-6 bg-gradient-to-br from-gray-100 to-gray-200 flex items-center justify-center">
//                         <canvas
//                             ref={canvasRef}
//                             width={400}
//                             height={300}
//                             className="border-2 border-gray-800 bg-white rounded-lg shadow-lg max-w-full max-h-full"
//                         />
//                     </div>
//                 </div>
//             </div>
//     );
// };

export default CanvasPanel;