import { useState, useEffect } from 'react';
import { getCurrentExerciseFromLocalStorage, isExercisePresentInLocalStorage } from '../utils/localStorageUtils';

export const useExerciseData = () => {
  const [categories, setCategories] = useState([]);
  const [exercises, setExercises] = useState({});
  const [loading, setLoading] = useState(true);
  const [sidebarReady, setSidebarReady] = useState(false); // Nuovo stato per sidebar
  const [firstExerciseReady, setFirstExerciseReady] = useState(false); // Stato per primo esercizio
  const [error, setError] = useState(null);
  const [loadingProgress, setLoadingProgress] = useState(0);
  const [loadingMessage, setLoadingMessage] = useState('Initializing...');

  // Funzione per caricare un singolo esercizio
  const loadSingleExercise = async (exerciseId) => {
    try {
      const exerciseResponse = await fetch(`/exercise/${exerciseId}/exercise.c`);
      if (!exerciseResponse.ok) throw new Error(`Exercise ${exerciseId} not found`);
      
      const exerciseCode = await exerciseResponse.text();
      
      const [readmeResponse, solutionResponse, metadataResponse] = await Promise.all([
        fetch(`/exercise/${exerciseId}/README.md`),
        fetch(`/exercise/${exerciseId}/SOLUTION.md`),
        fetch(`/exercise/${exerciseId}/metadata.json`)
      ]);

      const readme = readmeResponse.ok ? await readmeResponse.text() : '';
      const solution = solutionResponse.ok ? await solutionResponse.text() : '';
      const metadata = metadataResponse.ok ? await metadataResponse.json() : { 
        id: exerciseId, 
        name: `Exercise ${exerciseId}`, 
        difficulty: 'Medium' 
      };

      return {
        id: exerciseId,
        exerciseCode,
        readme,
        solution,
        ...metadata
      };
    } catch (error) {
      console.error(`Error loading exercise ${exerciseId}:`, error);
      return null;
    }
  };

  // Determina quale esercizio caricare per primo
  const getInitialExerciseId = () => {
    if (isExercisePresentInLocalStorage()) {
      const savedExercise = getCurrentExerciseFromLocalStorage();
      return savedExercise?.id || 1;
    }
    return 1;
  };

  // Carica il primo esercizio immediatamente
  const loadInitialExercise = async () => {
    try {
      setLoadingMessage('Loading initial exercise...');
      const initialId = getInitialExerciseId();
      
      const exercise = await loadSingleExercise(initialId);
      if (exercise) {
        setExercises(prev => ({ ...prev, [initialId]: exercise }));
        console.log(`Loaded initial exercise: ${initialId}`);
        setFirstExerciseReady(true);
        setLoadingMessage('Loading remaining exercises...');
      }
    } catch (error) {
      console.error('Error loading initial exercise:', error);
      setError(error.message);
    }
  };

  // Carica tutti gli esercizi in background
  const loadAllExercises = async () => {
    try {
      // Prima carica le categorie
      const categoriesResponse = await fetch('/categories.json');
      if (!categoriesResponse.ok) throw new Error('Failed to load categories');
      const categoriesData = await categoriesResponse.json();
      setCategories(categoriesData);

      // Raccogli tutti gli ID degli esercizi dalle categorie
      const allExerciseIds = new Set();
      categoriesData.forEach(category => {
        category.exercises?.forEach(id => allExerciseIds.add(id));
      });

      const exerciseIds = Array.from(allExerciseIds).sort((a, b) => a - b);
      const totalExercises = exerciseIds.length;
      const initialId = getInitialExerciseId();

      // Carica gli esercizi rimanenti (escludendo quello già caricato)
      const remainingIds = exerciseIds.filter(id => id !== initialId);
      
      for (let i = 0; i < remainingIds.length; i++) {
        const exerciseId = remainingIds[i];
        const exercise = await loadSingleExercise(exerciseId);
        
        if (exercise) {
          setExercises(prev => ({ ...prev, [exerciseId]: exercise }));
        }

        // Aggiorna il progresso
        const progress = Math.round(((i + 1) / totalExercises) * 100);
        setLoadingProgress(progress);
      }

      setSidebarReady(true);
      setLoading(false);
      setLoadingMessage('Complete!');
      
    } catch (error) {
      console.error('Error loading exercises:', error);
      setError(error.message);
      setLoading(false);
    }
  };

  useEffect(() => {
    const initializeData = async () => {
      // Prima carica l'esercizio iniziale
      await loadInitialExercise();
      // Poi carica tutto il resto in background
      await loadAllExercises();
    };

    initializeData();
  }, []);

  // Funzione per caricare un esercizio on-demand
  const loadExerciseOnDemand = async (exerciseId) => {
    if (exercises[exerciseId]) {
      return exercises[exerciseId]; // Già caricato
    }

    console.log(`Loading exercise ${exerciseId} on demand...`);
    const exercise = await loadSingleExercise(exerciseId);
    
    if (exercise) {
      setExercises(prev => ({ ...prev, [exerciseId]: exercise }));
      return exercise;
    }
    
    return null;
  };

  const getExercise = (id) => exercises[id] || null;

  const getExercisesByCategory = (categoryId) => {
    const category = categories.find(cat => cat.id === categoryId);
    if (!category) return [];
    
    return category.exercises
      .map(id => exercises[id])
      .filter(Boolean)
      .sort((a, b) => a.id - b.id);
  };

  const getPreviousExercise = (currentId) => {
    const allIds = Object.keys(exercises).map(Number).sort((a, b) => a - b);
    const currentIndex = allIds.indexOf(currentId);
    return currentIndex > 0 ? exercises[allIds[currentIndex - 1]] : null;
  };

  const getNextExercise = (currentId) => {
    const allIds = Object.keys(exercises).map(Number).sort((a, b) => a - b);
    const currentIndex = allIds.indexOf(currentId);
    return currentIndex < allIds.length - 1 ? exercises[allIds[currentIndex + 1]] : null;
  };

  return {
    categories,
    exercises,
    loading,
    sidebarReady,
    firstExerciseReady,
    error,
    loadingProgress,
    loadingMessage,
    getExercisesByCategory,
    getPreviousExercise,
    getNextExercise,
    getExercise,
    loadExerciseOnDemand, // Nuova funzione
  };
};