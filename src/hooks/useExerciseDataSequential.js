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

      // Calculate total exercises
      const totalExercises = categoriesData.reduce((acc, category) => acc + category.exercises.length, 0)
      setLoadingMessage(`Loading ${totalExercises} exercises`)

      // Collect all exercise IDs
      const allExerciseIds = categoriesData.flatMap(category => category.exercises)

      // Create parallel promises for each exercise
      const exercisePromises = allExerciseIds.map(exerciseId => 
        loadSingleExercise(exerciseId, totalExercises)
      )

      // Execute all downloads in parallel
      const exerciseResults = await Promise.allSettled(exercisePromises)
      
      // Process results
      const exerciseData = {}
      exerciseResults.forEach((result, index) => {
        if (result.status === 'fulfilled' && result.value) {
          const exerciseId = allExerciseIds[index]
          exerciseData[exerciseId] = result.value
        } else {
          console.warn(`Failed to load exercise ${allExerciseIds[index]}:`, result.reason)
        }
      })
      
      setExercises(exerciseData)
      setLoadingMessage("All exercises loaded successfully!")
      
    } catch (err) {
      setError(err.message)
      setLoadingMessage("Failed to load exercises.")
      console.error('Failed to load exercise data:', err)
    } finally {
      setTimeout(() => {
        setLoading(false)
      }, 500)
    }
  }

  // Load a single exercise with all its files in parallel
  const loadSingleExercise = async (exerciseId, totalExercises) => {
    try {
      // Start all file downloads in parallel
      const [metadataPromise, readmePromise, solutionPromise, exercisePromise] = [
        fetch(`/exercise/${exerciseId}/metadata.json`).then(r => r.json()),
        fetch(`/exercise/${exerciseId}/README.md`).then(r => r.text()),
        fetch(`/exercise/${exerciseId}/SOLUTION.md`).then(r => r.text()),
        fetch(`/exercise/${exerciseId}/exercise.c`).then(r => r.text())
      ]

      // Wait for all files to complete
      const [metadata, readme, solution, exerciseCode] = await Promise.all([
        metadataPromise,
        readmePromise,
        solutionPromise,
        exercisePromise
      ])

      // Update progress (this might race, but it's just for UI feedback)
      setLoadingProgress(prev => {
        const newProgress = Math.min(prev + Math.round(100 / totalExercises), 100)
        setLoadingMessage(`Loading exercises... ${newProgress}%`)
        return newProgress
      })

      return {
        ...metadata,
        readme,
        solution,
        exerciseCode
      }

    } catch (error) {
      console.warn(`Failed to load exercise ${exerciseId}:`, error)
      
      // Still update progress even on failure
      setLoadingProgress(prev => {
        const newProgress = Math.min(prev + Math.round(100 / totalExercises), 100)
        setLoadingMessage(`Loading exercises... ${newProgress}%`)
        return newProgress
      })
      
      throw error
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
    const allExercises = Object.values(exercises)
      .filter(Boolean)
      .sort((a, b) => a.id - b.id)
    
    const currentIndex = allExercises.findIndex(ex => ex.id === parseInt(currentExerciseId))
    return currentIndex > 0 ? allExercises[currentIndex - 1] : null
  }

  const getNextExercise = (currentExerciseId) => {
    const allExercises = Object.values(exercises)
      .filter(Boolean)
      .sort((a, b) => a.id - b.id)
    
    const currentIndex = allExercises.findIndex(ex => ex.id === parseInt(currentExerciseId))
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