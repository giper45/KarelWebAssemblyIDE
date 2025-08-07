// utils/handleCanvasMessage.js
export function handleCanvasMessage(e, canvasRef, worker) {
  const { type, fn, args } = e.data;
  if (type !== 'canvas' || !fn || !args) return;

  const canvas = window.canvas || (canvasRef && canvasRef.current);
  const ctx2d = window.ctx2d || (canvas && canvas.getContext('2d'));

  // Nota: Per gestire ImageData (createImageData, putImageData, imageDataSetData)
  // in un contesto di worker, il thread principale dovrebbe mantenere un Map
  // per associare gli 'handle' (numeri interi) agli oggetti ImageData.
  // Ad esempio:
  // if (!window.imageDataHandles) {
  //   window.imageDataHandles = new Map();
  // }
  // const handles = window.imageDataHandles;

  switch (fn) {
    case 'setWidth':
      if (canvas) canvas.width = args[0];
      break;
    case 'setHeight':
      if (canvas) canvas.height = args[0];
      break;
    case 'fillRect':
      if (ctx2d) ctx2d.fillRect(...args);
      break;
    case 'clearRect':
      if (ctx2d) ctx2d.clearRect(...args);
      break;
    case 'setFillStyle':
      if (ctx2d) ctx2d.fillStyle = args[0];
      break;
    case 'setFont':
      if (ctx2d) ctx2d.font = args[0];
      break;
    case 'setGlobalAlpha':
      if (ctx2d) ctx2d.globalAlpha = args[0];
      break;
    case 'setLineWidth':
      if (ctx2d) ctx2d.lineWidth = args[0];
      break;
    case 'beginPath':
      if (ctx2d) ctx2d.beginPath();
      break;
    case 'moveTo':
      if (ctx2d) ctx2d.moveTo(...args);
      break;
    case 'lineTo':
      if (ctx2d) ctx2d.lineTo(...args);
      break;
    case 'stroke':
      if (ctx2d) ctx2d.stroke();
      break;
    case 'strokeRect':
      if (ctx2d) ctx2d.strokeRect(...args);
      break;
    case 'fillText':
      // Gli argomenti contengono già la stringa elaborata dal worker
      if (ctx2d) ctx2d.fillText(...args);
      break;
    case 'strokeText':
      // Gli argomenti contengono già la stringa elaborata dal worker
      if (ctx2d) ctx2d.strokeText(...args);
      break;

    // --- Nuovi casi aggiunti basati sulle funzioni canvas_ fornite ---

    case 'requestAnimationFrame':
        requestAnimationFrame((ms) => {
          worker.postMessage({ type: 'canvas', fn: 'animationFrameCallback', args: [ms] });
        });
      break;

    case 'putImageData':
      // Questa funzione richiede l'accesso a una mappa 'handles' sul thread principale
      // che memorizza gli oggetti ImageData creati da 'canvas_createImageData'.
      // Senza tale mappa, non è possibile recuperare l'oggetto ImageData.
      // Esempio (se 'handles' fosse disponibile):
      // const imageData = handles.get(args[0]);
      // if (ctx2d && imageData) ctx2d.putImageData(imageData, args[1], args[2]);
      console.warn('putImageData richiede una mappa `handles` per recuperare gli oggetti ImageData.');
      break;

    case 'arc':
      if (ctx2d) ctx2d.arc(...args);
      break;
    case 'arcTo':
      if (ctx2d) ctx2d.arcTo(...args);
      break;
    case 'bezierCurveTo':
      if (ctx2d) ctx2d.bezierCurveTo(...args);
      break;
    case 'clip':
      // Il worker invia l'indice dell'array fillRule: ['nonzero', 'evenodd']
      if (ctx2d) ctx2d.clip(['nonzero', 'evenodd'][args[0]]);
      break;
    case 'closePath':
      if (ctx2d) ctx2d.closePath();
      break;
    case 'ellipse':
      if (ctx2d) ctx2d.ellipse(...args);
      break;
    case 'fill':
      // Il worker invia l'indice dell'array fillRule: ['nonzero', 'evenodd']
      if (ctx2d) ctx2d.fill(['nonzero', 'evenodd'][args[0]]);
      break;
    case 'quadraticCurveTo':
      if (ctx2d) ctx2d.quadraticCurveTo(...args);
      break;
    case 'rect':
      if (ctx2d) ctx2d.rect(...args);
      break;
    case 'restore':
      if (ctx2d) ctx2d.restore();
      break;
    case 'rotate':
      if (ctx2d) ctx2d.rotate(...args);
      break;
    case 'save':
      if (ctx2d) ctx2d.save();
      break;
    case 'scale':
      if (ctx2d) ctx2d.scale(...args);
      break;
    case 'setTransform':
      if (ctx2d) ctx2d.setTransform(...args);
      break;
    case 'transform':
      if (ctx2d) ctx2d.transform(...args);
      break;
    case 'translate':
      if (ctx2d) ctx2d.translate(...args);
      break;

    // Proprietà del Canvas (setter)
    case 'setLineCap':
      // Il worker invia l'indice dell'array lineCap: ['butt', 'round', 'square']
      if (ctx2d) ctx2d.lineCap = ['butt', 'round', 'square'][args[0]];
      break;
    case 'setLineDashOffset':
      if (ctx2d) ctx2d.lineDashOffset = args[0];
      break;
    case 'setLineJoin':
      // Il worker invia l'indice dell'array lineJoin: ['bevel', 'round', 'miter']
      if (ctx2d) ctx2d.lineJoin = ['bevel', 'round', 'miter'][args[0]];
      break;
    case 'setMiterLimit':
      if (ctx2d) ctx2d.miterLimit = args[0];
      break;
    case 'setShadowBlur':
      if (ctx2d) ctx2d.shadowBlur = args[0];
      break;
    case 'setShadowColor':
      // Gli argomenti contengono già la stringa elaborata dal worker
      if (ctx2d) ctx2d.shadowColor = args[0];
      break;
    case 'setShadowOffsetX':
      if (ctx2d) ctx2d.shadowOffsetX = args[0];
      break;
    case 'setShadowOffsetY':
      if (ctx2d) ctx2d.shadowOffsetY = args[0];
      break;
    case 'setStrokeStyle':
      // Gli argomenti contengono già la stringa elaborata dal worker
      if (ctx2d) ctx2d.strokeStyle = args[0];
      break;
    case 'setTextAlign':
      // Il worker invia l'indice dell'array textAlign: ['left', 'right', 'center', 'start', 'end']
      if (ctx2d) ctx2d.textAlign = ['left', 'right', 'center', 'start', 'end'][args[0]];
      break;
    case 'setTextBaseline':
      // Il worker invia l'indice dell'array textBaseline: ['top', 'hanging', 'middle', 'alphabetic', 'ideographic', 'bottom']
      if (ctx2d) ctx2d.textBaseline = [
        'top', 'hanging', 'middle', 'alphabetic', 'ideographic', 'bottom'
      ][args[0]];
      break;
    case 'measureText':
      // Il worker invia questo messaggio, ma il risultato di measureText non può essere
      // restituito direttamente al worker tramite questo meccanismo di messaggistica.
      // Il canvas_measureText del worker gestisce già il ritorno di 0 se è un worker.
      // Questo caso esegue semplicemente l'operazione sul thread principale, se necessario per effetti collaterali.
      if (ctx2d) {
        ctx2d.measureText(args[0]); // args[0] è già la stringa
      }
      break;

    default:
      // Puoi decommentare questa riga per loggare le funzioni non gestite
      // console.warn('Funzione Canvas non gestita:', fn, args);
      break;
  }
}
