import { useState, useEffect } from 'react'

export const useExerciseData = () => {
  const [categories, setCategories] = useState([])
  const [exercises, setExercises] = useState({})
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState(null)
  const [loadingProgress, setLoadingProgress] = useState(0)
  const [loadingMessage, setLoadingMessage] = useState("Loading exercises...")



  useEffect(() => {
    loadExerciseData()
  }, [])

  const loadExerciseData = async () => {
    try {
      setLoading(true)
      setLoadingProgress(0)
      setLoadingMessage("Loading categories and exercises...")
      
      // Load categories
      const categoriesResponse = await fetch('/categories.json')
      const categoriesData = await categoriesResponse.json()
      setCategories(categoriesData)

      // Load all exercises
      const totalExercises = categoriesData.reduce((acc, category) => acc + category.exercises.length, 0)
      setLoadingMessage(`Loading ${totalExercises} exercises...`)


      const exerciseData = {}
      let loadedExercises = 0
      
      for (const category of categoriesData) {
        for (const exerciseId of category.exercises) {
          try {
            // Load metadata
            const metadataResponse = await fetch(`/exercise/${exerciseId}/metadata.json`)
            const metadata = await metadataResponse.json()
            
            // Load README
            const readmeResponse = await fetch(`/exercise/${exerciseId}/README.md`)
            const readme = await readmeResponse.text()
            
            // Load solution
            const solutionResponse = await fetch(`/exercise/${exerciseId}/SOLUTION.md`)
            const solution = await solutionResponse.text()
            
            // // Load world code
            // const worldResponse = await fetch(`/exercise/${exerciseId}/world.c`)
            // const worldCode = await worldResponse.text()
            
            // Load exercise code (starter code)
            const exerciseResponse = await fetch(`/exercise/${exerciseId}/exercise.c`)
            const exerciseCode = await exerciseResponse.text()

            exerciseData[exerciseId] = {
              ...metadata,
              readme,
              solution,
              // worldCode,
              exerciseCode
            }


            loadedExercises++
            const progress = Math.round((loadedExercises / totalExercises) * 100)
            setLoadingProgress(progress)
            setLoadingMessage(`Loaded ${loadedExercises} of ${totalExercises} exercises (${progress}%)`)

          } catch (err) {
            console.warn(`Failed to load exercise ${exerciseId}:`, err)
            loadedExercises++
            const progress = Math.round((loadedExercises / totalExercises) * 100)
            setLoadingProgress(progress)
          }
        }
      }
      
      setExercises(exerciseData)
      setLoadingMessage("All exercises loaded successfully!")
    } catch (err) {
      setError(err.message)
      setLoadingMessage("Failed to load exercises.")

      console.error('Failed to load exercise data:', err)
    } finally {
      setTimeout(() => {
        setLoading(false)
      }, 500) // Delay to show final loading message
    }
  }

  const getExercisesByCategory = (categoryId) => {
    const category = categories.find(cat => cat.id === categoryId)
    if (!category) return []
    
    return category.exercises
      .map(id => exercises[id])
      .filter(Boolean)
      .sort((a, b) => a.id - b.id)
  }

  const getExercise = (exerciseId) => {
    return exercises[exerciseId] || null
  }

  const getCategoryInfo = (categoryId) => {
    return categories.find(cat => cat.id === categoryId) || null
  }

  const getPreviousExercise = (currentExerciseId) => {
    // Get all exercises sorted by ID
    const allExercises = Object.values(exercises)
      .filter(Boolean)
      .sort((a, b) => a.id - b.id)
    
    // Find current exercise index
    const currentIndex = allExercises.findIndex(ex => ex.id === parseInt(currentExerciseId))
    
    // Return previous exercise if exists
    return currentIndex > 0 ? allExercises[currentIndex - 1] : null
  }

  const getNextExercise = (currentExerciseId) => {
    // Get all exercises sorted by ID
    const allExercises = Object.values(exercises)
      .filter(Boolean)
      .sort((a, b) => a.id - b.id)
    
    // Find current exercise index
    const currentIndex = allExercises.findIndex(ex => ex.id === parseInt(currentExerciseId))
    
    // Return next exercise if exists
    return currentIndex < allExercises.length - 1 ? allExercises[currentIndex + 1] : null
  }

  return {
    categories,
    exercises,
    loading,
    error,
    loadingProgress,
    loadingMessage,
    getExercisesByCategory,
    getExercise,
    getCategoryInfo,
    getPreviousExercise,
    getNextExercise,
    reload: loadExerciseData
  }
}
