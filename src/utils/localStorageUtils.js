const LOCAL_STORAGE_KAREL_KEY = "karel_save_app"
function saveToLocalStorage(key, value) {
  try {
    localStorage.setItem(key, JSON.stringify(value));
  } catch (e) {
    console.error('Error saving to localStorage', e);
  }
}
function saveToLocalStorageString(key, value) {
  try {
    localStorage.setItem(key, value)
  } catch (e) {
    console.error('Error saving to localStorage', e);
  }
}


function getFromLocalStorage(key, fallback = null) {
  try {
    const item = localStorage.getItem(key);
    return item ? JSON.parse(item) : fallback;
  } catch (e) {
    console.error('Error reading from localStorage', e);
    return fallback;
  }
}
function getStringFromLocalStorage(key, fallback = null) {
  try {
    const item = localStorage.getItem(key);
    return item 
  } catch (e) {
    console.error('Error reading from localStorage', e);
    return fallback;
  }
}
function isPresentInLocalStorage(key) {
  try {
    return localStorage.getItem(key) !== null;
  } catch (e) {
    console.error('Error checking presence in localStorage', e);
    return false;
  }
}



function removeFromLocalStorage(key) {
  try {
    localStorage.removeItem(key);
  } catch (e) {
    console.error('Error removing from localStorage', e);
  }
}
export function isCodePresentInLocalStorage() {
  return isPresentInLocalStorage(`${LOCAL_STORAGE_KAREL_KEY}__code`) && 
    getCodeFromLocalStorage() != 'undefined'
  ;
}

export function isExercisePresentInLocalStorage() {
  return isPresentInLocalStorage(`${LOCAL_STORAGE_KAREL_KEY}__exercise`);
}


export function saveCodeToLocalStorage(code) {
    saveToLocalStorageString(`${LOCAL_STORAGE_KAREL_KEY}__code`, code)
}
export function saveCurrentExerciseToLocalStorage(currentExercise) {
    saveToLocalStorage(`${LOCAL_STORAGE_KAREL_KEY}__exercise`, currentExercise)
}

export function getCodeFromLocalStorage() {
    return getStringFromLocalStorage(`${LOCAL_STORAGE_KAREL_KEY}__code`)
}
export function getCurrentExerciseFromLocalStorage() {
    return getFromLocalStorage(`${LOCAL_STORAGE_KAREL_KEY}__exercise`)
}