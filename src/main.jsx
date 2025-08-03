import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import App from './App.jsx'
import HelloWorld from '../Test.jsx'

createRoot(document.getElementById('root')).render(
  <StrictMode>
    {/* <HelloWorld/> */}
    <App />
  </StrictMode>,
)


