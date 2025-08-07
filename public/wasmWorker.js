// Import shared.js for API and WASM logic
importScripts('/shared.js');
let animationFrameQueue = [];

// Worker state
let api = null;
let running = false;

// Listen for messages from main thread
self.onmessage = async function (e) {
  const { type, fn, code, args, showTiming } = e.data;

    if (type === 'canvas' && fn === 'animationFrameCallback') {
      // ms è il timestamp fornito dal main thread
      const ms = args[0];
      // Chiama la funzione C esportata dal WASM per aggiornare il canvas
      if (!api || !api.exports || !api.exports.canvas_loop) {
          animationFrameQueue.push(ms);
          console.warn("API not ready, queuing animation frame callback");
          return;
        }

        api.exports.canvas_loop(ms);
    }

  if (type === 'init') {
    // Initialize API (can pass options if needed)
    api = new self.API({
      readBuffer: async (filename) => {
        const response = await fetch(filename);
        return response.arrayBuffer();
      },
      compileStreaming: async (filename) => {
        const response = await fetch(filename);
        return WebAssembly.compile(await response.arrayBuffer());
      },
      hostWrite: (output) => {
        // Send output to main thread
        self.postMessage({ type: 'output', output });
      },
      showTiming: showTiming,
      clang: 'clang',
      lld: 'lld',
      memfs: 'memfs',
      sysroot: 'sysroot.tar'
    });
    self.postMessage({ type: 'initialized' });
  }

  if (type === 'run') {
    if (!api) {
      self.postMessage({ type: 'error', error: 'API not initialized' });
      return;
    }
    running = true;
    try {
      await api.compileLinkRun(code);
      while (animationFrameQueue.length > 0) {
        const ms = animationFrameQueue.shift();
        if (api.exports && api.exports.canvas_loop) 
          api.exports.canvas_loop(ms);
      }
      self.postMessage({ type: 'done' });
    } catch (err) {
      self.postMessage({ type: 'error', error: err.message });
    } finally {
      running = false;
    }
  }

  if (type === 'stop') {
    console.log("Stopping WASM worker");
    console.log(api && running)
    if (api) {
      try {
        await api.stop();
        self.postMessage({ type: 'stopped' });
      } catch (err) {
        self.postMessage({ type: 'error', error: err.message });
      }
      running = false;
    }
  }
};