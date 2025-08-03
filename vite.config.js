// vite.config.js
import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

import tailwindcss from '@tailwindcss/vite'


// https://vite.dev/config/
export default defineConfig({
  plugins: [
    react(),
    tailwindcss()
  ],
  server: {
    hmr: {
      overlay: false
    }
  },
  headers: {
    'Cache-Control': 'no-store, no-cache, must-revalidate, proxy-revalidate, max-age=0'
  },

});
