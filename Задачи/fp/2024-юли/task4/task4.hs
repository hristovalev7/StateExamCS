-- Задача 4 - Държавен изпит 09.07.2024 (Haskell)
-- Намиране на излишни реклами

-- а) Обединение на две множества
union :: Eq a => [a] -> [a] -> [a]
union xs ys = xs ++ [ y | y <- ys, not $ y `elem` xs]

-- б) Проверка за подмножество
subset :: Eq a => [a] -> [a] -> Bool
subset xs ys = all (\x -> x `elem` ys) xs

-- в) Събиране на всички потребители
collect :: Eq a => (b -> [a]) -> [b] -> [a]
collect clicks ads = foldr union [] (map clicks ads)

-- г) Намиране на излишни реклами
redundant :: Eq a => (b -> [a]) -> [b] -> [b]
redundant clicks ads = filter (\ad -> subset (clicks ad) (collect clicks (filter (\x -> x /= ad) ads))) ads

-- Примерна функция clicks
clicks :: String -> [Int]
clicks "a" = [1,2,3]
clicks "b" = [1,3,5]
clicks "c" = [2,3,5,7]
clicks _ = []

-- Тестване
main :: IO ()
main = do
  putStrLn "union [1,3,4] [4,1,7]:"
  print $ union [1,3,4] [4,1,7]
  
  putStrLn "\nsubset [1,2] [3,2,1]:"
  print $ subset [1,2] [3,2,1]
  
  putStrLn "\ncollect clicks [\"a\", \"b\", \"c\"]:"
  print $ collect clicks ["a", "b", "c"]
  
  putStrLn "\nredundant clicks [\"a\", \"b\", \"c\"]:"
  print $ redundant clicks ["a", "b", "c"]
